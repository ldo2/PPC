#include <error/exception.hpp>

#include <cstring>

namespace MSIUError {
  
  /*
   * class Exception implementation
   */
  
    Exception::Exception(const char* _name, const string& str) : name(_name) {
			cause += name;
			cause += ": ";
			cause += str;
		}
		
		Exception::Exception(const char* _name) : name(_name), cause(_name) {}
		
		Exception::Exception(const string& str) : name("Exception") {
			cause += name;
			cause += ": ";
			cause += str;
		}
		
		Exception::Exception() : name("Exception"), cause("Exception") {}
  
    Exception::~Exception() throw() {}
  
    const char* Exception::info() const throw() { 
      return cause.c_str(); 
    }
    
    ostream& operator << (ostream& os, Exception& e) {
      return os << e.info() << std::endl;
    }
    
  /*
   * end of Exception class
   */
   
  /*
   * class SystemCallError implementation
   */
   
     SystemCallError::SystemCallError(const char *_syscall, int _errnum, const string& str) : StandartError("SystemCallError"), syscall(_syscall), errnum(_errnum) {
       cause += ": in <";
       cause += syscall;
       cause += ">: ";
       cause += strerror(errnum);
       cause += ": ";
       cause += str;
     }
     
     SystemCallError::SystemCallError(const char *_syscall, int _errnum) : StandartError("SystemCallError"), syscall(_syscall), errnum(_errnum) {
       cause += ": in <";
       cause += syscall;
       cause += ">: ";
       cause += strerror(errnum);
     } 
     
     SystemCallError::SystemCallError(const char *_syscall, int _errnum, const char *from, const string& str): StandartError("SystemCallError"), syscall(_syscall), errnum(_errnum) {
       cause += ": in <";
       cause += syscall;
       cause += "> from <";
       cause += from;
       cause += ">: ";
       cause += strerror(errnum);
       cause += ": ";
       cause += str;
     }
     
		 SystemCallError::SystemCallError(const char *_syscall, int _errnum, const char *from): StandartError("SystemCallError"), syscall(_syscall), errnum(_errnum) {
       cause += ": in <";
       cause += syscall;
       cause += "> from <";
       cause += from;
       cause += ">: ";
       cause += strerror(errnum);
     }
   
  /*
   * end of SystemCallError class
   */
};
