#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    // Implement me!
    
  }
  int n;
  
  void init (int num_threads) {
    // Implement me!
    n = num_threads;
    level = new atomic_int[num_threads];
    victim = new atomic_int[num_threads];

    for (int i = 0; i < n; i ++) {
      level[i].store(0); // = 0;
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    int me = thread_id;

    for (int i = 1; i < n; i ++) {
      level[me].store(i); // = i;
      victim[i].store(me); // = me;
      for (int k = 0; k < n; k ++) {
	if (k != me) {
	  while (level[k].load() >= i && victim[i].load() == me) {
	   this_thread::yield;
	  }
	}
      }
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    level[thread_id].store(0); // = 0;
  }

 private:
  // Give me some private variables!
  atomic_int *victim;
  atomic_int *level;
};
