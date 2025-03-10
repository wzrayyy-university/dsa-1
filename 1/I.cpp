#include <iostream>

int FindNearestNeighbor(unsigned long long number, unsigned long long& power_first, unsigned long long& power_third) {
  if (number < 5) {
    power_first = 1;
    power_third = 1;
    return 3;
  }
  int binary_number[60];
  int size = 0;
  bool second_half = false;

  while (number != 0) {
    binary_number[size] = number % 2ULL;
    number /= 2;
    ++size;
  }

  for (int i = size - 1; i >= 0; --i) {
    if (binary_number[i] == 1 && !second_half) {
      if (power_first - 2 > size)
        ++power_first;
    } else if (binary_number[i] == 0) {
      second_half = true;
    } else if (binary_number[i] == 1 && second_half) {
      power_third = i + 1;
      return size;
    }
  }
  return size;
}

void PrintBinaryNumber(long long number) {
  int binary_number[60];
  int size = 0;

  while (number != 0) {
    binary_number[size] = number % 2ULL;
    number /= 2;
    ++size;
  }

  for (int i = size - 1; i >= 0; --i) {
    std::cout << binary_number[i];
  }
}

int main() {
//  unsigned long long start, stop;
//  std::cin >> start >> stop;
  unsigned long long start = 1, stop = 100000000000000000;
  unsigned long long counter = 0;
  unsigned long long power_first = 0;
  unsigned long long power_third = 0;
  unsigned long long number = 0;

  int size = FindNearestNeighbor(start, power_first, power_third);

  while (true) {
    number = (1ULL << size) - (1ULL << (size - power_first)) + (1ULL << (power_third)) - 1;

    if (number >= start && number <= stop) {
      PrintBinaryNumber(number);
      std::cout << " " << number << " " << power_first << " " << power_third << " " << size << std::endl;
      ++counter;
    }
    if (number > stop) {
      std::cout << counter;
      return 0;
    }


    ++power_third;

    if (power_third > size - power_first - 1) {
      ++power_first;
      power_third = 1;
    }

    if (power_first >= size - power_third) {
      ++size;
      power_first = 1;
      power_third = 1;
    }

  }
}
