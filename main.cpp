// 70978724
#include <iostream>
#include <vector>

long long n;
long long k;
long long a;
long long x;
long long y;
int size = 0;

std::vector<int> mini;

void Push() {
  mini.push_back(a);
  ++size;
}

void Append(int a) {
  if (mini.empty()) {
    Push();
  } else if (a <= mini[size - 1]) {
    if (size != k) {
      Push();
    } else {
      for (int i = 0; i != size - 1; ++i) {
        mini[i] = mini[i + 1];
      }
      mini[size - 1] = a;
    }
  } else {
    if (size != k) {
      Push();
      for (int i = size - 1; i != 0; --i) {
        mini[i] = mini[i - 1];
      }
    }
    for (int i = 1; i != size; ++i) {
      if (a > mini[i]) {
        for (int j = 0; j != i; ++j) {
          mini[j] = mini[j + 1];
        }
        mini[i - 1] = a;
        break;
      }
    }
  }
}

int main() {
  std::cin >> n >> k;
  std::cin >> a >> x >> y;
  a = (x * a + y) % 1073741824;
  for (int i = 0; i != n; ++i) {
    if (size < k || mini[0] > a) {
      Append(a);
    }
    a = (x * a + y) % 1073741824;
  }
  for (int i = size - 1; i != -1; --i) {
    std::cout << mini[i] << " ";
  }
  std::cout << std::endl;
}
