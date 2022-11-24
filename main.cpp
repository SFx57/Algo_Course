#include <algorithm>
#include <iostream>
#include <string>

class Elem {
 private:
  Elem* next_;
  int val_;

 public:
  Elem(int n) : next_(nullptr), val_(n) {}

  Elem* GetNext() { return this->next_; }

  void SetNext(Elem* next) { this->next_ = next; }

  int GetVal() { return this->val_; }

  void SetVal(int val) { this->val_ = val; }
};

class Stack {
 private:
  int last_;
  Elem* first_;

 public:
  Stack() : first_(nullptr) {}

  ~Stack() {
    while (!this->Empty()) {
      this->Pop();
    }
  }

  void Push(int val) {
    if (first_ == nullptr) {
      first_ = new Elem(val);
      last_ = val;
    } else {
      Elem* el = first_;
      first_ = new Elem(val);
      first_->SetNext(el);
    }
  }

  int GetLast() {
    if (this->Empty()) {
      return -1;
    }
    return last_;
  }

  int GetVal() { return first_->GetVal(); }

  bool Empty() { return first_ == nullptr; }

  int Pop() {
    if (this->Empty()) {
      return -1;
    }
    Elem* el = first_;
    first_ = first_->GetNext();
    int val = el->GetVal();
    delete el;
    return val;
  }
};

class Queue {
 private:
  int sz_ = 0;
  Stack* left_;
  Stack* right_;
  Stack* left_min_;
  Stack* right_min_;

 public:
  Queue() {
    left_ = new Stack();
    right_ = new Stack();
    left_min_ = new Stack();
    right_min_ = new Stack();
  }
  ~Queue() {
    delete left_;
    delete right_;
    delete left_min_;
    delete right_min_;
  }

  void Push(int val) {
    left_min_->Push(left_->Empty() ? val : std::min(val, left_min_->GetVal()));
    left_->Push(val);
    ++sz_;
  }

  int Pop() {
    if (left_->Empty() && right_->Empty()) {
      return -1;
    }
    if (right_->Empty()) {
      while (!left_->Empty()) {
        int num = left_->Pop();
        left_min_->Pop();
        int min = (right_->Empty() ? num : std::min(num, right_min_->GetVal()));
        right_->Push(num);
        right_min_->Push(min);
      }
    }
    right_min_->Pop();
    --sz_;
    return right_->Pop();
  }

  int Front() {
    if (left_->Empty() && right_->Empty()) {
      return -1;
    }
    return (right_->Empty() ? left_->GetLast() : right_->GetVal());
  }

  int Min() {
    if (left_->Empty() && right_->Empty()) {
      return -1;
    }
    int min;
    if (left_->Empty()) {
      min = right_min_->GetVal();
    } else if (right_->Empty()) {
      min = left_min_->GetVal();
    } else {
      min = std::min(left_min_->GetVal(), right_min_->GetVal());
    }
    return min;
  }

  int Size() { return sz_; }

  void Clear() {
    delete left_;
    delete right_;
    delete left_min_;
    delete right_min_;
    left_ = new Stack();
    right_ = new Stack();
    left_min_ = new Stack();
    right_min_ = new Stack();
    sz_ = 0;
  }
};

void Out(int val) {
  if (val == -1) {
    std::cout << "error\n";
    return;
  }
  std::cout << val << "\n";
}

void Define(std::string cmd, Queue* q) {
  if (cmd == "enqueue") {
    int x;
    std::cin >> x;
    q->Push(x);
    std::cout << "ok\n";
  }
  if (cmd == "dequeue") {
    Out(q->Pop());
  }
  if (cmd == "front") {
    Out(q->Front());
  }
  if (cmd == "clear") {
    q->Clear();
    std::cout << "ok\n";
  }
  if (cmd == "min") {
    Out(q->Min());
  }
  if (cmd == "size") {
    std::cout << q->Size() << "\n";
  }
}

int main() {
  size_t m;
  Queue* q = new Queue();
  std::cin >> m;
  for (size_t i = 0; i != m; ++i) {
    std::string cmd;
    std::cin >> cmd;
    Define(cmd, q);
  }
  delete q;
}
