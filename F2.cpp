#include <iostream>
#include <vector>

int n;
std::vector<long long> num;
std::vector<long long> num_copy;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cin >> n;
  num.resize(n);
  for (int i = 0; i != n; ++i) {
    std::cin >> num[i];
  }
  for (int i = 0; i != 64; ++i) {
    for (int j = 0; j != n; ++j) {
      if ((num[j] & (1LL << i)) == 0) {
        num_copy.push_back(num[j]);
      }
    }
    for (int j = 0; j != n; ++j) {
      if ((num[j] & (1LL << i)) != 0) {
        num_copy.push_back(num[j]);
      }
    }
    num = num_copy;
    num_copy.clear();
  }

  for (auto i : num) {
    std::cout << i << "\n";
  }
}
