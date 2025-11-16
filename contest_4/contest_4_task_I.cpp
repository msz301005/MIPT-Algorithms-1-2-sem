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

using Pair = std::pair<Node*, Node*>;

void Delete(Node*& ver) {
  if (ver == nullptr) {
    return;
  }
  Delete(ver->left);
  Delete(ver->right);
  delete ver;
}

int Size(Node* ver) { return ver == nullptr ? 0 : ver->size; }

void Update(Node* ver) {
  if (ver == nullptr) {
    return;
  }
  ver->size = Size(ver->left) + Size(ver->right) + 1;
}

Node* Merge(Node* left, Node* right) {
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

Pair Split(Node* ver, int val) {
  if (ver == nullptr) {
    return {nullptr, nullptr};
  }
  if (Size(ver->left) + 1 <= val) {
    Pair part = Split(ver->right, val - Size(ver->left) - 1);
    ver->right = part.first;
    Update(ver);
    return {ver, part.second};
  }
  Pair part = Split(ver->left, val);
  ver->left = part.second;
  Update(ver);
  return {part.first, ver};
}

Node* CtrlX(Node*& root, int l, int r) {
  Pair q1 = Split(root, r);
  Pair q2 = Split(q1.first, l - 1);
  root = Merge(q2.first, q1.second);
  return q2.second;
}

void CtrlV(Node*& root, Node*& ver, int pos) {
  Pair q = Split(root, pos - 1);
  root = Merge(q.first, Merge(ver, q.second));
}

void Build(Node*& root, const std::vector<int>& arr) {
  for (auto elem : arr) {
    root = Merge(root, new Node(elem));
  }
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

int64_t Get(Node* ver, int64_t tl, int64_t tr, int64_t left,
            int64_t right) {
  if (ver == nullptr || tl > tr || tr < left || right < tl) {
    return 0;
  }
  if (left <= tl && tr <= right) {
    return Size(ver);
  }
  int64_t ok = (left <= ver->key && ver->key <= right ? 1 : 0);
  return ok + Get(ver->left, tl, ver->key - 1, left, right) +
         Get(ver->right, ver->key + 1, tr, left, right);
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  int number;
  int query;
  std::cin >> number >> query;
  std::vector<int> power(number);
  for (auto& elem : power) {
    std::cin >> elem;
  }
  Node* root = nullptr;
  Build(root, power);
  while (query-- > 0) {
    std::string operation;
    std::cin >> operation;
    if (operation == "SET") {
      int pos;
      int val;
      std::cin >> pos >> val;
      Node* upd = CtrlX(root, pos, pos);
      upd->key = val;
      CtrlV(root, upd, pos);
    } else {
      int left;
      int right;
      int low;
      int high;
      std::cin >> left >> right >> low >> high;
      Node* segment = CtrlX(root, left, right);
      std::cout
          << Get(segment, FindMin(segment)->key, FindMax(segment)->key, low,
                 high) << '\n';
      CtrlV(root, segment, left);
    }
  }
  Delete(root);
}