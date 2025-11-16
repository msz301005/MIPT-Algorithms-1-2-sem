#include <bits/stdc++.h>

class Dsu {
 public:
  Dsu(int n) {
    p_.resize(n);
    sz_.resize(n, 1);
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Root(int a) {
    if (a == p_[a]) {
      return a;
    }
    return p_[a] = Root(p_[a]);
  }

  void Unite(int a, int b) {
    a = Root(a);
    b = Root(b);
    if (a == b) {
      return;
    }
    if (sz_[a] < sz_[b]) {
      std::swap(a, b);
    }
    p_[b] = a;
    sz_[a] += sz_[b];
  }

 private:
  std::vector<int> p_;
  std::vector<int> sz_;
};

struct Kar {
  std::string s;
  int u;
  int v;
};

int main() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  Dsu dsu(n);
  for (int i = 0; i < m; ++i) {
    int d;
    std::cin >> d >> d;
  }
  std::vector<Kar> query(k);
  std::vector<std::string> ans;
  for (auto& elem : query) {
    std::cin >> elem.s >> elem.u >> elem.v;
    --elem.u;
    --elem.v;
  }
  std::reverse(query.begin(), query.end());
  for (auto& elem : query) {
    if (elem.s == "ask") {
      ans.emplace_back(dsu.Root(elem.u) == dsu.Root(elem.v) ? "YES" : "NO");
    } else {
      dsu.Unite(elem.u, elem.v);
    }
  }
  std::reverse(ans.begin(), ans.end());
  for (auto& elem : ans) {
    std::cout << elem << '\n';
  }
}