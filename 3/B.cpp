#include <iostream>

struct Node {
  Node* next;
  int message;
};

class Queue {
 private:
  Node* first = nullptr;
  Node* last = nullptr;
  size_t size = 0;
 public:
  void Add(int message) {
    Node* new_node = new Node {nullptr, message};
    if (size == 0) {
      first = new_node;
    } else {
      last->next = new_node;
    }
    ++size;
    last = new_node;
  }

  int Pop() {
    if (size != 0) {
      Node* prev = first;
      int return_value = prev->message;
      first = prev->next;
      delete prev;
      --size;
      return return_value;
    }
  }

};

int main() {
  Queue queue;
  int n;
  int stack_idx = 0;

  std::cin >> n;

  int* return_values = new int[n];

  for (int i = 0; i < n; ++i) {
    char action;
    std::cin >> action;

    if (action == '+') {
      int message;

      std::cin >> message;

      queue.Add(message);
    } else {
      return_values[stack_idx] = queue.Pop();
      ++stack_idx;
    }
  }

  for (int i = 0; i < stack_idx; ++i) {
    std::cout << return_values[i] << '\n';
  }

  delete[] return_values;

  return 0;
}
