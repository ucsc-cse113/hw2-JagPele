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
    ticketNum = 0;
    curServing = 1;
    
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
    ticketNum ++;
    label[thread_id] = ticketNum;

    while (label[thread_id] != curServing.load()) {}
    for (int i = 0; i < thread_id; i ++) {
      if (flag[i] && label[i] == curServing.load()) {
	while (flag[i]){}
      }
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    flag[thread_id] = false;

    int tmp = curServing.load();
    tmp ++;
    curServing.store(tmp);
  }

 private:
  // Give me some private variables!
  atomic_bool *flag;
  atomic_int *label;
  atomic_int curServing;
  int ticketNum;
};
