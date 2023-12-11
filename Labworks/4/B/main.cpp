#include <iostream>
#include <vector>
#include <string>

#define int long long

class Heap {
 public:
  std::vector<int> heap_;

 public:
  void SiftUp(int i) {
    while (i > 0 && heap_[i] < heap_[(i - 1) / 2]) {
      std::swap(heap_[i], heap_[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  void Add(int element) {
    heap_.push_back(element);
    SiftUp(heap_.size() - 1);
  }

  void SiftDown(int i) {
    int smallest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    if (left < heap_.size() && heap_[left] < heap_[smallest]) {
      smallest = left;
    }
    if (right < heap_.size() && heap_[right] < heap_[smallest]) {
      smallest = right;
    }
    if (smallest != i) {
      std::swap(heap_[i], heap_[smallest]);
      SiftDown(smallest);
    }
  };

  void ExtractMin() {
    if (heap_.size() == 0) {
      std::cout << "*\n";
      return;
    }
    std::cout << heap_[0] << '\n';
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
  }
};

class PriorityQueue {
 private:
  std::vector<Heap> heaps_;
 public:
  void Create() {
    Heap new_heap;
    heaps_.push_back(new_heap);
  };

  void Insert(int k, int x) {
    heaps_[k].Add(x);
  };
  void ExtractMin(int k) {
    heaps_[k].ExtractMin();
  };
  void Merge(int m, int k) {
    Create();
    for (int i = 0; i < heaps_[m].heap_.size(); ++i) {
      heaps_[heaps_.size()-1].Add(heaps_[m].heap_[i]);
    }
    for (int i = 0; i < heaps_[k].heap_.size(); ++i) {
      heaps_[heaps_.size()-1].Add(heaps_[k].heap_[i]);
    }
  };
  void DecreaseKey(int k, int x, int y) {
    for (int i = 0; i < heaps_[k].heap_.size(); ++i) {
      if (heaps_[k].heap_[i] == x) {
        heaps_[k].heap_[i] = y;
        heaps_[k].SiftUp(i);
        break;
      }
    }
  };
};

signed main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::string argument;
  PriorityQueue priority_queue;

  while (std::cin >> argument) {
    if (argument == "create") {
      priority_queue.Create();
    } else if (argument == "insert") {
      int k, x;
      std::cin >> k >> x;
      priority_queue.Insert(k, x);
    } else if (argument == "extract-min") {
      int k;
      std::cin >> k;
      priority_queue.ExtractMin(k);
    } else if (argument == "merge") {
      int m, k;
      std::cin >> m >> k;
      priority_queue.Merge(m, k);
    } else if (argument == "decrease-key") {
      int k, x, y;
      std::cin >> k >> x >> y;
      priority_queue.DecreaseKey(k, x, y);
    }
  }

  return 0;
}
