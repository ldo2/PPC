#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <iostream>
#include <string>

using std::string;
using std::ostream;


namespace MSIUError {
	class Exception {
	  protected:
		  explicit Exception(const char* _name, const string& str);
	  	explicit Exception(const char* _name);
		
	  	const char *name;
	  	string cause;
  	public:
	  	explicit Exception(const string& str); 
		  explicit Exception();
		  virtual ~Exception() throw();
		  virtual const char* info() const throw();
		  
		  friend ostream& operator << (ostream& os, Exception& e);
	};
	
	class FatalError : public Exception {
	  protected:
	  	explicit FatalError(const char* _name, const string& str) : Exception(_name, str) {}
	  	explicit FatalError(const char* _name) : Exception(_name) {}
  	public:
	  	explicit FatalError(const string& str) : Exception("FatalError", str) {}
	  	explicit FatalError() : Exception("FatalError") {}
	  	virtual ~FatalError() throw() {}
	};
	
	class NoMemoryError : public Exception {
	  protected:
	  	explicit NoMemoryError(const char* _name, const string& str) : Exception(_name, str) {}
	  	explicit NoMemoryError(const char* _name) : Exception(_name) {}
  	public:
	  	explicit NoMemoryError(const string& str) : Exception("NoMemoryError", str) {}
	  	explicit NoMemoryError() : Exception("NoMemoryError") {}
	  	virtual ~NoMemoryError() throw() {}
	};
	
	class InternalError : public Exception {
	  protected:
	  	explicit InternalError(const char* _name, const string& str) : Exception(_name, str) {}
	  	explicit InternalError(const char* _name) : Exception(_name) {}
	  public:
	  	explicit InternalError(const string& str) : Exception("InternalError", str) {}
	  	explicit InternalError() : Exception("InternalError") {}
	  	virtual ~InternalError() throw() {}
	};
	
	class NotImplementedError : public InternalError {
  	protected:
	  	explicit NotImplementedError(const char* _name, const string& str) : InternalError(_name, str) {}
 	  	explicit NotImplementedError(const char* _name) : InternalError(_name) {}
  	public:
	  	explicit NotImplementedError(const string& str) : InternalError("NotImplementedError", str) {}
	  	explicit NotImplementedError() : InternalError("NotImplementedError") {}
	   	virtual ~NotImplementedError() throw() {}
	};
	
	class StandartError : public Exception {
	  protected:
	  	explicit StandartError(const char* _name, const string& str) : Exception(_name, str) {}
	  	explicit StandartError(const char* _name) : Exception(_name) {}
  	public:
  		explicit StandartError(const string& str) : Exception("StandartError", str) {}
	  	explicit StandartError() : Exception("StandartError") {}
	  	virtual ~StandartError() throw() {}
	};
	
	class IOError : public StandartError {
	  protected:
	  	explicit IOError(const char* _name, const string& str) : StandartError(_name, str) {}
	  	explicit IOError(const char* _name) : StandartError(_name) {}
	  public:
	  	explicit IOError(const string& str) : StandartError("IOError", str) {}
	  	explicit IOError() : StandartError("IOError") {}
	  	virtual ~IOError() throw() {}
	};
	
	class EOFError : public IOError {
  	protected:
	   	explicit EOFError(const char* _name, const string& str) : IOError(_name, str) {}
	  	explicit EOFError(const char* _name) : IOError(_name) {}
  	public:
	  	explicit EOFError(const string& str) : IOError("EOFError", str) {}
  		explicit EOFError() : IOError("EOFError") {}
  		virtual ~EOFError() throw() {}
	};
	
	class InvalidArgument : public StandartError {
  	protected:
	  	explicit InvalidArgument(const char* _name, const string& str) : StandartError(_name, str) {}
	  	explicit InvalidArgument(const char* _name) : StandartError(_name) {}
  	public:
	  	explicit InvalidArgument(const string& str) : StandartError("InvalidArgument", str) {}
	  	explicit InvalidArgument() : StandartError("InvalidArgument") {}
	  	virtual ~InvalidArgument() throw() {}
	};
	
	class TypeError : public StandartError {
  	protected:
  		explicit TypeError(const char* _name, const string& str) : StandartError(_name, str) {}
  		explicit TypeError(const char* _name) : StandartError(_name) {}
	  public:
	  	explicit TypeError(const string& str) : StandartError("TypeError", str) {}
	  	explicit TypeError() : StandartError("TypeError") {}
	  	virtual ~TypeError() throw() {}
	};
	
	class RuntimeError : public StandartError {
	  protected:
	  	explicit RuntimeError(const char* _name, const string& str) : StandartError(_name, str) {}
	  	explicit RuntimeError(const char* _name) : StandartError(_name) {}
	  public:
	  	explicit RuntimeError(const string& str) : StandartError("RuntimeError", str) {}
	  	explicit RuntimeError() : StandartError("RuntimeError") {}
	  	virtual ~RuntimeError() throw() {}
	};
	
	class SystemCallError : public StandartError {
  	protected:
	  	explicit SystemCallError(const char* _name, const string& str) : StandartError(_name, str), syscall(""), errnum(0) {}
	  	explicit SystemCallError(const char* _name) : StandartError(_name), syscall(""), errnum(0) {}
	  	
	  	const char *syscall;
	  	int errnum;
  	public:
		  explicit SystemCallError(const string& str) : StandartError("SystemCallError", str), syscall(""), errnum(0) {}
		  explicit SystemCallError(const char *_syscall, int _errnum, const char *from, const string& str);
		  explicit SystemCallError(const char *_syscall, int _errnum, const char *from);
		  explicit SystemCallError(const char *_syscall, int _errnum, const string& str);
		  explicit SystemCallError(const char *_syscall, int _errnum);
		  explicit SystemCallError() : StandartError("SystemCallError"), syscall(""), errnum(0) {}
		  virtual ~SystemCallError() throw() {}
	};
	
};

#endif /* _EXCEPTION_HPP_ */
