#ifndef _RPN_EXAMPLE_HPP_
#define _RPN_EXAMPLE_HPP_

#include <string>
#include <stack_compiler/compiler.hpp>

using namespace std;
using namespace StackCompiler;

class RPNExpression;
class RPNExpressionFactory;
class RPNSymbolDBAdapter;

class RPNExpression : public IExpression {
    public:
      string str;
    
      RPNExpression(void);
      RPNExpression(string _str);
      virtual ~RPNExpression(void);
      
      friend ostream& operator << (ostream& os, RPNExpression *e);
      
    friend class RPNExpressionFactory;
};

class RPNExpressionFactory : public IExpressionFactory {
    private: 
      bool trace;
    public:
      RPNExpressionFactory(void);
      RPNExpressionFactory(bool _trace);
      
      virtual IExpression *createExpression(ISymbol sym);
      
      virtual IExpression *createUnaryOperator(ISymbol sym, OperatorType type, IExpression *child);
      virtual IExpression *createBinaryOperator(ISymbol sym, IExpression *left, IExpression *right);
      
      virtual IExpression *createFunction(ISymbol sym);
      
      virtual void reverseAddSubExpression(IExpression *parent, IExpression *child);
};

class RPNSymbolDBAdapter : public ISymbolDBAdapter {
    public:
      virtual bool isOperator(string& oper);
      virtual bool isFunction(string& func);
      
      virtual long getPriority(string& oper);
      virtual OperatorAssociativity getAssociativity(string& oper);
};

#endif /* _RPN_EXAMPLE_HPP_ */

