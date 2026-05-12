struct Node {
  int   size  {   - 1   };
  Node *left  { nullptr }, *right { nullptr };
};

// Buffer Should Be 0
int getSizeOf(Node *node, int &buffer) {
  if (!node->left and !node->right and (node->size != -1)) return node->size;
  buffer += getSizeOf(node->left, buffer) + getSizeOf(node->right, buffer);
  if (node->size == -1) node->size = buffer;
  // return buffer;
} // TODO test that this works