#include <iostream>

class BinarySearch {
 private:
  int n;
  int k;
  int* arr;

  bool IsValid(int target) {
    int chairs = 1;
    int last_chair = arr[0];
    for (int i = 0; i < n; ++i) {
      if (arr[i] - last_chair >= target) {
        ++chairs;
        last_chair = arr[i];
      }
    }
    return chairs >= k;
  }

 public:
  BinarySearch(int n, int k, int* arr) : n(n), k(k), arr(arr) { }

  int Search() {
    int left = 0;
    int right = arr[n - 1] - arr[0] + 1;
    while (right - left > 1) {
      int mid = (left + right) / 2;
      if (IsValid(mid))
        left = mid;
      else
        right = mid;
    }
    return left;
  }

};

int main() {
  int n, k;
  std::cin >> n >> k;

  int* chairs = new int[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> chairs[i];
  }

  BinarySearch bs(n, k, chairs);

  std::cout << bs.Search();

  return 0;
}
