#ifndef _SC_TYPES_HPP_
#define _SC_TYPES_HPP_

namespace StackCompiler {

  enum OperatorAssociativity;
  enum OperatorType;
  
  enum NumberType;
  
  enum SymbolType;
  enum CharType;
  
  enum BracketType;
  
  enum OperatorAssociativity {
    LEFT,
    RIGHT,
    NON
  };
  
  enum OperatorType {
    UNITARY = 1,
    BINARY = 2
  };
  
  enum NumberType {
    INTEGER,
    FIXED_POINT,
    FLOATING_POINT
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
    STRING,
    BRACKET,
    UNDEFINED
  };
  
};

#endif /* _SC_TYPES_HPP_ */

