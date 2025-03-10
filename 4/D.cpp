#include <iostream>
#include <vector>

struct City {
  long long code;
  long long rating;
  long long pay;

  bool operator==(const City& city) const {
    return (code == city.code && rating == city.rating && pay == city.pay);
  }
};

enum class CompareBy {
  kRating,
  kPay
};

class Heap {
 private:
  std::vector<City> heap_;
  CompareBy compare_by_;

 private:
  bool Compare(const City& lhs, const City& rhs) {
    if (compare_by_ == CompareBy::kRating) {
      if (lhs.rating == rhs.rating) {
        return lhs.code > rhs.code;
      } else {
        return lhs.rating > rhs.rating;
      }
    } else if (compare_by_ == CompareBy::kPay) {
      if (lhs.pay == rhs.pay) {
        return lhs.code > rhs.code;
      } else {
        return lhs.pay > rhs.pay;
      }
    } else {
      return false;
    }
  }

 public:
  Heap(CompareBy compare_by) : compare_by_(compare_by) { };

  void SiftUp(long long i) {
    while (i > 0 && Compare(heap_[i], heap_[(i - 1) / 2])) {
      std::swap(heap_[i], heap_[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  void Add(City& element) {
    heap_.push_back(element);
    SiftUp(heap_.size() - 1);
  }

  void SiftDown(long long i) {
    long long smallest = i;
    long long left = i * 2 + 1;
    long long right = i * 2 + 2;

    if (left < heap_.size() && Compare(heap_[left], heap_[smallest])) {
      smallest = left;
    }
    if (right < heap_.size() && Compare(heap_[right], heap_[smallest])) {
      smallest = right;
    }

    if (smallest != i) {
      std::swap(heap_[i], heap_[smallest]);
      SiftDown(smallest);
    }
  };

  void Pop() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
  }

  City ExtractMin() {
    City worker = heap_[0];
    Pop();
    return worker;
  }

  City Peek() {
    return heap_[0];
  }

  bool IsEmpty() {
    return heap_.empty();
  }
};

int main() {
  Heap pay_heap {CompareBy::kPay};
  Heap rating_heap {CompareBy::kRating};

  long long n, m;
  std::cin >> n;

  for (long long i = 0; i < n; ++i) {
    long long code, rating, pay;
    std::cin >> code >> rating >> pay;
    City city {.code=code, .rating=rating, .pay=pay};
    pay_heap.Add(city);
    rating_heap.Add(city);
  }

  std::cin >> m;
  std::vector<bool> request_results;

  for (long long i = 0; i < m; ++i) {
    std::string container;
    std::cin >> container;
    request_results.push_back(container == "YES");
  }

  std::vector<long long> request_cities {};
  std::vector<long long> tour_cities {};

  long long current_request = 0;

  while (!pay_heap.IsEmpty() && !rating_heap.IsEmpty()) {
    City city_1 = rating_heap.ExtractMin();
    City city_2 = pay_heap.Peek();

    if (city_1 == city_2) {
      pay_heap.Pop();
      tour_cities.push_back(city_1.code);
    } else {
      if (current_request < request_results.size()) {
        request_cities.push_back(city_1.code);
        if (request_results[current_request++]) {
          tour_cities.push_back(city_1.code);
        }
      }
    }
  }

  for (long long i = 0; i < request_cities.size(); ++i) {
    std::cout << request_cities[i] << ' ';
  }

  std::cout << '\n';

  for (long long i = 0; i < tour_cities.size(); ++i) {
    std::cout << tour_cities[i] << ' ';
  }

  return 0;
}
