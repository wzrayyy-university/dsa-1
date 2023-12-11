#include <iostream>
#include <cstdlib>
#include <ctime>

long long CalculateMaxSquare(long long* a, int size);
int Partition(long long* arr, int start, int end);
void QuickSort(long long* arr, int start, int end);

int Partition(long long* arr, int start, int end) {
  long long pivot = arr[std::rand() % (end - start + 1) + start];
  int i = start - 1;
  int j = end + 1;

  while (true) {
    do {
      ++i;
    } while (arr[i] > pivot);

    do {
      --j;
    } while (arr[j] < pivot);

    if (i >= j)
      return j;

    std::swap(arr[i], arr[j]);
  }
}

void QuickSort(long long* arr, int start, int end) { // NOLINT(*-no-recursion)
  if (start >= end)
    return;

  int pivot_idx = Partition(arr, start, end);

  QuickSort(arr, start, pivot_idx);
  QuickSort(arr, pivot_idx + 1, end);
}

long long CalculateMaxSquare(long long* arr, int size) {
  long long sq_sum = 0;

  long long* viable_numbers = new long long[size];
  int viable_size = 0;
  for (int i = 0; i < size - 1; ++i) {
    if (std::abs(arr[i] - arr[i+1]) <= 1) {
      viable_numbers[viable_size] = std::min(arr[i], arr[i+1]);
      ++i;
      ++viable_size;
    }
  }

  QuickSort(viable_numbers, 0, viable_size - 1);

  for (int i = 0; i < size - 1; i += 2) {
    sq_sum += viable_numbers[i] * viable_numbers[i+1];
  }

  return sq_sum;
}

int main() {
  int size;
  std::cin >> size;
  long long* a = new long long[size];

  for (int i = 0; i < size; ++i) {
    std::cin >> a[i];
  }

  std::srand(std::time(nullptr)); // stinky code, but i'm too lazy
  QuickSort(a, 0, size - 1);

  std::cout << CalculateMaxSquare(a, size);

  delete[] a;
  return 0;
}
