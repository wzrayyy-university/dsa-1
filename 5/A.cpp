#include <iostream>
#include <vector>
#include <cstddef>

template<typename T>
struct Node {
  Node<T>* left_child = nullptr;
  Node<T>* right_child = nullptr;
  T value;

  Node(T value) : value(value){};

  bool operator==(T rhs) {
    return value == rhs;
  }

  bool operator<(T rhs) {
    return value < rhs;
  }

  bool operator>(T rhs) {
    return value > rhs;
  }

  bool operator<=(T rhs) {
    return (*this < rhs) || (*this == rhs);
  }

  bool operator>=(T rhs) {
    return (*this > rhs) || (*this == rhs);
  }
};

template<typename T>
class BinarySearchTree {
 public:
  void PreorderTraversal() {
    if (!root) {
      return;
    }
    PreorderTraversal(root);
  }

  void InorderTraversal() {
    if (!root) {
      return;
    }
    InorderTraversal(root);
  }

  void PostorderTraversal() {
    if (!root) {
      return;
    }
    PostorderTraversal(root);
  }

  void AddChild(T value) {
    if (!root) {
      root = new Node(value);
      return;
    }
    AddChild(root, value);
  }

  void Construct(const std::vector<T>& array) {
    root = Construct(array, 0, array.size() - 1);
  }


 private:
  Node<T>* AddChild(Node<T>* node, T value) {
    if (!node) return new Node(value);

    if (*node < value) {
      node->left_child = AddChild(node->left_child, value);
    } else if (*node >= value) {
      node->right_child = AddChild(node->right_child, value);
    }

    return node;
  }

  void PreorderTraversal(Node<T>* node) {
    if (!node) {
      return;
    }
    std::cout << node->value << ' ';
    PreorderTraversal(node->left_child);
    PreorderTraversal(node->right_child);
  }

  void InorderTraversal(Node<T>* node) {
    if (!node) {
      return;
    }
    InorderTraversal(node->left_child);
    std::cout << node->value << ' ';
    InorderTraversal(node->right_child);
  }

  void PostorderTraversal(Node<T>* node) {
    if (!node) {
      return;
    }
    PostorderTraversal(node->left_child);
    PostorderTraversal(node->right_child);
    std::cout << node->value << ' ';
  }

  Node<T>* Construct(const std::vector<T>& array, long long start, long long end) {
    if (start > end)
      return nullptr;

    size_t mid = (start + end) / 2;
    Node<T>* node = new Node<T>(array[mid]);

    node->left_child = Construct(array, start, mid - 1);
    node->right_child = Construct(array, mid + 1, end);

    return node;
  }

 private:
  Node<T>* root = nullptr;
};

int main() {
  BinarySearchTree<int> bst;
  int n;
  std::cin >> n;

  std::vector<int> arr;
  arr.reserve(n);

  for (int i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    arr.push_back(tmp);
  }

  bst.Construct(arr);
  bst.PreorderTraversal();
}
