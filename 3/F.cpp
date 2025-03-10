#include <iostream>

struct Node {
  Node* next;
  int value;
  int idx;
};

class Stack {
 private:
  Node* first = nullptr;
  int size = 0;

 public:
  void Add(int message, int idx) {
    Node* new_node = new Node{first, message, idx};
    first = new_node;
    ++size;
  };

  int Pop() {
    Node* last = first;
    int return_value = last->value;
    first = last->next;
    delete last;
    --size;
    return return_value;
  }

  int Get() {
    return first->value;
  }

  int GetIdx() {
    return first->idx;
  }

  int GetSize() {
    return size;
  }
};

int main() {
  int n;
  std::cin >> n;
  Stack stack;
  int* tasks = new int[n];

  for (int i = 0; i < n; ++i) {
    int diff;
    std::cin >> diff;

    while (stack.GetSize() != 0 && stack.Get() < diff) {
      tasks[stack.GetIdx()] = i - stack.GetIdx();
      stack.Pop();
    }
    stack.Add(diff, i);

  }

  while (stack.GetSize() != 0) {
    tasks[stack.GetIdx()] = -1;
    stack.Pop();
  }

  for (int i = 0; i < n; ++i) {
    std::cout << tasks[i] << ' ';
  }

  return 0;
}
