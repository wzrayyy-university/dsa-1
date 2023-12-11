#include <iostream>

using namespace std;

int FindClosestNeighbor(int number, int &power_first, int &power_third) {
  int binary_number[60];
  int size = 0;
  bool second_half = false;

  while (number != 0) {
    binary_number[size] = number % 2;
    number /= 2;
    ++size;
  }

  for (int i = size - 1; i >= 0; --i) {
    if (binary_number[i] == 1 && !second_half) {
      ++power_first;
    } else if (binary_number[i] == 0) {
      second_half = true;
    } else if (binary_number[i] == 1 && second_half) {
      power_third = i + 1;
      return size;
    }
    ++power_third;
    if (power_first + power_third = size) {
      --power_first;
      power_third = size - power_first - 1;
    }
  }
  return size;
}

int main() {
//  long long start, stop;
//  cin >> start >> stop;
  int start = 32766, stop = 32775;
  int counter = 0;

  int power_first = 0;
  int power_third = 0;
  long long number = 0;

  int size = FindClosestNeighbor(start, power_first, power_third);

  while (true) {
    number = (1 << size) - (1 << (size - power_first)) + (1 << (power_third)) - 1;
    ++power_third;

    if (power_third >= size - power_first) {
      ++power_first;
      power_third = 1;
    }

    if (size - power_first <= 1) {
      ++size;
      power_first = 1;
      power_third = 1;
    }

    if (number > stop) {
      return 0;
    }
    std::cout << number << std::endl;
  }
}
