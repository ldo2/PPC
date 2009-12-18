#include <compiler_example/rpn_example.hpp>
#include <iostream>

/*
 * class RPNExpression implementation
 */
       
  RPNExpression::RPNExpression() {}
  RPNExpression::RPNExpression(string _str) : str(_str) { 
    cout << "create RPNExpression: " << str << endl; 
  }
  //RPNExpression::RPNExpression(string& _str) : str(_str) {}
  RPNExpression::~RPNExpression(void) {}
  
  /*
  ostream& operator << (ostream& os, RPNExpression *e) {
    os << e->str;
  }
  */

/*
 * end of RPNExpression class
 */

/*
 * class RPNExpressionFactory implementation
 */

  RPNExpressionFactory::RPNExpressionFactory(void) {}
      
  IExpression *RPNExpressionFactory::createExpression(ISymbol sym) {
    return new RPNExpression(sym.getString());
  }
      
  IExpression *RPNExpressionFactory::createUnitaryOperator(ISymbol sym, IExpression *child) {
    RPNExpression *result = new RPNExpression(dynamic_cast<RPNExpression *>(child)->str + " " + sym.getString());
    delete child;
    return result;
  }
  
  IExpression *RPNExpressionFactory::createBinaryOperator(ISymbol sym, IExpression *left, IExpression *right) {
    RPNExpression *result = new RPNExpression(dynamic_cast<RPNExpression *>(left)->str + " " + dynamic_cast<RPNExpression *>(right)->str + " " + sym.getString());
    
    delete left;
    delete right;
    
    return result;
  }
      
  IExpression *RPNExpressionFactory::createFunction(ISymbol sym) {
    return new RPNExpression(sym.getString());
  }
      
  void RPNExpressionFactory::reverseAddSubExpression(IExpression *parent, IExpression *child) {
    RPNExpression *p = dynamic_cast<RPNExpression *>(parent);
    RPNExpression *c = dynamic_cast<RPNExpression *>(child);
    
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

