#pragma once

#include <atomic>
#include <mutex>
using namespace std;

class rw_mutex {
 public:
  rw_mutex() {
    // Implement me!
    num_readers = 0;
    writer = false;
    w_req = 0;
  }

  void lock_reader() {
    // Implement me!
    //printf("READER req\n");
    bool acquired = false;
    while (!acquired) {
      internal_mutex.lock();
      if (!writer && w_req == 0) {
	acquired = true;
	num_readers ++;
      }
      internal_mutex.unlock();
    }
  }
  
  void unlock_reader() {
    // Implement me!
    internal_mutex.lock();
    num_readers --;
    internal_mutex.unlock();
  }

  
  void lock() {
    // Implement me!
    //printf("Writer req\n");
    bool acquired = false;
    w_req ++; 
    //printf("OUT OF WRITE MUTEX 1\n");
    while (!acquired) {
      //printf("In write while, W_REQ = %d\n", w_req.load());
      internal_mutex.lock();
      //w_req ++;
      if (!writer && num_readers == 0) {
	acquired = true;
	writer = true;
	w_req --;
      }
      internal_mutex.unlock();
    }
  }
  
  void unlock() {
    // Implement me!
    internal_mutex.lock();
    writer = false;
    internal_mutex.unlock();
  }

 private:
  // Give me some private variables!
  int num_readers;
  bool writer;
  mutex internal_mutex;
  atomic_int w_req;
};
