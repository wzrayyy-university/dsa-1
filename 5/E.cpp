#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

struct Node {
  Node* left_child = nullptr;
  Node* right_child = nullptr;
  int count;
  std::string value;

  Node(std::string value) : value(value), count(1){};

  bool operator<(std::string& rhs) {
    return value < rhs;
  }

  bool operator>(std::string& rhs) {
    return value > rhs;
  }

  bool operator==(std::string& rhs) {
    return value == rhs;
  }
};

class BinarySearchTree {
 public:
  ~BinarySearchTree() {
    DeleteNodes(root);
  }

  void AddChild(std::string& value) {
    if (!root) {
      root = new Node(value);
      return;
    }
    AddChild(root, value);
  }

  int Find(std::string& value) {
    return Find(root, value)->count;
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

  Node* AddChild(Node* node, std::string& value) {
    if (!node) return new Node(value);

    if (*node == value) {
      node->count++;
    }

    if (*node > value) {
      node->left_child = AddChild(node->left_child, value);
    } else if (*node < value) {
      node->right_child = AddChild(node->right_child, value);
    }

    return node;
  }

  Node* Find(Node* node, std::string& value) {
    if (!node || *node == value) {
      return node;
    }

    if (*node > value) {
      return Find(node->left_child, value);
    } else {
      return Find(node->right_child, value);
    }
  }

 private:
  Node* root = nullptr;
};

std::string GetValueFromStdin() {
  std::string temp;
  std::cin >> temp;
  return temp;
}

int main() {
  BinarySearchTree bst;

  std::vector<std::vector<std::string>> values(3);

  ll n;
  std::cin >> n;

  for (int i = 0; i < 3; ++i) {
    values[i].reserve(n);
    for (int j = 0; j < n; ++j) {
      std::string value = GetValueFromStdin();
      values[i].push_back(value);
      bst.AddChild(value);
    }
  }

  
  for (int i = 0; i < 3; ++i){
    int ans = 0;
    for (int j = 0; j < n; ++j){
      int count = bst.Find(values[i][j]);
      if (count == 1) {
        ans += 3;
      } else if (count == 2) {
        ++ans;
      }
    }
    std::cout << ans << " ";
  }
}
