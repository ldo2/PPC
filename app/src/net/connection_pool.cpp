#include <cstdio>
#include <cstring>
#include <iostream>

#include <net/connection_pool.hpp>

using namespace std;

namespace MSIUNet {
  
 /*
  * interface IConnectionHandler 
  */
  
   void *IConnectionHandler::handle(void *args) {
     return NULL;
   }
  
 /*
  * end of IConnectionHandler interface
  */
  
 /*
  * class ConnectionPool implementation
  */

  ConnectionPool::ConnectionPool(int max_connections) {
    if (max_connections <= 0) {
      max_connections = STD_CONNECTION_COUNT;
    }

    free_threads = new list<ConnectionThread *>;
    
    while (max_connections-- > 0) {
      new ConnectionThread(this);
    }
  }
  
  ConnectionPool::~ConnectionPool(void) { 
    while (!free_threads->empty()) {
      delete free_threads->front();
      free_threads->pop_front();
    }
    
    delete free_threads;
  }
  
  int ConnectionPool::run(IConnectionHandler *handler, void *args = NULL) {
    ConnectionThread *connection;
    volatile MSIUThreads::MutexLocking locking(mutex);
    
    if (free_threads->empty()) {
      // cout << "no threads" << endl;
      return -1;
    }
    
    connection = free_threads->front();
    free_threads->pop_front();

    connection->handler = handler;
    connection->args = args;
    connection->startSem->signal();

    return 0;
  }
  
 /*
  * end of ConnectionPool class
  */

 /*
  * class ConnectionThread implementation
  */
  
  ConnectionThread::ConnectionThread(ConnectionPool *_pool) {
    pthread_attr_t attr;
    volatile MSIUThreads::MutexLocking locking(_pool->mutex);
    
    memset(&thread, 0, sizeof(pthread_t));

    pool = _pool;
    
    startSem = new ConnectionSemaphore(0);
    readySem = new ConnectionSemaphore(0);
    handler = NULL;

    pool->free_threads->push_back(this);

    pthread_attr_init(&attr);
    pthread_create(&thread, &attr, &ConnectionThread::startCallback, this);
    pthread_attr_destroy(&attr);
  }
  
  ConnectionThread::~ConnectionThread(void) {
    delete startSem;
    delete readySem;
  }
  
  void ConnectionThread::start(void) {
    pool->mutex.lock();
    while (true) { 
      startSem->wait(pool);
      if (handler == NULL) {
        break;
      }
      
      pool->mutex.unlock();
      handler->handle(args);

      pool->mutex.lock();
      
      handler = NULL;
      args = NULL;
      
      pool->free_threads->push_back(this);

      /* readySem->signal(); */
    }
    // readySem->signal();
    pool->mutex.unlock();
  }
  
  void ConnectionThread::stop(void) {
    handler = NULL;
    startSem->signal();
  }
  
  void *ConnectionThread::startCallback(void *cThread) {
    if (cThread) {
      ((ConnectionThread *) cThread)->start();
    }
    return NULL;
  }
  
 /*
  * end of ConnectionThread class
  */
  
 /*
  * class ConnectionSemaphore implementation
  */
  
  ConnectionSemaphore::ConnectionSemaphore(int initValue) : count(initValue) {}
  
  ConnectionSemaphore::~ConnectionSemaphore(void) {}
  
  void ConnectionSemaphore::signal(void) {
    count += 1;
    cond.signal();
  }
  
  void ConnectionSemaphore::wait(ConnectionPool *pool) {
    while (count == 0) {
      cond.wait(pool->mutex);
    }
    count -= 1;
  }

 /*
  * end of ConnectionSemaphore class
  */
   
};

