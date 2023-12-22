#include <cstddef>
#include <iostream>

#include <string>
#include <vector>

typedef long long ll;

struct Node {
  Node* left_child = nullptr;
  Node* right_child = nullptr;
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

  void InorderTraversalVector(std::vector<ll>& container) {
    InorderTraversalVector(root, container);
  }

  void InorderTraversalVector(Node* node, std::vector<ll>& container) {
    if (!node) {
      return;
    }

    InorderTraversalVector(node->left_child, container);
    container.push_back(node->value);
    InorderTraversalVector(node->right_child, container);
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

  void AddChild(Node* node) {
    if (!root) {
      root = node;
      return;
    }
    AddChild(root, node);
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

  void PrintRightElement() {
    ll height = FindHeight(root);
    for (ll i = 1; i <= height; ++i) {
      PrintRightElement(root, i);
    }
  }

 private:
  void DeleteNodes(Node* node) {
    if (!root) {

      return;
    }
    // DeleteNodes(node->left_child);
    // DeleteNodes(node->right_child);
    delete node;
  }

  Node* AddChild(Node* node, ll value) {

    if (!node) return new Node(value);

    if (*node > value) {
      node->left_child = AddChild(node->left_child, value);
    } else {
      node->right_child = AddChild(node->right_child, value);
    }

    return node;
  }

  Node* AddChild(Node* node, Node* value) {

    if (!node) return value;

    if (*node > value->value) {
      node->left_child = AddChild(node->left_child, value);
    } else {
      node->right_child = AddChild(node->right_child, value);
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

      delete next;
      return node;
    }
  }

  ll FindHeight(Node* node) {
    if (!node)

      return 0;
    else {
      ll left = FindHeight(node->left_child);
      ll right = FindHeight(node->right_child);

      return std::max(left, right) + 1;
    }
  }

  bool PrintRightElement(Node* node, ll level) {
    bool ret_val = false;
    if (!node) {
      return false;
    }
    if (level == 1) {
      std::cout << node->value << ' ';
      return true;
    } else if (level > 1) {
      ret_val = PrintRightElement(node->right_child, level - 1);
      if (!ret_val) {
        ret_val = PrintRightElement(node->left_child, level - 1);
      }
    }
    return ret_val;
  }

 public:
  Node* root = nullptr;
};

ll GetValueFromStdin() {
  ll temp;
  std::cin >> temp;
  return temp;
}

int main() {
  ll n;
  std::cin >> n;

  BinarySearchTree acc1;
  BinarySearchTree acc2;

  std::string cmd;
  for (ll i = 0; i < n; ++i) {
    std::cin >> cmd;
    if (cmd == "buy") {
      int acc;
      std::cin >> acc;

      if (acc == 1) {
        acc1.AddChild(GetValueFromStdin());
      } else {
        acc2.AddChild(GetValueFromStdin());
      }
    } else if (cmd == "sell") {
      int acc;
      std::cin >> acc;

      if (acc == 1) {
        acc1.Delete(GetValueFromStdin());
      } else {
        acc2.Delete(GetValueFromStdin());
      }
    } else if (cmd == "merge") {
      std::vector<ll> nodes_1;
      std::vector<ll> nodes_2;
      acc2.InorderTraversalVector(nodes_2);
      acc2.root = nullptr;

      for (ll node : nodes_2) {
        acc1.AddChild(node);
      }

      acc1.InorderTraversalVector(nodes_1);
      if (nodes_1.empty()) {
        continue;
      }

      for (int i = 0; i < nodes_1.size() - 1; ++i) {
        std::cout << nodes_1[i] << " ";
      }
      std::cout << nodes_1[nodes_1.size() - 1] << '\n';
    }
  }
}
