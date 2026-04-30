/* Part of ADS1
   University of Vienna
   Author: Sagar Kale.
   Test code generated with the help of an LLM.
   NOTE: THE MAIN PURPOSE OF THIS CODE IS DEMONSTRATION OF DATA STRUCTURE
   CONCEPTS. THIS CODE MAY NOT NECESSARILY SHOW BEST SOFTWARE ENGINEERING
   PRACTICES!
*/

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

struct Node {
  int data = 0;
  Node *next = nullptr;
};

class LinkedList {
    Node *start = nullptr;
  public:
    LinkedList() {

    }
    void insert(int value) {
      Node *previousNode = start;
      start = new Node;

      start->data = value;
      start->next = previousNode;
    }
    int remove() {
      int val = start->data;
      auto update = start->next;
      delete start;
      start = update;
      return val;
    }
    bool is_empty() {
      return !start;
    }
    ~LinkedList() {
      while (!(this->is_empty()))
        this->remove();
    }
};

class my_stack {
    LinkedList data;
  public:
    my_stack(){

    }
    void push(int value) {
      this->data.insert(value);
    }
    int pop() {
      return this->data.remove();
     }
    bool is_empty() { 
      return this->data.is_empty();
     }
};

void test_stack() {
  my_stack ms;
  std::stack<int> s;
  std::srand(std::time(0));
  int num_elements = std::rand() % 100000 + 1;

  // Push elements
  for (int i = 0; i < num_elements; ++i) {
    int value = std::rand();
    ms.push(value);
    s.push(value);
  }

  // std::cout << ms.get_first() << std::endl
  //           << ms.get_second() << std::endl;
  // Pop elements and verify
  while (!s.empty()) {
    assert(ms.pop() == s.top());
    s.pop();
  }
  assert(ms.is_empty() == s.empty());
}

void test_stack_mixed() {
  my_stack ms;
  std::stack<int> s;
  std::srand(std::time(0));
  int num_operations = std::rand() % 100000 + 1;

  for (int i = 0; i < num_operations; ++i) {
    int operation = std::rand() % 2; // 0 for push, 1 for pop
    if (operation == 0 || s.empty()) {
      int value = std::rand();
      ms.push(value);
      s.push(value);
    } else {
      assert(ms.pop() == s.top());
      s.pop();
    }
  }
  assert(ms.is_empty() == s.empty());
}

int main() {
  test_stack();
  test_stack_mixed();
  std::cout << "Stack tests passed!" << std::endl;
  return 0;
}
