#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

struct Node {
  Node* left_child = nullptr;
  Node* right_child = nullptr;
  ll right_count = 0;
  ll value;

  Node(ll value) : value(value){};

  bool operator==(ll rhs) {
    return value == rhs;
  }

  bool operator<(ll rhs) {
    return value < rhs;
  }

  bool operator>(ll rhs) {
    return value > rhs;
  }

  bool operator<=(ll rhs) {
    return (*this < rhs) || (*this == rhs);
  }

  bool operator>=(ll rhs) {
    return (*this > rhs) || (*this == rhs);
  }
};

class BinarySearchTree {
 public:
  ~BinarySearchTree() {
    DeleteNodes(root);
  }
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

  void AddChild(ll value) {
    if (!root) {
      root = new Node(value);
      return;
    }
    AddChild(root, value);
  }

  void Construct(const std::vector<ll>& array) {
    root = Construct(array, 0, array.size() - 1);
  }

  void GetNextValue(ll number) {
    Node* node = root;
    Node* next = nullptr;

    while (node) {
      if (*node > number) {
        next = node;
        node = node->left_child;
      } else {
        node = node->right_child;
      }
    }

    if (!next) {
      std::cout << "none" << std::endl;
    } else {
      std::cout << next->value << std::endl;
    }
  }

  void GetPrevValue(ll number) {
    Node* node = root;
    Node* next = nullptr;

    while (node) {
      if (*node < number) {
        next = node;
        node = node->right_child;
      } else {
        node = node->left_child;
      }
    }

    if (!next) {
      std::cout << "none" << std::endl;
    } else {
      std::cout << next->value << std::endl;
    }
  }

  void Find(ll value) {
    std::cout << Find(root, value)->value << std::endl;
  }

  void Exists(ll value) {
    std::cout << (Find(root, value) ? "true" : "false") << std::endl;
  }

  void Delete(ll value) {
    root = Delete(root, value);
  }
  void KthMax(ll value) {
    KthMax(root, value);
  }

 private:
  void DeleteNodes(Node* node) {
    if (!node) {
      return;
    }
    DeleteNodes(node->left_child);
    DeleteNodes(node->right_child);
    delete node;
  }

  Node* AddChild(Node* node, ll value) {
    if (!node) return new Node(value);

    if (*node > value) {
      node->left_child = AddChild(node->left_child, value);
    } else if (*node < value) {
      node->right_child = AddChild(node->right_child, value);
      node->right_count++;
    }

    return node;
  }

  void PreorderTraversal(Node* node) {
    if (!node) {
      return;
    }
    std::cout << node->value << ' ';
    PreorderTraversal(node->left_child);
    PreorderTraversal(node->right_child);
  }

  void InorderTraversal(Node* node) {
    if (!node) {
      return;
    }
    InorderTraversal(node->left_child);
    std::cout << node->value << ' ';
    InorderTraversal(node->right_child);
  }

  void PostorderTraversal(Node* node) {
    if (!node) {
      return;
    }
    PostorderTraversal(node->left_child);
    PostorderTraversal(node->right_child);
    std::cout << node->value << ' ';
  }

  Node* Construct(const std::vector<ll>& array, ll start, ll end) {
    if (start > end) return nullptr;

    size_t mid = (start + end) / 2;
    Node* node = new Node(array[mid]);

    node->left_child = Construct(array, start, mid - 1);
    node->right_child = Construct(array, mid + 1, end);

    return node;
  }

  Node* Find(Node* node, ll value) {
    if (!node || *node == value) {
      return node;
    }

    if (*node > value) {
      return Find(node->left_child, value);
    } else {
      return Find(node->right_child, value);
    }
  }

  Node* Delete(Node* node, ll value) {
    if (!node) {
      return node;
    }

    if (*node > value) {
      node->left_child = Delete(node->left_child, value);
      return node;
    } else if (*node < value) {
      node->right_child = Delete(node->right_child, value);
      node->right_count = node->right_child ? node->right_child->right_count + 1 : 0;
      return node;
    }

    if (!node->left_child && !node->right_child) {
      delete node;
      return nullptr;
    } else if (!node->left_child) {
      Node* tmp = node->right_child;
      delete node;
      return tmp;
    } else if (!node->right_child) {
      Node* tmp = node->left_child;
      delete node;
      return tmp;
    } else {
      Node* next_parent = nullptr;
      Node* next = node->right_child;

      while (next->left_child) {
        next_parent = next;
        next = next->left_child;
      }

      if (next_parent) {
        next_parent->left_child = next->right_child;
      } else {
        node->right_child = next->right_child;
      }
      node->value = next->value;
      node->right_count = next->right_count;

      delete next;
      return node;
    }
  }

  void KthMax(Node* node, ll k) {
    if (!node) {
      return;
    }

    if (k == node->right_count + 1) {
      std::cout << node->value << '\n';
      return;
    }
    if (k < node->right_count + 1) {
      KthMax(node->right_child, k);
    } else {
      KthMax(node->left_child, k - node->right_count - 1);
    }
  }

 private:
  Node* root = nullptr;
};

ll GetValueFromStdin() {
  ll temp;
  std::cin >> temp;
  return temp;
}

int main() {
  BinarySearchTree bst;

  ll n;
  std::cin >> n;

  for (ll i = 0; i < n; ++i) {
    int command;
    std::cin >> command;
    if (command == 1) {
      ll value = GetValueFromStdin();
      bst.AddChild(value);
    } else if (command == -1) {
      ll value = GetValueFromStdin();
      bst.Delete(value);
    } else if (command == 0) {
      ll value = GetValueFromStdin();
      bst.KthMax(value);
    }
  }
}
