#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int num_first;
  int num_now;
  int k = 1;
  std::cin >> num_first;
  for (int i = 0; i != n - 1; ++i) {
    std::cin >> num_now;
    (num_now > num_first) ? ++k : k;
  }
  std::cout << k % n;
}
