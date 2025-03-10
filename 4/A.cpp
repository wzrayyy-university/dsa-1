#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  for (int i = 0; i < n; ++i) {
    if (2 * i + 1 >= n) {
      break;
    }

    if (arr[i] > arr[2 * i + 1]) {
      std::cout << "NO";
      return 0;
    }

    if (2 * i + 2 >= n) {
      break;
    }

    if (arr[i] > arr[2 * i + 2]) {
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";

  delete[] arr;
  return 0;
}
