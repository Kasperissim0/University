#include <stdexcept>
// void treeify(int arr[], const int index, const int size);
bool contains(const int key, const Node *pivot = &root) {
  if (key < pivot->key) return (pivot->left  ? contains(key, pivot->left)  : false);
  if (key > pivot->key) return (pivot->right ? contains(key, pivot->right) : false);
  return (pivot->key == key); //? equivalent to true
}
void insert(const int key, Node *pivot = &root, Node *newNode = new Node{key}) {
  if (key < pivot->key) {
    if (pivot->left) return insert(key, pivot->left, newNode);
    pivot->left = newNode;
  } else if (key > pivot->key) {
    if (pivot->right) return insert(key, pivot->right, newNode);
    pivot->right = newNode;
  } else {
    delete newNode;
    throw std::runtime_error("duplicate entry");
  }
}
void remove(const Node *target) {
  if (target->right) {
    if (target->left) { //* right and left

    }
    else { //* right and !left

    }
  }
  else {
    if (target->left) { //* !right and left
      
    }
    else { //* !right and !left
      //* do nothing
    }
  }
  delete target;
}