#include <bits/stdc++.h>

std::random_device rd;
std::mt19937 gen(rd());

struct Node {
  long long key;
  long long size;
  long long sum;
  long long prior;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(long long key) : key(key), size(1), sum(key * key), prior(gen()) {}
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

long long Size(Node* ver) { return ver == nullptr ? 0 : ver->size; }

long long Sum(Node* ver) { return ver == nullptr ? 0 : ver->sum; }

void Update(Node* ver) {
  if (ver == nullptr) {
    return;
  }
  ver->size = Size(ver->left) + Size(ver->right) + 1;
  ver->sum = ver->key * ver->key + Sum(ver->left) + Sum(ver->right);
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

Pair Split(Node* ver, long long val) {
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

Node* CtrlX(Node*& root, long long left, long long right) {
  Pair q1 = Split(root, right);
  Pair q2 = Split(q1.first, left - 1);
  root = Merge(q2.first, q1.second);
  return q2.second;
}

void CtrlV(Node*& root, Node* ver, long long pos) {
  Pair part = Split(root, pos - 1);
  root = Merge(part.first, Merge(ver, part.second));
}

void Build(Node*& root, const std::vector<int>& arr) {
  for (auto elem : arr) {
    root = Merge(root, new Node(elem));
  }
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  long long number;
  long long trash;
  std::cin >> number >> trash;
  std::vector<int> segments(number);
  for (auto& elem : segments) {
    std::cin >> elem;
  }
  long long query;
  std::cin >> query;
  Node* root = nullptr;
  Build(root, segments);
  std::cout << Sum(root) << '\n';
  // std::cerr << "ok\n";
  while (query-- > 0) {
    long long type;
    long long val;
    std::cin >> type >> val;
    if (type == 1) {
      if (val == 1) {
        // std::cerr << "first\n";
        Node* del = CtrlX(root, val, val);
        Node* upd = CtrlX(root, val, val);
        upd->key += del->key;
        upd->sum = upd->key * upd->key;
        CtrlV(root, upd, val);
        delete del;
      } else if (val == Size(root)) {
        // std::cerr << "last\n";
        Node* del = CtrlX(root, val, val);
        Node* upd = CtrlX(root, val - 1, val - 1);
        upd->key += del->key;
        upd->sum = upd->key * upd->key;
        CtrlV(root, upd, val - 1);
        delete del;
      } else {
        // std::cerr << "mid\n";
        Node* del_and_upd = CtrlX(root, val - 1, val + 1);
        Node* del = CtrlX(del_and_upd, 2, 2);
        Node* upd_left = CtrlX(del_and_upd, 1, 1);
        upd_left->key += del->key / 2;
        upd_left->sum = upd_left->key * upd_left->key;
        del_and_upd->key += del->key - del->key / 2;
        del_and_upd->sum = del_and_upd->key * del_and_upd->key;
        CtrlV(root, Merge(upd_left, del_and_upd), val - 1);
        delete del;
      }
    } else {
      // std::cerr << "ok2\n";
      Node* del = CtrlX(root, val, val);
      Node* upd_left = new Node(del->key / 2);
      Node* upd_right = new Node(del->key - del->key / 2);
      CtrlV(root, Merge(upd_left, upd_right), val);
      delete del;
    }
    std::cout << Sum(root) << '\n';
  }
  Delete(root);
}