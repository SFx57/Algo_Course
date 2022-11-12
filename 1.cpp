#include <iostream>
#include <string>

template <typename T>
class AvlTree {
 public:
  T x;
  AvlTree<T>* left;
  AvlTree<T>* right;
  short height;
  int child;
  AvlTree(T x) {
    this->x = x;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
    this->child = 1;
  }
  ~AvlTree() {
    delete this->right;
    delete this->left;
  }
  int GetHeight(AvlTree<T>* t) { return t == nullptr ? 0 : t->height; }
  int CountChild(AvlTree<T>* t) { return t == nullptr ? 0 : t->child; }
  int BalanceFact(AvlTree<T>* t) {
    if (t == nullptr) {
      return 0;
    }
    return GetHeight(t->right) - GetHeight(t->left);
  }
  void FixHeight(AvlTree<T>* t) {
    int left_height = GetHeight(t->left);
    int right_height = GetHeight(t->right);
    t->height =
        (left_height > right_height ? left_height + 1 : right_height + 1);
  }
  void FixChild(AvlTree<T>* t) {
    int left_child = CountChild(t->left);
    int right_child = CountChild(t->right);
    t->child = left_child + right_child + 1;
  }
  AvlTree<T>* RotateR(AvlTree<T>* t) {
    AvlTree<T>* q = t->left;
    t->left = q->right;
    q->right = t;
    FixHeight(t);
    FixHeight(q);
    FixChild(t);
    FixChild(q);
    return q;
  }
  AvlTree<T>* RotateL(AvlTree<T>* t) {
    AvlTree<T>* q = t->right;
    t->right = q->left;
    q->left = t;
    FixHeight(t);
    FixHeight(q);
    FixChild(t);
    FixChild(q);
    return q;
  }
  AvlTree<T>* BalanceTree(AvlTree<T>* t) {
    FixHeight(t);
    FixChild(t);
    if (BalanceFact(t) == 2) {
      if (BalanceFact(t->right) < 0) {
        t->right = RotateR(t->right);
      }
      return RotateL(t);
    }
    if (BalanceFact(t) == -2) {
      if (BalanceFact(t->left) > 0) {
        t->left = RotateL(t->left);
      }
      return RotateR(t);
    }
    return t;
  }
  AvlTree<T>* Insert(AvlTree<T>* t, T& x) {
    if (t == nullptr) {
      return new AvlTree(x);
    }
    t->child += 1;
    if (x < t->x) {
      t->left = Insert(t->left, x);
    } else {
      t->right = Insert(t->right, x);
    }
    return BalanceTree(t);
  }
  AvlTree<T>* Next(AvlTree<T>* t, int& x) {
    AvlTree<T>* avl = t;
    AvlTree<T>* ans = nullptr;
    while (avl != nullptr) {
      if (avl->x >= x) {
        ans = avl;
        avl = avl->left;
      } else {
        avl = avl->right;
      }
    }
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AvlTree<int>* avl = new AvlTree<int>(-1);
  int n;
  std::cin >> n;
  char todo;
  int inp;
  int ans_past;
  std::cin >> todo >> inp;
  if (todo == '+') {
    avl = avl->Insert(avl, inp);
  } else {
    std::cout << -1 << "\n";
    ans_past = -1;
  }
  char todo_past = todo;
  for (int i = 0; i != n - 1; ++i) {
    std::cin >> todo >> inp;
    if (todo == '?') {
      AvlTree<int>* node = avl->Next(avl, inp);
      ans_past = (node == nullptr ? -1 : node->x);
      std::cout << ans_past << "\n";
    } else if (todo_past == '+') {
      avl = avl->Insert(avl, inp);
    } else {
      int num = (inp + ans_past) % 1000000000;
      avl = avl->Insert(avl, num);
    }
    todo_past = todo;
  }
  delete avl;
}