#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__
#include <pthread.h>

#include "msiu_threads.hpp"

namespace MSIUThreads {

  class Mutex {
    public:
      Mutex(void);
      ~Mutex(void);
      
      void lock(void);
      bool trylock(void);
      void unlock(void);
      
    private:
      pthread_mutex_t mutex;
      
    friend class ConditionVariable;
  };
  
  class MutexLocking {
    public:
      MutexLocking(Mutex & _mutex);
      ~MutexLocking(void);
    private:
      Mutex & mutex;
  };

};

#endif /* __MUTEX_HPP__ */

