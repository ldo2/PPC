#ifndef _SC_SYMBOLS_HPP_
#define _SC_SYMBOLS_HPP_

#include <string>

#include <stack_compiler/types.hpp>
#include <stack_compiler/compiler.hpp>

using std::string;

namespace StackCompiler {

  class ISymbol {
    protected:
      ISymbol(SymbolType _type);
    
      SymbolType type;
      string str;
      
    public:
      ISymbol();
      
      virtual ~ISymbol(void);
      
      SymbolType getType(void);
      string& getString(void);
      
      virtual bool canAppendChar(char c);
      virtual void appendChar(char c);
  };

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

      int argumentCount;
    public:
      FunctionSymbol();
      
      virtual bool canAppendChar(char c);
      
      int getArgumentCount(void);
      void addArgument(void);
  };
  
  class OperatorSymbol : public ISymbol {
    protected:
      OperatorSymbol(SymbolType _type);

    public:
      /* there are no good to use this public fields *WALL* */
      long priority;
      OperatorAssociativity associativity;
      OperatorType operatorType;
    
      OperatorSymbol();
      
      virtual bool canAppendChar(char c);
      
      void addArgument(void);
      
      friend bool operator<<(const OperatorSymbol& a, const OperatorSymbol& b);
  };
  
  class BracketSymbol : public ISymbol {
    protected:
      BracketSymbol(SymbolType _type);

      BracketType bracketType;
      bool isOpen;
    public:
      BracketSymbol();
      BracketSymbol(char c);
      BracketSymbol(BracketType _bt);
      
      virtual bool canAppendChar(char c);
      virtual void appendChar(char c);
      
      BracketType getBracketType(void);
      bool getIsOpen(void);
      
      bool isCloseFor(BracketSymbol *b);
  };

};

#endif /* _SC_SYMBOLS_HPP_ */

