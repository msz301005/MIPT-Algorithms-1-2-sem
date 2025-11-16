#include <bits/stdc++.h>
const long long kLen = 1e9;
struct Segtree {
  long long tl;
  long long tr;
  long long sum = 0;
  Segtree* left_son = nullptr;
  Segtree* right_son = nullptr;
  Segtree() = default;
  Segtree(long long left, long long right) : tl(left), tr(right) {}
  void Extend() {
    if (left_son == nullptr && tl + 1 < tr) {
      long long tm = (tl + tr) / 2;
      left_son = new Segtree(tl, tm);
      right_son = new Segtree(tm, tr);
    }
  }
  void Add(long long pos, long long val) {
    Extend();
    sum += val;
    if (left_son != nullptr) {
      if (pos < left_son->tr) {
        left_son->Add(pos, val);
      } else {
        right_son->Add(pos, val);
      }
    }
  }
  long long GetSum(long long left, long long right) {
    if (tl >= left && tr <= right) {
      return sum;
    }
    if (std::max(tl, left) >= std::min(tr, right)) {
      return 0;
    }
    Extend();
    return left_son->GetSum(left, right) + right_son->GetSum(left, right);
  }

  ~Segtree() {
    delete left_son;
    delete right_son;
  }
};
void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}
int main() {
  Speed();
  long long queries;
  std::cin >> queries;
  Segtree tree(0, kLen);
  while (queries-- > 0) {
    char operation;
    std::cin >> operation;
    if (operation == '+') {
      long long page;
      std::cin >> page;
      tree.Add(page, page);
    } else {
      long long user;
      std::cin >> user;
      std::cout << tree.GetSum(0, user + 1) << '\n';
    }
  }
}