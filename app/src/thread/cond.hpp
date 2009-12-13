#ifndef __COND_VAR_HPP__
#define __COND_VAR_HPP__

#include <pthread.h>

#include <thread/msiu_threads.hpp>
#include <thread/mutex.hpp>

namespace MSIUThreads {

  class ConditionVariable {
    public:
      ConditionVariable(void);
      ~ConditionVariable(void);
      
      void wait(Mutex & mutex);
      void timedwait(Mutex & mutex, long utime);
      void signal(void);
      void broadcast(void);
    private:
      pthread_cond_t cond;
  };

};

#endif /* __COND_VAR_HPP__ */

