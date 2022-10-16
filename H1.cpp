#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int n;
  int q;
  std::cin >> n;
  double* num = new double[n];
  double* mult = new double[n + 1];
  mult[0] = 1.0;
  for (int i = 0; i != n; ++i) {
    std::cin >> num[i];
    mult[i + 1] = mult[i] * std::pow(num[i], 1.0 / n);
  }
  std::cin >> q;
  for (int k = 0; k != q; ++k) {
    int i;
    int j;
    std::cin >> i >> j;
    double exp = 1.0 / (j - i + 1.0);
    double ans = std::pow(mult[j + 1] / mult[i], n * exp);
    std::cout << std::setprecision(12) << ans << std::endl;
  }
  delete[] num;
  delete[] mult;
}
