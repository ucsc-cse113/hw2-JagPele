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
  }

  void lock_reader() {
    // Implement me!
    bool acquired = false;
    while (!acquired) {
      internal_mutex.lock();
      if (!writer) {
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
    bool acquired = false;
    while (!acquired) {
      internal_mutex.lock();
      if (!writer && num_readers == 0) {
	acquired = true;
	writer = true;
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
};
