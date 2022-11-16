// 71340120
#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  int h;
  Node(int n) {
    key = n;
    left = 0;
    right = 0;
    h = 1;
  }
  int Height(Node* n);
  void NewHeight(Node* n);
  int Differ(Node* n);
  Node* RotateR(Node* n);
  Node* RotateL(Node* n);
  Node* Insert(Node* root, int num, int* count);
  void Delete(Node* root);
};

void Delete(Node* root) {
  if (root != 0) {
    Delete(root->right);
    Delete(root->left);
  }
  delete root;
}

void Print(Node* root) {
  if (root != 0) {
    Print(root->left);
    std::cout << root->key << " ";
    Print(root->right);
  }
}

int Height(Node* n) {
  if (n == 0) {
    return 0;
  }
  return n->h;
}

int Differ(Node* n) { return (Height(n->right) - Height(n->left)); }

void NewHeight(Node* n) {
  int hl = Height(n->left);
  int hr = Height(n->right);
  n->h = (hl > hr ? hl : hr) + 1;
}

Node* RotateR(Node* n) {
  Node* m = n->left;
  n->left = (m->right == 0 ? 0 : m->right);
  m->right = n;
  NewHeight(m);
  NewHeight(n);
  return m;
}

Node* RotateL(Node* n) {
  Node* m = n->right;
  n->right = (m->left == 0 ? 0 : m->left);
  m->left = n;
  NewHeight(m);
  NewHeight(n);
  return m;
}

Node* Fix(Node* n) {
  NewHeight(n);
  if (Differ(n) == 2) {
    if (Differ(n->right) < 0) {
      n->right = RotateR(n->right);
    }
    return RotateL(n);
  }
  if (Differ(n) == -2) {
    if (Differ(n->left) > 0) {
      n->left = RotateL(n->left);
    }
    return RotateR(n);
  }
  return n;
}

Node* Insert(Node* root, int num) {
  if (root == 0) {
    return (new Node(num));
  }
  if (num < (root->key)) {
    root->left = Insert(root->left, num);
  } else {
    root->right = Insert(root->right, num);
  }
  return Fix(root);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Node* root = 0;
  int n;
  std::cin >> n;
  for (int i = 0; i != n; ++i) {
    int k;
    std::cin >> k;
    for (int j = 0; j != k; ++j) {
      int num;
      std::cin >> num;
      root = Insert(root, num);
    }
  }
  Print(root);
  Delete(root);
}
