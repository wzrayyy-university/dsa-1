#include <iostream>

struct Node {
  Node* next;
  Node* prev;
  int weight;
};

class Backpack {
 private:
  Node* first = nullptr;
  Node* last = nullptr;
  int count = 0;
 public:
  void Add(int weight) {
    Node* new_node = new Node {nullptr, last, weight};
    if (count == 0) {
      first = new_node;
      last = new_node;
    } else {
      last->next = new_node;
      last = new_node;
    }
    ++count;
  }
  int PopFirst() {
    if (count != 0) {
      Node* prev = first;
      int weight = first->weight;
      first = first->next;
      --count;
      delete prev;
      return weight;
    }
  }

  int PopLast() {
    if (count != 0) {
      Node* prev = last;
      int weight = last->weight;
      last = last->prev;
      --count;
      delete prev;
      return weight;
    }
  }
};

int main() {
  int n, max_count;
  std::cin >> n >> max_count;
  Backpack bp;

  if (n <= max_count) {
    int x;
    while (std::cin >> x) {
      std::cout << x << ' ';
    }
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;

    if (i >= max_count) {
      int y = bp.PopLast();
      int z = bp.PopFirst();
      if (x < y)
        std::swap(x, y);
      if (y < z)
        std::swap(y, z);
      if (x < y)
        std::swap(x, y);
      bp.Add(y);
    }
    bp.Add(x);
  }

  for (int i = 0; i < max_count; ++i) {
    std::cout << bp.PopFirst() << ' ';
  }

  return 0;
}
