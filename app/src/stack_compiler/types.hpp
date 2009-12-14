#ifndef _SC_TYPES_HPP_
#define _SC_TYPES_HPP_

namespace StackCompiler {
  
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
    OPEN_BRACKET_CHAR,
    CLOSE_BRACKET_CHAR,
    SEPARATOR_CHAR,
    STRING_BRACKET_CHAR,
    OPERATOR_CHAR,
    LETTER_CHAR,
    DIGIT_CHAR,
    SPACE_CHAR,
    OTHER_CHAR
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

