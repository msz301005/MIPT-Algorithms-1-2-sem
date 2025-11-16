#include <bits/stdc++.h>

using Pair = std::pair<std::string, std::string>;

bool operator<(const Pair& left, const std::string& right) {
  return left.first < right;
}

bool operator==(const Pair& left, const std::string& right) {
  return left.first == right;
}

template <typename Type>
struct Node {
  Type key;
  int height;
  Node* left;
  Node* right;
  Node(Type key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
 public:
  void Insert(const Pair& val) { root_ = Insert(root_, val); }

  void Remove(const Pair& val) { root_ = Remove(root_, val); }

  template <typename TypeKey>
  Node<Pair>* Find(const TypeKey& key) {
    return Find(root_, key);
  }

  ~AVL() { Delete(root_); }

 private:
  Node<Pair>* root_ = nullptr;

  template <typename Type>
  void Delete(Type ver) {
    if (ver == nullptr) {
      return;
    }
    Delete(ver->left);
    Delete(ver->right);
    delete ver;
  }

  template <typename Type>
  int BalanceFactor(Type ver) {
    int hr = ver->right != nullptr ? ver->right->height : 0;
    int hl = ver->left != nullptr ? ver->left->height : 0;
    return hr - hl;
  }

  template <typename Type>
  void FixHeight(Type ver) {
    int hr = ver->right != nullptr ? ver->right->height : 0;
    int hl = ver->left != nullptr ? ver->left->height : 0;
    ver->height = (hl > hr ? hl : hr) + 1;
  }

  template <typename Type>
  Type RotateRight(Type ver) {
    Type son = ver->left;
    ver->left = son->right;
    son->right = ver;
    FixHeight(ver);
    FixHeight(son);
    return son;
  }

  template <typename Type>
  Type RotateLeft(Type ver) {
    Type son = ver->right;
    ver->right = son->left;
    son->left = ver;
    FixHeight(ver);
    FixHeight(son);
    return son;
  }

  template <typename Type>
  Type Balance(Type ver) {
    FixHeight(ver);
    if (BalanceFactor(ver) == 2) {
      if (BalanceFactor(ver->right) < 0) {
        ver->right = RotateRight(ver->right);
      }
      return RotateLeft(ver);
    }
    if (BalanceFactor(ver) == -2) {
      if (BalanceFactor(ver->left) > 0) {
        ver->left = RotateLeft(ver->left);
      }
      return RotateRight(ver);
    }
    return ver;
  }

  template <typename Type>
  Type Insert(Type ver, const Pair& val) {
    if (ver == nullptr) {
      ver = new Node(val);
      return ver;
    }
    if (val < ver->key) {
      ver->left = Insert(ver->left, val);
    } else {
      ver->right = Insert(ver->right, val);
    }
    return Balance(ver);
  }

  template <typename Type>
  Type FindMin(Type ver) {
    if (ver == nullptr) {
      return ver;
    }
    return ver->left != nullptr ? FindMin(ver->left) : ver;
  }

  template <typename Type>
  Type RemoveMin(Type ver) {
    if (ver == nullptr) {
      return ver;
    }
    if (ver->left == nullptr) {
      return ver->right;
    }
    ver->left = RemoveMin(ver->left);
    return Balance(ver);
  }

  template <typename Type>
  Type Remove(Type ver, const Pair& val) {
    if (ver == nullptr) {
      return ver;
    }
    if (val < ver->key) {
      ver->left = Remove(ver->left, val);
    } else if (val > ver->key) {
      ver->right = Remove(ver->right, val);
    } else {
      Type left_son = ver->left;
      Type right_son = ver->right;
      delete ver;
      if (right_son != nullptr) {
        return left_son;
      }
      Type min = FindMin(right_son);
      min->right = RemoveMin(right_son);
      min->left = left_son;
      return Balance(min);
    }
    return Balance(ver);
  }

  template <typename Type, typename TypeKey>
  Type Find(Type ver, const TypeKey& key) {
    if (ver == nullptr) {
      return ver;
    }
    if (ver->key == key) {
      return ver;
    }
    return ver->key < key ? Find(ver->right, key) : Find(ver->left, key);
  }
};

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  int number;
  std::cin >> number;
  AVL racer_car;
  AVL car_racer;
  while (number-- > 0) {
    Pair racer;
    std::cin >> racer.first >> racer.second;
    racer_car.Insert(racer);
    std::swap(racer.first, racer.second);
    car_racer.Insert(racer);
  }
  int query;
  std::cin >> query;
  while (query-- > 0) {
    std::string word;
    std::cin >> word;
    auto* find_car = racer_car.Find(word);
    if (find_car != nullptr) {
      std::cout << find_car->key.second << '\n';
      continue;
    }
    auto* find_racer = car_racer.Find(word);
    if (find_racer != nullptr) {
      std::cout << find_racer->key.second << '\n';
    }
  }
}