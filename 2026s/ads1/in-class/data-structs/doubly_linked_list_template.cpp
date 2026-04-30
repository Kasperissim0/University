/* Part of ADS1
   University of Vienna
   Author: Sagar Kale and Niklas Hahn.
   Test code generated with the help of an LLM.
   NOTE: THE MAIN PURPOSE OF THIS CODE IS DEMONSTRATION OF DATA STRUCTURE
   CONCEPTS. THIS CODE MAY NOT NECESSARILY SHOW BEST SOFTWARE ENGINEERING
   PRACTICES!
*/

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <queue>

struct Node {
  int data;
  Node *previous = nullptr, *next = nullptr;
  auto output(std::ostream& o) const {
    std::stringstream out;
    out << "- Value: " << data << std::endl
        << "- Located At: " << this << std::endl
        << "  Pointing To: " << std::endl
        << "  - Forward: " << next << std::endl
        << "  - Back: " << previous << std::endl;
    return out.str();
  }
};
struct Sentinel {
  Node *ptr = nullptr;
};

class DoublyLinkedList {
    Sentinel head, tail;
    size_t amount = 0;
  public:
    DoublyLinkedList() {
    }
    void insert_front(int value) {
      Node *n = new Node,     *previousFirstNode = head.ptr;
      if (this->is_empty())   tail.ptr = n;
      else                    n->next = previousFirstNode;
                              head.ptr = n;
      if (previousFirstNode)  previousFirstNode->previous = n;
                              n->data = value;
      ++amount;
    }
    void insert_back(int value) {
      Node *n = new Node,     *previousLastNode = tail.ptr;
      if (this->is_empty())   head.ptr = n;
      else                    n->previous = previousLastNode;
                              tail.ptr = n;
      if (previousLastNode)   previousLastNode->next = n;
                              n->data = value;
      ++amount;
    }
    int remove_front() { if (this->is_empty()) throw std::runtime_error("List Is Empty, Can't Delete");
      auto data = head.ptr->data; // TODO improve
      Node *newFirst = head.ptr->next;
      if (newFirst) delete newFirst->previous, newFirst->previous = nullptr;
      else assert(head.ptr == tail.ptr), delete ((rand() % 2) ? head.ptr : tail.ptr);
      head.ptr = newFirst;
      if (!head.ptr) tail.ptr = head.ptr;
      return --amount, data;
     }
    int remove_back() { if (this->is_empty()) throw std::runtime_error ("List Is Empty, Can't Delete");
      auto data = tail.ptr->data; // TODO improve
      Node *newLast = tail.ptr->previous;
      if (newLast) delete newLast->next, newLast->next = nullptr;
      else assert(head.ptr == tail.ptr), delete ((rand() % 2) ? head.ptr : tail.ptr);
      tail.ptr = newLast;
      if (!tail.ptr) head.ptr = tail.ptr;
      return --amount, data;
    }
    bool is_empty() {
      assert(static_cast<bool>(head.ptr) == (head.ptr == nullptr) || static_cast<bool>(head.ptr) == !(head.ptr == nullptr));
      assert((static_cast<bool>(head.ptr)) == (static_cast<bool>(tail.ptr)));
      assert((amount == 0) || (amount == 1) || (head.ptr != tail.ptr));
      return !amount;
     }
    ~DoublyLinkedList() {
      while (!this->is_empty()) ((rand() % 2) ? this->remove_back() : this->remove_front());
      // Node *current = head.ptr, *next = nullptr;s
      // while (!this->is_empty()) {
      //   if (current->next) next = current->next;
      //   delete current;
      //   current = next;
      // }
    }
    std::ostream& output(std::ostream& o) const {
      size_t currentNumber = 0;
      Node *currentNode = head.ptr;
      o << "--- HEAD ---" << std::endl << "Pointing To: " << head.ptr << std::endl << "------" << std::endl;
      while ((currentNumber++ < amount) && (currentNode && currentNode->next && (currentNode = currentNode->next)))
        o << "Node #" << currentNumber << std::endl << std::endl
          << ((currentNode == head.ptr) ? currentNode->previous : currentNode)->output(o) 
          << (!(currentNumber - 1) ? "" : "------") << std::endl;
      return o << "------" << std::endl << "Pointing To: " << tail.ptr << std::endl << "--- TAIL ---" << std::endl;
      return o;
    }
};
std::ostream& operator<<(std::ostream& o, const Node &n) {
  return o << n.output(o);
}
std::ostream& operator<<(std::ostream& o, const DoublyLinkedList &l) {
  return l.output(o);
}

void test_queue() {
  DoublyLinkedList dll{};
  std::queue<int> q;
  std::srand(std::time(0));
  int num_elements = std::rand() % 100000 + 1;

  // Enqueue elements
  for (int i = 0; i < num_elements; ++i) {
    int value = std::rand();
    dll.insert_back(value);
    q.push(value);
  }

  // Dequeue elements and verify
  while (!q.empty()) {
    assert(dll.remove_front() == q.front());
    q.pop();
  }
  assert(dll.is_empty() == q.empty());
}

void test_queue_mixed() {
  DoublyLinkedList dll{};
  std::queue<int> q;
  std::srand(std::time(0));
  int num_operations = std::rand() % 100000 + 1;

  for (int i = 0; i < num_operations; ++i) {
    int operation = std::rand() % 2; // 0 for enqueue, 1 for dequeue
    if (operation == 0 || q.empty()) {
      int value = std::rand();
      dll.insert_back(value);
      q.push(value);
    } else {
      assert(dll.remove_front() == q.front());
      q.pop();
    }
  }
  assert(dll.is_empty() == q.empty());
}

void test_deque_mixed() {
  DoublyLinkedList dll{};
  std::deque<int> d;
  std::srand(std::time(0));
  int num_operations = std::rand() % 100000 + 1;

  for (int i = 0; i < num_operations; ++i) {
    int operation = std::rand() % 4; // 0,1 for insert (front/back), 2,3 for remove (front/back)
    if (operation == 0 || d.empty()) {
      int value = std::rand();
      dll.insert_back(value);
      d.push_back(value);
    } 
    else if (operation == 1){
      int value = std::rand();
      dll.insert_front(value);
      d.push_front(value);
    }
    else if (operation == 2){
      assert(dll.remove_front() == d.front());
      d.pop_front();
    }
    else {
      assert(dll.remove_back() == d.back());
      d.pop_back();
    }
  }
  assert(dll.is_empty() == d.empty());
}

int main() {
  test_queue();
  test_queue_mixed();
  test_deque_mixed();
  std::cout << "DoublyLinkedList tests passed!" << std::endl;
  return 0;
}
