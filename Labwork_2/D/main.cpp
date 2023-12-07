#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int* a = new int[n];

  for (int i = 1; i <= n; ++i) {
    a[i-1] = i;
  }

  for (int i = 2; i < n; ++i) {
    std::swap(a[i], a[i/2]);
  }

  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }

  delete[] a;
  return 0;
}
