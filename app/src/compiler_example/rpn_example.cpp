#include <compiler_example/rpn_example.hpp>
#include <iostream>

/*
 * class RPNExpression implementation
 */
       
  RPNExpression::RPNExpression() {}
  RPNExpression::RPNExpression(string _str) : str(_str) {}
  RPNExpression::~RPNExpression(void) {}

/*
 * end of RPNExpression class
 */

/*
 * class RPNExpressionFactory implementation
 */

  RPNExpressionFactory::RPNExpressionFactory(void) : trace(false) {}
  RPNExpressionFactory::RPNExpressionFactory(bool _trace) : trace(_trace) {}
      
  IExpression *RPNExpressionFactory::createExpression(ISymbol sym) {
    if(trace) {
      cout << "RPNEF: createExpression for \"" << sym.getString() << "\"" << endl;
    }
    return new RPNExpression(sym.getString());
  }
      
  IExpression *RPNExpressionFactory::createUnaryOperator(ISymbol sym, OperatorType type, IExpression *child) {
    if(trace) {
      cout << "RPNEF: createUnaryOperator \"" << sym.getString() << "\" ";
      cout << "mode: " << (type == UNARY_POSTFIX ? "postfix" : "prefix") << " ";
      cout << "for \"" << dynamic_cast<RPNExpression *>(child)->str << "\"" << endl;
    }
    
    RPNExpression *result = new RPNExpression(dynamic_cast<RPNExpression *>(child)->str + " " + sym.getString());
    delete child;
    return result;
  }
  
  IExpression *RPNExpressionFactory::createBinaryOperator(ISymbol sym, IExpression *left, IExpression *right) {
    if(trace) {
      cout << "RPNEF: createBinaryOperator \"" << sym.getString() << "\" ";
      cout << "for \"" << dynamic_cast<RPNExpression *>(left)->str << "\" ";
      cout << "and \"" << dynamic_cast<RPNExpression *>(right)->str << "\"" << endl;
    }
    RPNExpression *result = new RPNExpression(dynamic_cast<RPNExpression *>(left)->str + " " + dynamic_cast<RPNExpression *>(right)->str + " " + sym.getString());
    
    delete left;
    delete right;
    
    return result;
  }
      
  IExpression *RPNExpressionFactory::createFunction(ISymbol sym) {
    if(trace) {
      cout <<"RPNEF: createFunction \"" << sym.getString() << "\"" << endl;
    }
    return new RPNExpression(sym.getString());
  }
      
  void RPNExpressionFactory::reverseAddSubExpression(IExpression *parent, IExpression *child) {
    RPNExpression *p = dynamic_cast<RPNExpression *>(parent);
    RPNExpression *c = dynamic_cast<RPNExpression *>(child);
    
    if(trace) {
      cout << "RPNEF: reverseAddSubExpression \"" << c->str << "\" ";
      cout << "to \"" << p->str << "\"" << endl;
    }
    
    p->str = c->str + " " + p->str;
     
    delete child;
  }

/*
 * end of RPNExpressionFactory class
 */
  
/*
 * class RPNSymbolDBAdapter implementation
 */

  bool RPNSymbolDBAdapter::isOperator(string& oper) {
    return true;
  }
  
  bool RPNSymbolDBAdapter::isFunction(string& func) {
    return true;
  }
      
  long RPNSymbolDBAdapter::getPriority(string& oper) {
    if("+" == oper || "-" == oper) {
      return 1;
    } else if("*" == oper || "/" == oper || "%" == oper) {
      return 2;
    } else if("**" == oper) {
      return 3;
    } 
    
    return 0;
  }
  
  OperatorAssociativity RPNSymbolDBAdapter::getAssociativity(string& oper) {
    return "**" == oper ? RIGHT: LEFT;
  }
  
/*
 * end of RPNSymbolDBAdapter class
 */

