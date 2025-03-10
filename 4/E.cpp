#include <iostream>
#include <vector>

class Heap {
 private:
  std::vector<int> heap_;

 public:
  Heap(std::vector<int>& heap): heap_(heap) {
    for(int i = 0; i < heap_.size(); ++i) {
      SiftUp(i);
    }
  };

  void SiftUp(int i) {
    while (i > 0) {
      if (heap_[i] >= heap_[(i-1)/2]) {
        return;
      }
      std::swap(heap_[i], heap_[(i-1)/2]);
      i = (i-1)/2;
    }
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
    if (smallest == i) {
      return;
    }
    std::swap(heap_[i], heap_[smallest]);
    SiftDown(smallest);
  };

  int ExtractMin() {
    int element = heap_[0];
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
    return element;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<int> array(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  Heap heap(array);

  for (int i = 0; i < n; ++i) {
    std::cout << heap.ExtractMin() << ' ';
  }

  return 0;
}