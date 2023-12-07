#include <iostream>
#include <vector>

int main() {
  int length;
  int offset;
  std::cin >> length >> offset;

  if (offset > 0)
    offset %= length;
  else if (offset < 0)
    offset = -((-offset) % length);

  int* numbers = new int[length];

  for (int i = 0; i < length; i++) {
    std::cin >> numbers[i];
  }

  if (offset < 0) {
    for (int a = 0; a > offset; --a) {
      for (int j = 1; j < length; ++j) {
        std::swap(numbers[j], numbers[j - 1]);
      }
    }
  } else {
    for (int a = 0; a < offset; ++a) {
      for (int j = length - 1; j > 0; --j) {
        std::swap(numbers[j], numbers[j - 1]);
      }
    }
  }
  for (int i = 0; i < length; i++) {
    std::cout << numbers[i] << " ";
  }
}

