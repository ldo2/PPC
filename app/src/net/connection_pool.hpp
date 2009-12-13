#ifndef __CONNECTION_POOL_HPP__
#define __CONNECTION_POOL_HPP__
#include <list>

#include <pthread.h>

#include <thread/threads.hpp>

#define STD_CONNECTION_COUNT (0x10)

using namespace std;

namespace MSIUNet {

  class ConnectionPool;
  class ConnectionSemaphore;
  class ConnectionThread;

  class IConnectionHandler {
    public:
      virtual void *handle(void *args);
  };

  class ConnectionPool {
    private:
      list<ConnectionThread *> *free_threads;
      MSIUThreads::Mutex mutex;

    public:
    
      ConnectionPool(int max_connections);
      ~ConnectionPool(void);
      
      int run(IConnectionHandler *handler, void *args);
      
      friend class ConnectionThread;
      friend class ConnectionSemaphore;
  };

  class ConnectionThread {
    private:
      pthread_t thread;
      ConnectionPool *pool;
      IConnectionHandler *handler;
      void *args;
      int runned;
      
      ConnectionSemaphore *startSem;
      ConnectionSemaphore *readySem;
    
    public:
    
      ConnectionThread(ConnectionPool *pool);
      ~ConnectionThread(void);
      
      void start(void);
      void stop(void);
      
      static void *startCallback(void *cThread);
    
      friend class ConnectionPool;
  };

  class ConnectionSemaphore {
    private:
      MSIUThreads::ConditionVariable cond;
      int count;
      
    public:
      
      ConnectionSemaphore(int initValue);
      ~ConnectionSemaphore(void);
      
      void signal(void);
      
      void wait(ConnectionPool *pool);
  };

}; /* namespace MSIUNet end */

#endif /* __CONNECTION_POOL_HPP__ */

