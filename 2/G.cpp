#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>

struct LabWork {
  long long time_complexity;
  long long deadline;
};

int Partition(LabWork* arr, int start, int end);
void QuickSort(LabWork* arr, int start, int end);


int Partition(LabWork* arr, int start, int end) {
  int pivot = arr[rand() % (end - start + 1) + start].time_complexity; // NOLINT
  int i = start - 1;
  int j = end + 1;

  while (true) {
    do {
      ++i;
    } while (arr[i].time_complexity < pivot);

    do {
      --j;
    } while (arr[j].time_complexity > pivot);

    if (i >= j)
      return j;

    std::swap(arr[i], arr[j]);
  }
}

void QuickSort(LabWork* arr, int start, int end) { // NOLINT(*-no-recursion)
  if (start >= end)
    return;

  int pivot_idx = Partition(arr, start, end);

  QuickSort(arr, start, pivot_idx);
  QuickSort(arr, pivot_idx + 1, end);
}

int main() {
  size_t size;
  std::cin >> size;
  LabWork* labs = new LabWork[size]; // NOLINT[*-auto]
  for (long long i = 0; i < size; ++i) {
    std::cin >> labs[i].time_complexity >> labs[i].deadline;
  }

  if (size < 1) {
    std::cout << 0;
    return 0;
  }

  std::srand(std::time(nullptr));
  QuickSort(labs, 0, size - 1);

  long long date = 0;
  long long sum = 0;
  for (long long i = 0; i < size; ++i) {
    LabWork lab = labs[i];
    date += labs[i].time_complexity;
    sum += lab.deadline - date;
  }

  std::cout << sum;
  return 0;
}
