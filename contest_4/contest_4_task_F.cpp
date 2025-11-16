#include <bits/stdc++.h>

const int64_t kMod = 1e9;

template <typename Type>
struct Node {
  Type key;
  Type sum;
  int64_t height;
  Node* left;
  Node* right;
  Node(Type key)
      : key(key), sum(key), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
 public:
  void Insert(int64_t val) { root_ = Insert(root_, val); }

  void Remove(int64_t val) { root_ = Remove(root_, val); }

  int64_t GetSum(int64_t left, int64_t right) {
    if (root_ == nullptr) {
      return 0;
    }
    return GetSum(root_, FindMin(root_)->key, FindMax(root_)->key, left, right);
  }

  template <typename TypeKey>
  Node<int>* Find(const TypeKey& key) {
    return Find(root_, key);
  }

  ~AVL() { Delete(root_); }

 private:
  Node<int64_t>* root_ = nullptr;

  template <typename Type>
  int64_t Sum(Type ver) {
    return ver == nullptr ? 0 : ver->sum;
  }

  template <typename Type>
  void UpdateSum(Type ver) {
    if (ver == nullptr) {
      return;
    }
    ver->sum = ver->key + Sum(ver->left) + Sum(ver->right);
  }

  template <typename Type>
  int64_t GetSum(Type ver, int64_t tl, int64_t tr, int64_t left,
                 int64_t right) {
    if (ver == nullptr || tl > tr || tr < left || right < tl) {
      return 0;
    }
    if (left <= tl && tr <= right) {
      return ver->sum;
    }
    int64_t ok = (left <= ver->key && ver->key <= right ? ver->key : 0);
    return ok + GetSum(ver->left, tl, ver->key - 1, left, right) +
           GetSum(ver->right, ver->key + 1, tr, left, right);
  }

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
  int64_t BalanceFactor(Type ver) {
    int64_t hr = ver->right != nullptr ? ver->right->height : 0;
    int64_t hl = ver->left != nullptr ? ver->left->height : 0;
    return hr - hl;
  }

  template <typename Type>
  void FixHeight(Type ver) {
    int64_t hr = ver->right != nullptr ? ver->right->height : 0;
    int64_t hl = ver->left != nullptr ? ver->left->height : 0;
    ver->height = (hl > hr ? hl : hr) + 1;
  }

  template <typename Type>
  Type RotateRight(Type ver) {
    Type son = ver->left;
    ver->left = son->right;
    son->right = ver;
    UpdateSum(ver);
    UpdateSum(son);
    FixHeight(ver);
    FixHeight(son);
    return son;
  }

  template <typename Type>
  Type RotateLeft(Type ver) {
    Type son = ver->right;
    ver->right = son->left;
    son->left = ver;
    UpdateSum(ver);
    UpdateSum(son);
    FixHeight(ver);
    FixHeight(son);
    return son;
  }

  template <typename Type>
  Type Balance(Type ver) {
    UpdateSum(ver);
    FixHeight(ver);
    if (BalanceFactor(ver) == 2) {
      if (BalanceFactor(ver->right) < 0) {
        ver->right = RotateRight(ver->right);
      }
      // UpdateSum(ver);
      return RotateLeft(ver);
    }
    if (BalanceFactor(ver) == -2) {
      if (BalanceFactor(ver->left) > 0) {
        ver->left = RotateLeft(ver->left);
      }
      // UpdateSum(ver);
      return RotateRight(ver);
    }
    UpdateSum(ver);
    return ver;
  }

  template <typename Type>
  Type Insert(Type ver, int64_t val) {
    if (ver == nullptr) {
      ver = new Node(val);
      return ver;
    }
    if (val < ver->key) {
      ver->left = Insert(ver->left, val);
    } else if (val == ver->key) {
      return ver;
    } else {
      ver->right = Insert(ver->right, val);
    }
    // UpdateSum(ver);
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
  Type FindMax(Type ver) {
    if (ver == nullptr) {
      return ver;
    }
    return ver->right != nullptr ? FindMax(ver->right) : ver;
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
  Type Remove(Type ver, int64_t val) {
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
    if (ver == nullptr || ver->key == key) {
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
  int64_t number;
  std::cin >> number;
  AVL family;
  std::vector<std::pair<char, int64_t>> member(number);
  for (int64_t ind = 0; ind < number; ++ind) {
    std::cin >> member[ind].first;
    if (member[ind].first == '+') {
      std::cin >> member[ind].second;
      if (ind - 1 >= 0 && member[ind - 1].first == '?') {
        family.Insert((member[ind].second + member[ind - 1].second) % kMod);
      } else {
        family.Insert(member[ind].second);
      }
    } else {
      int64_t left;
      int64_t right;
      std::cin >> left >> right;
      member[ind].second = family.GetSum(left, right);
      std::cout << member[ind].second << '\n';
    }
  }
}