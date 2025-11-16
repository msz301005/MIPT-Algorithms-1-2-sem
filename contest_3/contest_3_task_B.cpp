#include <bits/stdc++.h>
class Segtree {
 public:
  Segtree(std::vector<int>::iterator ptr_begin,
          std::vector<int>::iterator ptr_end) {
    tree_.resize(4 * (ptr_end - ptr_begin));
    ptr_arr_ = ptr_begin;
    Build(0, 0, ptr_end - ptr_begin);
  }

  void Build(int ver, int left, int right) {
    if (left + 1 == right) {
      tree_[ver] = *(ptr_arr_ + left);
      return;
    }
    int mid = (left + right) / 2;
    Build(2 * ver + 1, left, mid);
    Build(2 * ver + 2, mid, right);
    tree_[ver] = tree_[2 * ver + 1] + tree_[2 * ver + 2];
  }

  int Get(int ver, int tl, int tr, int left, int right) {
    if (right <= tl || tr <= left) {
      return 0;
    }
    if (left <= tl && tr <= right) {
      return tree_[ver];
    }
    int tm = (tl + tr) / 2;
    return Get(2 * ver + 1, tl, tm, left, right) +
           Get(2 * ver + 2, tm, tr, left, right);
  }

  void Update(int ver, int tl, int tr, int pos, int val) {
    if (pos < tl || tr <= pos) {
      return;
    }
    if (tl == tr - 1) {
      tree_[ver] = val;
      return;
    }
    int tm = (tl + tr) / 2;
    Update(2 * ver + 1, tl, tm, pos, val);
    Update(2 * ver + 2, tm, tr, pos, val);
    tree_[ver] = tree_[2 * ver + 1] + tree_[2 * ver + 2];
  }

 private:
  std::vector<int> tree_;
  std::vector<int>::iterator ptr_arr_;
};
bool operator<(std::pair<int, int> a, std::pair<int, int> b) {
  return (a.first < b.first && b.second < a.second);
}
int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> a(n);
  for (auto& elem : a) {
    std::cin >> elem.first >> elem.second;
  }
  std::sort(a.begin(), a.end());
  for (auto& elem : a) {
    std::cout << elem.first << ' ' << elem.second << '\n';
  }
  //std::cout << std::lower_bound(a.begin(), a.end(), std::make_pair(1, 4)) - a.begin();
  std::cout << (std::make_pair(1,3) < std::make_pair(1,4));
}