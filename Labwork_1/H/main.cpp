#include <iostream>

int main() {
  int n;

  std::cin >> n;

  int min_blocks = n;
  int* a = new int[n];

  for (long i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  for (long start = 0; start < 32; ++start) {
    bool *is_border = new bool[n]();
    long cx = a[start];
    int i = start;
    int border_count = 0;

    while (!is_border[i % n]) {
      if ((cx & a[(i + 1) % n]) == 0) {
        cx |= a[(i + 1) % n];
      } else {
        cx = a[(i + 1) % n];
        is_border[i % n] = true;
        ++border_count;
      }
      i++;
    }

    min_blocks = std::min(min_blocks, border_count);

    delete[] is_border;
  }
  std::cout << min_blocks;
  delete[] a;
  return 0;
}
