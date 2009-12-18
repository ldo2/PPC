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
  
  string& ISymbol::getString(void) {
    return str;
  }
  
  bool ISymbol::canAppendChar(char c) {
    return false;
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
    return Compiler::charType(c) == DIGIT_CHAR;
  }

 /*
  * end of NumberSymbol class
  */
  
 /*
  * class FunctionSymbol implementation
  */
  
  FunctionSymbol::FunctionSymbol(SymbolType _type) : ISymbol(_type) {}

  FunctionSymbol::FunctionSymbol() : ISymbol(FUNCTION), argumentCount(0) {}
      
  bool FunctionSymbol::canAppendChar(char c) {
    CharType ct = Compiler::charType(c);
    return ct == LETTER_CHAR || ct == DIGIT_CHAR;
  }

  int FunctionSymbol::getArgumentCount(void) {
    return argumentCount;
  }
  
  void FunctionSymbol::addArgument(void) {
    argumentCount += 1;
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
    return Compiler::charType(c) == OPERATOR_CHAR;
  }

  bool operator<<(const OperatorSymbol& a, const OperatorSymbol& b) {
    if(a.associativity == NON && b.associativity == NON ) {
      // throw exception here
    }
    return (b.associativity == LEFT && a.priority <= b.priority) || 
            (b.associativity == RIGHT && a.priority < b.priority);
  }

 /*
  * end of OperatorSymbol class
  */
  
 /*
  * class BracketSymbol implementation
  */


  BracketSymbol::BracketSymbol(SymbolType _type) : ISymbol(_type) {}


  BracketSymbol::BracketSymbol() : ISymbol(BRACKET), bracketType(ROUND), isOpen(true) {}
  
  BracketSymbol::BracketSymbol(char c) : ISymbol(BRACKET), bracketType(ROUND), isOpen(false) {
    switch(c) {
      case '(':
        isOpen = true;
      case ')':
        bracketType = ROUND;
        break;
      case '[':
        isOpen = true;
      case ']':
        bracketType = SQUARE;
        break;
      case '{':
        isOpen = true;
      case '}':
        bracketType = CURLY;
        break;
      default:
        /* throw some error here ! */
        ;
    }
  }
  
  BracketSymbol::BracketSymbol(BracketType _bt) : ISymbol(BRACKET), bracketType(_bt) {}
      
      
  bool BracketSymbol::canAppendChar(char c) {
    return false;
  }
  
  void BracketSymbol::appendChar(char c) {
    /* throw some error here ! */
  }
  
  BracketType BracketSymbol::getBracketType(void) {
    return bracketType;
  }
  
  bool BracketSymbol::getIsOpen(void) {
    return isOpen;
  }
  
  bool BracketSymbol::isCloseFor(BracketSymbol *b) {
    if(b ==  NULL) {
      return false;
    }
    return !isOpen && b->getIsOpen() && bracketType == b->getBracketType();
  }

 /*
  * end of BracketSymbol class
  */
};

