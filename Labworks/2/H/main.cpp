// СПАСИБО БОЛЬШОЕ ЧЕЛОВЕКУ С НИКОМ РИДИСКАМУЖИК ЗА ТО ЧТО ОН МНЕ В 7:36 УТРА ОБЪЯСНИЛ ВЕСЬ ЭТОТ ПИЗДЕЦ БЯТЬ Я НЕ ЗНАЮ КАК Я ЭТУ ХУЙНЮ ЗАЩИЩУ НО ПОХУЙ БЛЯТЬ У МЕНЯ БУДЕТ КРУТАЯ АСИМПТОТИКА

#include <iostream>

void Merge(long long* arr, int left, int mid, int right);
void MergeSort(long long* arr, int start, int end);

void Merge(long long* arr, int left, int mid, int right) {
  int left_size = mid-left+1;
  int right_size = right-mid;

  long long* left_arr = new long long[left_size];
  long long* right_arr = new long long[right_size];

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

void MergeSort(long long* arr, int start, int end) {
  if (start >= end)
    return;

  int mid = start + (end - start) / 2;
  MergeSort(arr, start, mid);
  MergeSort(arr, mid + 1, end);

  Merge(arr, start, mid, end);
}

int main() {
  int size;
  std::cin >> size;
  long long* a = new long long[size];

  for (int i = 0; i < size; ++i) {
    long long number;
    std::cin >> number;
    a[i] = number + i;
  }

  MergeSort(a, 0, size - 1);

  for (int i = 1; i < size; ++i) {
    if (a[i] - i < a[i-1] - (i - 1)) {
      std::cout << ":(";
      return 0;
    }
  }

  for (int i = 0; i < size; ++i) {
    std::cout << a[i] - i << " ";
  }

  delete[] a;
  return 0;
}