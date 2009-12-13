#include <thread/mutex.hpp>

#include <cstring>

#include <error/exception.hpp>

using namespace MSIUError;

namespace MSIUThreads {

 /*
  * class Mutex implementation
  */

    Mutex::Mutex(void) {
      int result;
      
      memset(&mutex, 0, sizeof(pthread_mutex_t));
      
      result = pthread_mutex_init(&mutex, NULL);
      
      if(result != 0) {
        throw SystemCallError("pthread_mutex_init", result, __FUNCTION__);
      }
    }
    
    Mutex::~Mutex(void) {
      int result;
      
      result = pthread_mutex_destroy(&mutex);
      
      if(result != 0) {
        throw SystemCallError("pthread_mutex_destroy", result, __FUNCTION__);
      }
    }
      
    void Mutex::lock(void) {
      int result;
      
      result = pthread_mutex_lock(&mutex);
      
      if(result != 0) {
        throw SystemCallError("pthread_mutex_lock", result, __FUNCTION__);
      }
    }
    
    bool Mutex::trylock(void) {
      int result;
      
      result = pthread_mutex_trylock(&mutex);
      
      return (result == 0);
    }
    
    void Mutex::unlock(void) {
      int result;
      
      result = pthread_mutex_unlock(&mutex);
      
      if(result != 0) {
        throw SystemCallError("pthread_mutex_unlock", result, __FUNCTION__);
      }
    }

 /*
  * end of Mutex class
  */

 /*
  * class MutexLocking implementation
  */

    MutexLocking::MutexLocking(Mutex & _mutex) : mutex(_mutex) {
      mutex.lock();
    }
    
    MutexLocking::~MutexLocking(void) {
      mutex.unlock();
    }
   
 /*
  * end of MutexLocking class
  */
  
};

