#include <shared_mutex>
using namespace std;

class Llist_node {
 public:  
  Llist_node(int d) {   
    data = d;
    next = NULL;
  }
  
  int data;
  Llist_node *next;
};

class CSE113_Stack {
 public:
  
  CSE113_Stack() {
    m.lock();
    start = NULL;
    m.unlock();
  }
  
  int pop() {
    m.lock();
    if (start == NULL) {
      m.unlock();
      return -1;
    }

    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      m.unlock();
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL) {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;
    m.unlock();
    return ret;
  }

  
  int peek() {
    m.lock_shared();
    if (start == NULL) {
      m.unlock_shared();
      return -1;
    }
    
    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }
    int ret = current->data;
    m.unlock_shared();
    return ret;    
  }
  
  void push(int p) {
    m.lock();
    if (start == NULL) {

      start = new Llist_node(p);
      m.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new Llist_node(p);
    m.unlock();
  }

  void swaptop(int to_swap) {
    // Implement me!
    m.lock_shared();

    if (start == NULL) {
      m.unlock_shared();
      return;
    }
    
    Llist_node *cur = start;

    while(cur->next != NULL) {
      cur = cur->next;
    }

    if (cur->data == to_swap) {
      m.unlock_shared();
      return;
    }
    m.unlock_shared();
    
    m.lock();
    Llist_node *current =  start;
    while (current->next != NULL) {
      current = current->next;
    }
    current->data = to_swap;

    m.unlock();
    return;
    
  }

 private:
  Llist_node *start;
  shared_mutex m;
};
