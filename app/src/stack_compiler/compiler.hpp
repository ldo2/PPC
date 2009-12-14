#ifndef _STACK_COMPILER_HPP_
#define _STACK_COMPILER_HPP_

#include <stack>
#include <string>

#include <stack_compiler/types.hpp>

using std::stack;
using std::string;

namespace StackCompiler {
  
  class Compiler;
  
  class ISymbol;
  class IExpression;
  
  class ISymbolDBAdapter;
  class IExpressionFactory;

  class Compiler {
    public: 
      Compiler(ISymbolDBAdapter& _symbolDBAdapter, IExpressionFactory& _exprFactory);
      ~Compiler(void);
      
      IExpression *compile(string& str);
      
      static CharType charType(char c);
    private:
      stack<ISymbol *> symbolStack;
      stack<IExpression *> exprStack;
      
      ISymbol *currentSymbol;
      int charIndex;
      
      ISymbolDBAdapter& symbolDBAdapter;
      IExpressionFactory& exprFactory;
      
      void processCharacter(char c);
      
      void processSuspendedSymbols(void);
      
  };


  class ISymbol {
    protected:
      ISymbol(SymbolType _type);
    
      SymbolType type;
      string str;
      
    public:
      ISymbol();
      
      virtual ~ISymbol(void);
      
      SymbolType getType(void);
      string getString(void);
      
      virtual bool canAppendChar(char c);
      virtual void appendChar(char c);
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

