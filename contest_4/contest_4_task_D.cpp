#include <bits/stdc++.h>

std::random_device rd;
std::mt19937 gen(rd());

struct Node {
  int key;
  int size;
  int prior;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(int key) : key(key), size(1), prior(gen()) {}
};

class Treap {
 public:
  bool Exists(int val) { return Exists(root_, val); }

  void Insert(int val) { Insert(root_, val); }

  void Erase(int val) { Erase(root_, val); }

  std::string Next(int val) { return Next(root_, val); }

  std::string Prev(int val) { return Prev(root_, val); }

  std::string Kth(int val) {
    auto* kth_stat = Kth(root_, val);
    return kth_stat == nullptr ? "none" : std::to_string(kth_stat->key);
  }

  ~Treap() { Delete(root_); }

 private:
  using Pair = std::pair<Node*, Node*>;
  Node* root_ = nullptr;

  static void Delete(Node*& ver) {
    if (ver == nullptr) {
      return;
    }
    Delete(ver->left);
    Delete(ver->right);
    delete ver;
  }

  static int Size(Node* ver) { return ver == nullptr ? 0 : ver->size; }

  static void Update(Node* ver) {
    if (ver == nullptr) {
      return;
    }
    ver->size = Size(ver->left) + Size(ver->right) + 1;
  }

  static Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->prior > right->prior) {
      left->right = Merge(left->right, right);
      Update(left);
      return left;
    }
    right->left = Merge(left, right->left);
    Update(right);
    return right;
  }

  static Pair Split(Node* ver, int val) {
    if (ver == nullptr) {
      return {nullptr, nullptr};
    }
    if (ver->key <= val) {
      Pair part = Split(ver->right, val);
      ver->right = part.first;
      Update(ver);
      return {ver, part.second};
    }
    Pair part = Split(ver->left, val);
    ver->left = part.second;
    Update(ver);
    return {part.first, ver};
  }

  static Node* FindMin(Node* ver) {
    if (ver == nullptr) {
      return ver;
    }
    return ver->left != nullptr ? FindMin(ver->left) : ver;
  }

  static Node* FindMax(Node* ver) {
    if (ver == nullptr) {
      return ver;
    }
    return ver->right != nullptr ? FindMax(ver->right) : ver;
  }

  static Node* Kth(Node* ver, int val) {
    if (ver == nullptr || Size(ver) < val) {
      return nullptr;
    }
    if (val == Size(ver->left) + 1) {
      return ver;
    }
    if (val <= Size(ver->left)) {
      return Kth(ver->left, val);
    }
    return Kth(ver->right, val - Size(ver->left) - 1);
  }

  static bool Exists(Node* root, int val) {
    if (root == nullptr) {
      return false;
    }

    if (root->key == val) {
      return true;
    }

    if (val < root->key) {
      return Exists(root->left, val);
    }
    return Exists(root->right, val);
  }

  static void Insert(Node*& root, int val) {
    if (Exists(root, val)) {
      return;
    }
    Pair part = Split(root, val);
    Node* ver = new Node(val);
    root = Merge(part.first, Merge(ver, part.second));
  }

  static void Erase(Node*& root, int val) {
    auto [left, right] = Split(root, val);
    auto [left1, elem] = Split(left, val - 1);
    root = Merge(left1, right);
    delete elem;
  }

  static std::string Next(Node*& root, int val) {
    auto [left, right] = Split(root, val);
    auto* next_val = FindMin(right);
    root = Merge(left, right);
    if (next_val == nullptr) {
      return "none";
    }
    return std::to_string(next_val->key);
  }

  static std::string Prev(Node*& root, int val) {
    auto [left, right] = Split(root, val - 1);
    auto* prev_val = FindMax(left);
    root = Merge(left, right);
    if (prev_val == nullptr) {
      return "none";
    }
    return std::to_string(prev_val->key);
  }
};

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  std::string operation;
  Treap root;
  while (std::cin >> operation) {
    int val;
    std::cin >> val;
    if (operation == "insert") {
      root.Insert(val);
    } else if (operation == "delete") {
      root.Erase(val);
    } else if (operation == "exists") {
      std::cout << (root.Exists(val) ? "true\n" : "false\n");
    } else if (operation == "next") {
      std::cout << root.Next(val) << '\n';
    } else if (operation == "prev") {
      std::cout << root.Prev(val) << '\n';
    } else if (operation == "kth") {
      std::cout << root.Kth(++val) << '\n';
    }
  }
}