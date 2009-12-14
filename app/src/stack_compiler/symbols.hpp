#ifndef _SC_SYMBOLS_HPP_
#define _SC_SYMBOLS_HPP_

#include <string>

#include <stack_compiler/types.hpp>
#include <stack_compiler/compiler.hpp>

using std::string;

namespace StackCompiler {

  class NumberSymbol : public ISymbol {
    protected:
      NumberSymbol(SymbolType _type);
    
      NumberType numType;

    public:
      NumberSymbol();
      
      virtual bool canAppendChar(char c);
  };
  
  /*
  class StringSymbol : public ISymbol {
    
  };
  */
  
  class FunctionSymbol : public ISymbol {
    protected:
      FunctionSymbol(SymbolType _type);

    public:
      FunctionSymbol();
      
      virtual bool canAppendChar(char c);
  };
  
  class OperatorSymbol : public ISymbol {
    protected:
      OperatorSymbol(SymbolType _type);

    public:
      OperatorSymbol();
      
      virtual bool canAppendChar(char c);
  };
  
  class BracketSymbol : public ISymbol {
    protected:
      BracketSymbol(SymbolType _type);

      BracketType bracketType;
    public:
      BracketSymbol();
      BracketSymbol(char c);
      BracketSymbol(BracketType _bt);
      
      virtual bool canAppendChar(char c);
      virtual void appendChar(char c);
  };

};

#endif /* _SC_SYMBOLS_HPP_ */

