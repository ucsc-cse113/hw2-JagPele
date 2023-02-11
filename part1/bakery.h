#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    // Implement me!
  }

  int n;
  int ticketNum;
  
  void init (int num_threads) {
    // Implement me!
    n = num_threads;
    ticketNum = 0;
    
    flag = new atomic_bool[n];
    label = new atomic_int[n];
    
    
    for (int i = 0; i < n; i ++) {
      flag[i] = false; label[i] = 0;
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    flag[thread_id] = true;
    ticketNum ++;
    label[thread_id] = ticketNum;

    for (int i = 0; i < n; i ++) {
      if (i != thread_id) {
	while (label[i] < label[thread_id]){}
	if (label[i] == label[thread_id]) {
	  while (i < thread_id){}
	}
      }
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    flag[thread_id] = false;
  }

 private:
  // Give me some private variables!
  atomic_bool *flag;
  atomic_int *label;
};
