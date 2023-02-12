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
    
    flag = new atomic_bool[n];
    label = new atomic_int[n];
    
    
    for (int i = 0; i < n; i ++) {
      flag[i] = false;
      label[i] = 0;
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    flag[thread_id] = true;

    int tmp = label[0];
    for (int i = 1; i < n; i ++) {
      if (label[i] > tmp) {
	tmp = label[i];
      }
    }
    label[thread_id] = tmp;

    for (int k = 0; k < n; k++) {
      while (flag[k] && label[k] < label[thread_id] | ( flag[k] && label[k] == label[thread_id] && k < thread_id)) {}
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    //printf("UNLOCK\n\n");
    flag[thread_id] = false;
  }

 private:
  // Give me some private variables!
  atomic_bool *flag;
  atomic_int *label;
};
