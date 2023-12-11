#include <iostream>

void PrintArray(const int* arr, const int* size);
void SortArray(int* arr, const int* size);


void PrintArray(const int* arr, const int* size) {
  for (int i = 0; i < *size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void SortArray(int* arr, const int* size) {
  if (*size == 1)
    return;

  int i, j, idx;
  idx = 0;
  i = idx;
  j = 1;

  while (idx < *size) {
    while (arr[i] > arr[j]) {
      std::swap(arr[i], arr[j]);
      if (i == 0)
        break;
      --j;
      --i;
    }
    i = idx;
    j = ++idx;
  }
}

int main() {
  int size;
  std::cin >> size;

  int* a = new int[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> a[i];
  }

  SortArray(a, &size);
  PrintArray(a, &size);

  return 0;
}
