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
    max = new atomic_int[n];
    
    
    for (int i = 0; i < n; i ++) {
      flag[i].store(false); // = false;
      label[i].store(0); // = 0;
      max[i].store(0); // = 0;
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    flag[thread_id].store(true); // = true;

    max[thread_id].store(label[0].load()); // = label[0].load();
    for (int i = 1; i < n; i ++) {
      if (label[i].load() > max[thread_id].load()) {
	max[thread_id].store(label[i].load()); // = label[i].load();
      }
    }
    label[thread_id].store(max[thread_id].load()); // = max[thread_id];

    for (int k = 0; k < n; k++) {
      if ( k != thread_id) {
	while ((flag[k].load() && label[k].load() < label[thread_id].load()) || (flag[k].load() && label[k].load() == label[thread_id].load() && k < thread_id)) {}
      }
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    //printf("UNLOCK\n\n");
    flag[thread_id].store(false); // = false;
  }

 private:
  // Give me some private variables!
  atomic_bool *flag;
  atomic_int *label;
  atomic_int *max;
};
