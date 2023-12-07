#include <iostream>
#include <cstdlib>
#include <ctime>

int Partition(int* arr, int start, int end);
void PrintArray(int* arr, int start, int end);
void QuickSort(int* arr, int start, int end);

void PrintArray(int* arr, int start, int end) {
  for (int i = start; i <= end; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
}

int Partition(int* arr, int start, int end) {
  int pivot = arr[std::rand() % (end - start + 1) + start];
  int i = start - 1;
  int j = end + 1;

  // move pivot to the start
  while (true) {
    do {
      ++i;
    } while (arr[i] < pivot);

    do {
      --j;
    } while (arr[j] > pivot);

    if (i >= j)
      return j;

    std::swap(arr[i], arr[j]);
  }
}

void QuickSort(int* arr, int start, int end) { // NOLINT(*-no-recursion)
  if (start >= end)
    return;

  int pivot_idx = Partition(arr, start, end);

  QuickSort(arr, start, pivot_idx);
  QuickSort(arr, pivot_idx + 1, end);

}

int main() {
  int size;
  std::cin >> size;
  int* a = new int[size];

  for (int i = 0; i < size; ++i) {
    std::cin >> a[i];
  }

  std::srand(std::time(nullptr));
  QuickSort(a, 0, size - 1);
  PrintArray(a, 0, size - 1);

  delete[] a;

  return 0;
}
