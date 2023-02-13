#include <mutex>
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
    start = NULL;
  }
  
  int pop() {
    //printf("pop req\n")
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

    //m.lock();
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
    m.lock();
    //printf("peek req\n");
    if (start == NULL) {
      m.unlock();
      return -1;
    }
    
    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }
    int ret = current->data;
    m.unlock();
    return ret;
  }
  
  void push(int p) {
    //printf("push req\n");
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

 private:
  Llist_node *start;
  mutex m;
};

