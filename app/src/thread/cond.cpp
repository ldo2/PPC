#include <thread/cond.hpp>

#include <cstring>

#include <error/exception.hpp>

using namespace MSIUError;

namespace MSIUThreads {
 /*
  * class ConditionVariable implementation
  */
  
    ConditionVariable::ConditionVariable(void) {
      int result;
      
      memset(&cond, 0, sizeof(pthread_cond_t));
      
      result = pthread_cond_init(&cond, NULL);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_init", result, __FUNCTION__);
      }
    }
    
    ConditionVariable::~ConditionVariable(void) {
      int result;
      
      result = pthread_cond_destroy(&cond);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_destroy", result, __FUNCTION__);
      }
    }
      
    void ConditionVariable::wait(Mutex & mutex) {
      int result;
      
      result = pthread_cond_wait(&cond, &mutex.mutex);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_wait", result, __FUNCTION__);
      }
    }
    
    void ConditionVariable::timedwait(Mutex & mutex, long utime) {
      int result;
      struct timespec timeout;
      
      memset(&timeout, 0, sizeof(struct timespec));
      timeout.tv_sec = utime;
      
      result = pthread_cond_timedwait(&cond, &mutex.mutex, &timeout);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_timedwait", result, __FUNCTION__);
      }
    }
    
    void ConditionVariable::signal(void) {
      int result;
      
      result = pthread_cond_signal(&cond);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_signal", result, __FUNCTION__);
      }
    }
    
    void ConditionVariable::broadcast(void) {
      int result;
      
      result = pthread_cond_broadcast(&cond);
      
      if(result != 0) {
        throw SystemCallError("pthread_cond_broadcast", result, __FUNCTION__);
      }
    }
  
 /*
  * end of ConditionVariable class
  */


};

