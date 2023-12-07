#include <iostream>

void Merge(int* arr, int left, int mid, int right, long long& counter);
void MergeSort(int* arr, int start, int end, long long& counter);

void Merge(int* arr, int left, int mid, int right, long long& counter) {
  int left_size = mid-left+1;
  int right_size = right-mid;

  int* left_arr = new int[left_size];
  int* right_arr = new int[right_size];

  for (int i = 0; i < left_size; ++i) {
    left_arr[i] = arr[left + i];
  }

  for (int i = 0; i < right_size; ++i) {
    right_arr[i] = arr[mid + 1 + i];
  }

  int i = 0, j = 0, idx = left;

  while (i < left_size && j < right_size) {
    if (left_arr[i] <= right_arr[j]) {
      arr[idx] = left_arr[i];
      ++i;
    } else {
      arr[idx] = right_arr[j];
      ++j;
      counter += left_size - i;
    }
    ++idx;
  }

  while (i < left_size) {
    arr[idx] = left_arr[i];
    ++i;
    ++idx;
  }

  while (j < right_size) {
    arr[idx] = right_arr[j];
    ++j;
    ++idx;
  }

  delete[] left_arr;
  delete[] right_arr;
}

void MergeSort(int* arr, int start, int end, long long& counter) {
  if (start >= end)
    return;

  int mid = start + (end - start) / 2;
  MergeSort(arr, start, mid, counter);
  MergeSort(arr, mid + 1, end, counter);

  Merge(arr, start, mid, end, counter);
}

int main() {
  int size;
  std::cin >> size;
  int* a = new int[size];

  for (int i = 0; i < size; ++i) {
    std::cin >> a[i];
  }

  long long counter = 0;

  MergeSort(a, 0, size - 1, counter);

  std::cout << counter;

  delete[] a;
  return 0;
}
