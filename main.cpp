// 70680957
#include <cmath>
#include <iomanip>
#include <iostream>

void Fill(double* num, double* mult, size_t n, size_t i) {
  if (i == n) {
    return;
  }
  std::cin >> num[i];
  mult[i + 1] = mult[i] * std::pow(num[i], 1.0 / n);
  Fill(num, mult, n, i + 1);
}

void Loud(double* mult, size_t k, size_t q, size_t n) {
  if (k == q) {
    return;
  }
  int i;
  int j;
  std::cin >> i >> j;
  double exp = 1.0 / (j - i + 1.0);
  double ans = std::pow(mult[j + 1] / mult[i], n * exp);
  std::cout << std::setprecision(12) << ans << std::endl;
  Loud(mult, k + 1, q, n);
}

int main() {
  size_t n;
  size_t q;
  std::cin >> n;
  double* num = new double[n];
  double* mult = new double[n + 1];
  mult[0] = 1.0;

  Fill(num, mult, n, 0);

  std::cin >> q;

  Loud(mult, 0, q, n);

  delete[] num;
  delete[] mult;
}
