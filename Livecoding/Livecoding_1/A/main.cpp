#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int Partition(std::vector<int>& arr, int start, int end) {
  int pivot = arr[std::rand() % (end - start + 1) + start];
  int i = start - 1;
  int j = end + 1;

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

void QuickSort(std::vector<int>& arr, int start, int end) {
  if (start >= end)
    return;

  int pivot_idx = Partition(arr, start, end);

  QuickSort(arr, start, pivot_idx);
  QuickSort(arr, pivot_idx + 1, end);

}

int RHSBinarySearch(std::vector<int>& arr, int l, int r, int x) {
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] <= x) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return l;
}

int LHSBinarySearch(std::vector<int>& arr, int l, int r, int x) {
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] >= x) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return l;
}


signed main() {
  std::srand(std::time(nullptr));
  int n, k;
  std::cin >> n;

  std::vector<int> products(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> products[i];
  }

  QuickSort(products, 0, n - 1);

  std::cin >> k;

  std::vector<int> k_arr;

  for (int i = 0; i < k; ++i) {
    int a, b;
    std::cin >> a >> b;

    std::cout << RHSBinarySearch(products, 0, n-1, b) - LHSBinarySearch(products, 0, n-1, a) << ' ';
  }
}
