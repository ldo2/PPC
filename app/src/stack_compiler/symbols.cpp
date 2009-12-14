#include <stack_compiler/symbols.hpp>
#include <stack_compiler/types.hpp>
#include <stack_compiler/compiler.hpp>

namespace StackCompiler {
 /*
  * interface ISymbol 
  */
  
  ISymbol::ISymbol(SymbolType _type) : type(_type) {}
  
  ISymbol::ISymbol() : type(UNDEFINED) {}
  
  ISymbol::~ISymbol(void) {}
  
  SymbolType ISymbol::getType(void) {
    return type;
  }
  
  string ISymbol::getString(void) {
    return str;
  }
  
  void ISymbol::appendChar(char c) {
    str += c; 
  }
  
 /*
  * end of ISymbol interface
  */
   
 /*
  * class NumberSymbol implementation
  */
  
  NumberSymbol::NumberSymbol(SymbolType _type) : ISymbol(_type) {}

  NumberSymbol::NumberSymbol() : ISymbol(NUMBER) {}
      
  bool NumberSymbol::canAppendChar(char c) {
    return Compiler.charType(c) == DIGIT;
  }

 /*
  * end of NumberSymbol class
  */
  
 /*
  * class FunctionSymbol implementation
  */
  
  FunctionSymbol::FunctionSymbol(SymbolType _type) : ISymbol(_type) {}

  FunctionSymbol::FunctionSymbol() : ISymbol(NUMBER) {}
      
  bool FunctionSymbol::canAppendChar(char c) {
    CharType ct = Compiler.charType(c)
    return ct == LETTER || ct == DIGIT;
  }

 /*
  * end of FunctionSymbol class
  */
  
 /*
  * class OperatorSymbol implementation
  */

  OperatorSymbol::OperatorSymbol(SymbolType _type) : ISymbol(_type) {}

  OperatorSymbol::OperatorSymbol() : ISymbol(OPERATOR)  {}
      
  bool OperatorSymbol::canAppendChar(char c) {
    return Compiler.charType(c) == OPERATOR;
  }

 /*
  * end of OperatorSymbol class
  */
  
 /*
  * class BracketSymbol implementation
  */


  BracketSymbol::BracketSymbol(SymbolType _type) : ISymbol(_type) {}


  BracketSymbol::BracketSymbol() : ISymbol(BRACKET), bracketType(ROUND) {}
  
  BracketSymbol::BracketSymbol(char c) : ISymbol(BRACKET), bracketType(ROUND) {
    switch(Compiler.charType(c)) {
      case LEFT_ROUND:
        bt = ROUND;
        break;
      case LEFT_SQUARE:
        bt = SQUARE;
        break;
      case LEFT_CURLY:
        bt = CURLY;
        break;
      default:
        /* throw some error here ! */
    }
  }
  
  BracketSymbol::BracketSymbol(BracketType _bt) : ISymbol(BRACKET), bracketType(_bt) {}
      
      
  bool BracketSymbol::canAppendChar(char c) {
    return false;
  }
  
  void BracketSymbol::appendChar(char c) {
    /* throw some error here ! */
  }

 /*
  * end of BracketSymbol class
  */
};

