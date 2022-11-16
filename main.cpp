//70370782
#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  const int* mid = begin + (end - begin) / 2;
  if (end - mid == 1 && *mid != target && *begin != target) {
    return false;
  }
  if (*mid < target) {
    return BinarySearch(mid + 1, end, target);
  }
  if (*mid > target) {
    return BinarySearch(begin, mid, target);
  }
  return true;
}

int main() {
  int n;
  int q;
  std::cin >> n;
  int* search = new int[n];
  for (int i = 0; i != n; ++i) {
    int x;
    std::cin >> x;
    search[i] = x;
  }
  std::cin >> q;
  for (int k = 0; k != q; ++k) {
    int i;
    int j;
    int t;
    std::cin >> i >> j >> t;
    std::cout << (BinarySearch(&search[i], &search[j], t) ? "YES" : "NO")
              << std::endl;
  }
  delete[] search;
  return 0;
}
