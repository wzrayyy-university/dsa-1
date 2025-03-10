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
  char* formula = new char[10000];
  int idx = 0;

  while ((formula[idx] = static_cast<char>(std::cin.get()))) {
    if (formula[idx] == '\n')
      break;
    ++idx;
  }

  for (int i = 0; i < idx; ++i) {
    std::cout << formula[i];
  }

  return 0;
}
