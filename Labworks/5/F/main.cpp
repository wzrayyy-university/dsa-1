#include <cstddef>
#include <iostream>
#include <vector>
#include <stack>

typedef long long ll;

struct Node {
  Node* left_child = nullptr;
  Node* right_child = nullptr;
  ll value;

  Node(ll value) : value(value){};

  bool operator==(ll rhs) {
    return value == rhs;
  }

  bool operator!=(ll rhs) {
    return value != rhs;
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
  void AddTraversals(std::vector<ll>& inorder_, std::vector<ll>& postorder_) {
    inorder = &inorder_;
    postorder = &postorder_;
  }
  BinarySearchTree() = default;
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
    ll i = 0;
    InorderTraversal(root, i);
  }

  void PostorderTraversal() {
    if (!root) {

      return;
    }
    ll i = 0;
    PostorderTraversal(root, i);
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

  void PrintRightElement() {
    ll height = FindHeight(root);
    for (ll i = 1; i <= height; ++i) {
      PrintRightElement(root, i);
    }
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

  void InorderTraversal(Node* node, ll& i) {
    if (!node) {
      return;
    }

    InorderTraversal(node->left_child, i);

    if (*node != (*inorder)[i]) {
      // for (int j = 0; j < 6; ++j) {
      //   std::cout << (*inorder)[j] << ' ';
      // }
      // std::cout << "\n";
      // std::cout << node->value << ' ' << (*inorder)[i] << '\n';
      std::cout << "NO";
      exit(0);
    }
    // else {
    //   std::cout << (*inorder)[i] << " Matches\n";
    // }
    ++i;

    InorderTraversal(node->right_child, i);
  }

  void PostorderTraversal(Node* node, ll& i) {
    if (!node) {
      return;
    }
    PostorderTraversal(node->left_child, i);
    PostorderTraversal(node->right_child, i);
    if (*node != (*postorder)[i]) {
      std::cout << "NO";
      exit(0);
    }
    ++i;
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
  std::vector<ll>* inorder;
  std::vector<ll>* postorder;
};

ll GetValueFromStdin() {
  ll temp;
  std::cin >> temp;
  return temp;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  ll n;
  std::cin >> n;

  std::vector<std::vector<ll>> values(2);

  BinarySearchTree bst;

  std::stack<Node*> stack;

  ll value = GetValueFromStdin();

  Node* new_node = new Node(value);
  bst.root = new_node;
  stack.push(new_node);

  for (ll i = 1; i < n; ++i) {
    value = GetValueFromStdin();
    Node* current_node = nullptr;
    while (!stack.empty() && (*stack.top()) <= value) {
      current_node = stack.top();
      stack.pop();
    }
    if (!current_node) {
      current_node = stack.top();
      Node* new_node = new Node(value);
      current_node->left_child = new_node;
      stack.push(new_node);
    } else {
      Node* new_node = new Node(value);
      current_node->right_child = new_node;
      stack.push(new_node);
    }
  }

  values[0].reserve(n);
  values[1].reserve(n);
  for (int i = 0; i < 2; ++i) {
    for (ll j = 0; j < n; ++j)
      values[i].push_back(GetValueFromStdin());
  }

  bst.AddTraversals(values[0], values[1]);
  bst.InorderTraversal();
  bst.PostorderTraversal();

  std::cout << "YES";
  return 0;
}
