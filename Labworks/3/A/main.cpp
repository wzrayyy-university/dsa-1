#include <iostream>

struct Node {
  Node* next;
  int message;
};

class Stack {
 private:
  Node* first = nullptr;

 public:
  void Add(int message) {
    Node* new_node = new Node{first, message};
    first = new_node;
  };

  int Poop() {
    Node* last = first;
    int return_value = last->message;
    first = last->next;
    delete last;
    return return_value;
  }
};

int main() {
  Stack stack;
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

      stack.Add(message);
    } else {
      return_values[stack_idx] = stack.Poop();
      ++stack_idx;
    }
  }

  for (int i = 0; i < stack_idx; ++i) {
    std::cout << return_values[i] << '\n';
  }

  delete[] return_values;

  return 0;
}
