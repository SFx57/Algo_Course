#include <algorithm>
#include <iostream>
#include <string>

int arr[200000];
int arr_min[200000];
int arr2[200000];
int arr2_min[200000];
int last_stud_num = 0;
int last2 = 0;

void Enqueue() {
  int n;
  std::cin >> n;
  std::cout << "ok" << std::endl;
  arr[last_stud_num] = n;
  arr_min[last_stud_num] =
      (last_stud_num == 0 ? n : std::min(n, arr_min[last_stud_num - 1]));
  ++last_stud_num;
}

void Dequeue() {
  if (last_stud_num == 0 && arr2[0] == 0) {
    std::cout << "error" << std::endl;
  } else {
    if (arr2[0] == 0) {
      while (arr[0] != 0) {
        int num = arr[last_stud_num - 1];
        arr[last_stud_num - 1] = 0;
        arr_min[last_stud_num - 1] = 0;
        int min = (arr2[0] == 0 ? num : std::min(num, arr2_min[last2 - 1]));
        arr2[last2] = num;
        arr2_min[last2] = min;
        ++last2;
        --last_stud_num;
      }
      last_stud_num = 0;
    }
    std::cout << arr2[last2 - 1] << std::endl;
    --last2;
    arr2[last2] = 0;
    arr2_min[last2] = 0;
  }
}

void Front() {
  if (last_stud_num == 0 && arr2[0] == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << (arr2[0] == 0 ? arr[0] : arr2[last2 - 1]) << std::endl;
  }
}

void Min() {
  if (last_stud_num == 0 && arr2[0] == 0) {
    std::cout << "error" << std::endl;
  } else {
    int min;
    if (last_stud_num == 0) {
      min = arr2_min[last2 - 1];
    } else if (arr2[0] == 0) {
      min = arr_min[last_stud_num - 1];
    } else {
      min = std::min(arr2_min[last2 - 1], arr_min[last_stud_num - 1]);
    }
    std::cout << min << std::endl;
  }
}

void Size() { std::cout << last_stud_num + last2 << std::endl; }

void Clear() {
  std::cout << "ok" << std::endl;
  for (int i = 0; i != last_stud_num; ++i) {
    arr[i] = 0;
    arr_min[i] = 0;
  }
  for (int i = 0; i != last2; ++i) {
    arr2[i] = 0;
    arr2_min[i] = 0;
  }
  last_stud_num = 0;
  last2 = 0;
}

void Define(std::string cmd) {
  if (cmd == "enqueue") {
    Enqueue();
  }
  if (cmd == "dequeue") {
    Dequeue();
  }
  if (cmd == "front") {
    Front();
  }
  if (cmd == "clear") {
    Clear();
  }
  if (cmd == "min") {
    Min();
  }
  if (cmd == "size") {
    Size();
  }
}

int main() {
  int m;
  std::cin >> m;
  for (int i = 0; i != m; ++i) {
    std::string cmd;
    std::cin >> cmd;
    Define(cmd);
  }
}
