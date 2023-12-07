#include <iostream>
#include <cstdlib>
#include <ctime>

int OrderStatistic(int32_t* arr, int size, int k);
int Partition(int32_t* arr, int start, int end);

int Partition(int32_t* arr, int start, int end) {
  int32_t pivot = arr[std::rand() % (end - start + 1) + start];
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

int OrderStatistic(int32_t* arr, int size, int k) {
  int left = 0;
  int right = size - 1;

  while (true) {
    int mid = Partition(arr, left, right);

    if (mid == k) {
      return arr[mid];
    } else if (k < mid) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
}

int main() {
  std::srand(std::time(nullptr));

  int n, k, A, B, C;
  std::cin >> n >> k >> A >> B >> C;
  int32_t* a = new int32_t[n];
  std::cin >> a[0] >> a[1];

  for (int i = 2; i < n; ++i) {
    a[i] = a[i-2]*A + a[i-1]*B + C;
  }

  OrderStatistic(a, n, k - 1);

  int32_t out = 0;
  for (int i = 0; i < k; ++i) {
    out ^= a[i];
  }

  std::cout << out;

  delete[] a;
  return 0;
}