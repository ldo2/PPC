#ifndef _STACK_COMPILER_HPP_
#define _STACK_COMPILER_HPP_

#include <stack>
#include <string>

#include <stack_compiler/sc_preheader.hpp>
#include <stack_compiler/types.hpp>
#include <stack_compiler/symbols.hpp>

using std::stack;
using std::string;

namespace StackCompiler {

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
      unsigned int charIndex;
      
      ISymbolDBAdapter& symbolDBAdapter;
      IExpressionFactory& exprFactory;
      
      void processCharacter(char c);
      
      void processCurrentSymbol(void);
      bool processInCurrentSymbol(char c);
      
      void processOpenBracket(char c);
      void processCloseBracket(char c);
      
      void processArgSeparator(char c);
      
      void processSuspendedSymbols(void);
      
      void executeSymbol(ISymbol *sym);
      void executeFunction(FunctionSymbol *sym);
      void executeOperator(OperatorSymbol *sym);
      
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
      virtual IExpression *createExpression(ISymbol sym);
      
      virtual IExpression *createUnitaryOperator(ISymbol sym, IExpression *child);
      virtual IExpression *createBinaryOperator(ISymbol sym, IExpression *left, IExpression *right);
      
      virtual IExpression *createFunction(ISymbol sym);
      // virtual IExpression *createFunction(ISymbol sym, int argc, IExpression args[]);
      
      virtual void reverseAddSubExpression(IExpression *parent, IExpression *child);
  };
  
};

#endif /* _STACK_COMPILER_HPP_ */

