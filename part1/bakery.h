#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    // Implement me!
  }
  
  void init (int num_threads) {
    // Implement me!
    counter = 0;
    currently_serving = 0;
  }
  
  void lock(int thread_id) {
    // Implement me!
    int my_num = atomic_fetch_add(&counter, 1);
    while (currently_serving.load() != my_num) {
      this_thread::yield;
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    currently_serving ++;
  }

 private:
  // Give me some private variables!
  atomic_int counter;
  atomic_int currently_serving;
};
