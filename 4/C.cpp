#include <iostream>
#include <vector>

struct Worker {
  long long pay;
  long long finish_time;
};

enum class CompareBy {
  kPay,
  kFinishTime
};

class Heap {
 private:
  std::vector<Worker> heap_;
  CompareBy compare_by_;

 private:
  bool Compare(const Worker& lhs, const Worker& rhs) {
    if (compare_by_ == CompareBy::kFinishTime) {
      return lhs.finish_time <= rhs.finish_time;
    } else if (compare_by_ == CompareBy::kPay) {
      return lhs.pay <= rhs.pay;
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

  void Add(Worker& element) {
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

  Worker ExtractMin() {
    Worker worker = heap_[0];
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
    return worker;
  }

  Worker Peek() {
    return heap_[0];
  }

  bool isEmpty() {
    return heap_.empty();
  }
};

int main() {
  long long n, m;
  std::cin >> n >> m;

  Heap free_heap {CompareBy::kPay};
  Heap busy_heap {CompareBy::kFinishTime};

  for (long long i = 0; i < n; ++i) {
    long long pay;
    std::cin >> pay;
    Worker worker {.pay = pay, .finish_time = 0};
    free_heap.Add(worker);
  }

  long long ans = 0;
  for (long long i = 0; i < m; ++i) {
    long long t, f;
    std::cin >> t >> f;

    while (!busy_heap.isEmpty()) {
      if (busy_heap.Peek().finish_time > t) {
        break;
      }
      Worker worker = busy_heap.ExtractMin();
      free_heap.Add(worker);
    }

    if (!free_heap.isEmpty()) {
      Worker worker = free_heap.ExtractMin();
      worker.finish_time = t + f;
      ans += worker.pay * f;
      busy_heap.Add(worker);
    }
    continue;
  }
  std::cout << ans;
  return 0;
}
