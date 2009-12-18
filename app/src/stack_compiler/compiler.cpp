#include <stack_compiler/compiler.hpp>


#include <cctype>

#include <stack_compiler/types.hpp>
#include <stack_compiler/symbols.hpp>

namespace StackCompiler {
  /* some secret dark magic here */
  inline bool isoperator(const char c);

 /*
  * class Compiler implementation
  */

  Compiler::Compiler(ISymbolDBAdapter& _symbolDBAdapter, IExpressionFactory& _exprFactory) : symbolDBAdapter(_symbolDBAdapter), exprFactory(_exprFactory) {}
  Compiler::~Compiler(void) {}
      
  IExpression *Compiler::compile(string& str) {
    currentSymbol = NULL;
    //charIndex = -1;
    IExpression *result;
    
    processCharacter('(');
    
    for (charIndex = 0; charIndex < str.length(); ++charIndex) {
      processCharacter(str[charIndex]);
    }
    
    processCharacter(')');
    
    result = exprStack.top();
    exprStack.pop();
    
    return result;
  }
    
    
  /*
   * Следующая функция реализована очень плохо, ее надо исправить. 
   */   
  CharType Compiler::charType(char c) {
    switch(c) {
      case '(':
      case '[':
      case '{':
        return OPEN_BRACKET_CHAR;
      case ')':
      case ']':
      case '}':
        return CLOSE_BRACKET_CHAR;
      case ',':
        return SEPARATOR_CHAR;
      case '\"':
        return STRING_BRACKET_CHAR;
    }

    if(isdigit(c))             { return DIGIT_CHAR;    }
    if(isalpha(c) || c == '_') { return LETTER_CHAR;   }
    if(isspace(c))             { return SPACE_CHAR;    }
    if(isoperator(c))          { return OPERATOR_CHAR; }

    return OTHER_CHAR;
  }

  bool isoperator(const char c) {
    switch(c) {
      case '=':
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
      case '^':
      case '<':
      case '>':
      case '|':
      case '&':
      case '!':
      case '~':
      case '@':
      case '$':
      case '#':
      case '\'':
      case '\\':
        return true;
    }
    
    return false;
  }
      
  void Compiler::processCharacter(char c) {
    if(processInCurrentSymbol(c)) { 
      return; 
    }
  
    switch(Compiler::charType(c)) {
      case OPEN_BRACKET_CHAR:
        processOpenBracket(c);
        break;
      case CLOSE_BRACKET_CHAR:
        processCloseBracket(c);
        break;
      case SEPARATOR_CHAR:
        processArgSeparator(c);
        break;
      case STRING_BRACKET_CHAR:
        /* not support now */
        break;
      case OPERATOR_CHAR:
        currentSymbol = new OperatorSymbol();
        currentSymbol->appendChar(c);
        break;
      case LETTER_CHAR:
        currentSymbol = new FunctionSymbol();
        currentSymbol->appendChar(c);
        break;
      case DIGIT_CHAR:
        currentSymbol = new NumberSymbol();
        currentSymbol->appendChar(c);
        break;
      case SPACE_CHAR:
        /* ignore space characters */
        processCurrentSymbol();
        break;
      case OTHER_CHAR:
        /* throw some error here */
        break;
    }
  }
  
  bool Compiler::processInCurrentSymbol(char c) {
    if(currentSymbol != NULL) {
      if(currentSymbol->canAppendChar(c)) {
        currentSymbol->appendChar(c);
        return true;
      } else {
        processCurrentSymbol();
      }
    }
    
    return false;
  }
  
  void Compiler::processCurrentSymbol(void) {
    if(currentSymbol == NULL) { return; }
    
    switch(currentSymbol->getType()) {
      case FUNCTION:
      case BRACKET:
        symbolStack.push(currentSymbol);
        break;
      case OPERATOR:
        /* refactor to autoupdate */
        dynamic_cast<OperatorSymbol *>(currentSymbol)->priority = symbolDBAdapter.getPriority(currentSymbol->getString());
        dynamic_cast<OperatorSymbol *>(currentSymbol)->associativity = symbolDBAdapter.getAssociativity(currentSymbol->getString());
        processSuspendedSymbols();
        symbolStack.push(currentSymbol);
        break;
      case NUMBER:
      case STRING:
        executeSymbol(currentSymbol);
        break;
      default:
        /* throw exception here ! */
        break;
    }
    
    currentSymbol = NULL;
  }
  
  void Compiler::processOpenBracket(char c) {
    if(symbolStack.empty() || symbolStack.top()->getType() != FUNCTION) {
      symbolStack.push(new FunctionSymbol());
    }
    
    currentSymbol = new BracketSymbol(c);
  }
  
  void Compiler::processCloseBracket(char c) {
    BracketSymbol bs(c);
    bool hasArg = false;

    while(!symbolStack.empty() && symbolStack.top()->getType() != BRACKET) {
      hasArg = true;
      executeSymbol(symbolStack.top());
      symbolStack.pop();
    }
    
    if(symbolStack.empty()) {
      // throw exception here !
    } 
    
    if(bs.isCloseFor(dynamic_cast<BracketSymbol *>(symbolStack.top()))) {
      symbolStack.pop();
      if(symbolStack.empty()) {
        // idioto !!!
        throw 23;
      }
      if(hasArg) {
        dynamic_cast<FunctionSymbol *>(symbolStack.top())->getArgumentCount();
      }
      /* execute function */
      executeSymbol(symbolStack.top());
      symbolStack.pop();
    } else {
      // throw exception here, wronb brackets !!!
    }
    
  }
      
  void Compiler::processArgSeparator(char c) {
    ISymbol *bracket;
    while(!symbolStack.empty() && symbolStack.top()->getType() != BRACKET) {
      executeSymbol(symbolStack.top());
      symbolStack.pop();
    }
    
    if(symbolStack.empty()) {
      // throw exception here !
    } 
    
    bracket = symbolStack.top();
    symbolStack.pop();
    // here no empty check
    
    dynamic_cast<FunctionSymbol *>(symbolStack.top())->getArgumentCount();
    
    symbolStack.push(bracket);
  }
  
      
  void Compiler::processSuspendedSymbols(void) {
    OperatorSymbol *os = dynamic_cast<OperatorSymbol *>(currentSymbol);
    while(!symbolStack.empty() && (*os << *dynamic_cast<OperatorSymbol *>(symbolStack.top()))) {
      executeSymbol(symbolStack.top());
      symbolStack.pop();
    }
  }
  
  void Compiler::executeSymbol(ISymbol *sym) {
    switch(sym->getType()) {
      case FUNCTION:
        executeFunction(dynamic_cast<FunctionSymbol *>(sym));
        break;
      case OPERATOR:
        executeOperator(dynamic_cast<OperatorSymbol *>(sym));
        break;
      case NUMBER:
      case STRING:
        exprStack.push(exprFactory.createExpression(*sym));
        break;
      default:
        // throw some exception here
        break;
    }
    
    delete sym;
  }
  
  void Compiler::executeFunction(FunctionSymbol *sym) {
    IExpression *func;
    int i;
    
    func = exprFactory.createFunction(*sym);
    for(i = 0; i < sym->getArgumentCount(); ++i) {
      if(exprStack.empty()) {
        // throw exception here ;
      }
      exprFactory.reverseAddSubExpression(func, exprStack.top());
      exprStack.pop();
    }
        
    exprStack.push(func); 
  }
  
  void Compiler::executeOperator(OperatorSymbol *sym) {
    IExpression *left, *right;
    
    // TODO UNITARY OPERATOR PROCESS
    
    right = exprStack.top();
    symbolStack.pop();
    left = exprStack.top();
    symbolStack.pop();
        
    exprStack.push(exprFactory.createBinaryOperator(*sym, left, right));
  }
  
 /*
  * end of Compiler class
  */
  
  
 /*
  * interface IExpression
  */

  IExpression::IExpression(void) {}
  IExpression::~IExpression(void) {}
  
 /*
  * end of IExpression interface
  */
  
  ISymbolDBAdapter::ISymbolDBAdapter(void) {}
  
  bool ISymbolDBAdapter::isOperator(string& oper) {
    return true;
  }
  
  bool ISymbolDBAdapter::isFunction(string& func) {
    return true;
  }
      
  long  ISymbolDBAdapter::getPriority(string& oper) {
    return 0;
  }
  
  OperatorAssociativity  ISymbolDBAdapter::getAssociativity(string& oper) {
    return LEFT;
  }
  

  IExpression *IExpressionFactory::createExpression(ISymbol sym) {
    return NULL;
  }
      
  IExpression *IExpressionFactory::createUnitaryOperator(ISymbol sym, IExpression *child) {
    return NULL;
  }
  IExpression *IExpressionFactory::createBinaryOperator(ISymbol sym, IExpression *left, IExpression *right) {
    return NULL;
  }
      
  IExpression *IExpressionFactory::createFunction(ISymbol sym) {
    return NULL;
  }
      
  void IExpressionFactory::reverseAddSubExpression(IExpression *parent, IExpression *child) {}

}; 

