// 70437052
#include <iostream>

int Count(int first, int now) { return (now > first ? 1 : 0); }

int main() {
  size_t n;
  std::cin >> n;
  int num_first;
  int num_now;
  int k = 1;
  std::cin >> num_first;

  for (size_t i = 0; i != n - 1; ++i) {
    std::cin >> num_now;
    k += Count(num_first, num_now);
  }

  std::cout << k % n;
}
