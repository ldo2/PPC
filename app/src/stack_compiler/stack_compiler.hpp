#ifndef _STACK_COMPILER_HPP_
#define _STACK_COMPILER_HPP_

#include <stack>
#include <string>

using std::stack;
using std::string;

namespace StackCompiler {
  
  class Compiler;
  
  class ISymbol;
  class IExpression;
  
  enum OperatorAssociativity;
  enum OperatorType;
  
  enum SymbolType;
  enum CharType;
  
  enum BracketType;
  
  class ISymbolDBAdapter;
  class IExpressionFactory;
  
  enum OperatorAssociativity {
    LEFT,
    RIGHT,
    NON
  };
  
  enum OperatorType {
    UNITARY = 1,
    BINARY = 2
  };
  
  enum BracketType {
    ROUND,
    SQUARE,
    CURLY,
    ANGLE
  };
  
  enum CharType {
    LEFT_ROUND  = '(',
    RIGHT_ROUND = ')',
    LEFT_SQUARE = '[',
    RIGHT_SQUARE = ']',
    LEFT_CURLY = '{',
    RIGHT_CURLY = '}',
    SEPARATOR = ',',
    STRING_BRACKET = '\"',
    SYMBOL_BRACKET = '\'',
    OPERATOR,
    LETTER,
    DIGIT,
    SPACE,
    OTHER
  };
  
  enum SymbolType {
    FUNCTION,
    OPERATOR,
    NUMBER,
    SYMBOL,
    STRING,
    BRACKET
  };


  class Compiler {
    public: 
      Compiler(ISymbolDBAdapter& _symbolDBAdapter, IExpressionFactory& _exprFactory);
      ~Compiler(void);
      
      IExpression *compile(String str);
    private:
      stack<ISymbol *> symbolStack;
      stack<IExpression *> exprStack;
      
      ISymbol *currentSymbol;
      
      ISymbolDBAdapter& symbolDBAdapter;
      IExpressionFactory& exprFactory;
    
      CharType charType(char c);
      
      void processCharacter(char c);
      
      void processSuspendedSymbols(void);
      
  };


  class ISymbol {
    public:
      ISymbol(SymbolType _type);
      ISymbol(SymbolType _type, char _c);
      
      virtual ~ISymbol(void);
      
      SymbolType getType(void);
      string getString(void);
      
      virtual bool canAppendChar(char c);
      virtual void appendChar(char c);
      
      
    protected:
      SymbolType type;
      string str;
  };
  
  
  class IExpression {
    public:
      IExpression(void);
      virtual ~IExpression(void);
  };
  
  
  class ISymbolDBAdapter {
    public:
      virtual bool isOperator(string& oper);
      virtual bool isFunction(string& func);
      
      virtual long getPriority(string& oper);
      virtual OperatorAssociativity getAssociativity(string& oper);
  };
  
  
  class IExpressionFactory {
    public:
      virtual IExpression *createExpression(ISymbol *sym);
      
      virtual IExpression *createUnitaryOperator(ISymbol *sym, IExpression *child);
      virtual IExpression *createBinaryOperator(ISymbol *sym, IExpression *left, IExpression *right);
      
      virtual IExpression *createFunction(ISymbol *sym, BracketType bt);
      // virtual IExpression *createFunction(ISymbol *sym, BracketType bt, int argc, IExpression args[]);
      
      virtual void reverseAddSubExpression(IExpression *parent, IExpression *child);
  };
  
};

#endif /* _STACK_COMPILER_HPP_ */

