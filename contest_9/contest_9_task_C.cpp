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

struct Edge {
  int from, to, w;
  Edge(int from, int to, int w) : from(from), to(to), w(w) {}
};

bool Comp(const Edge& first, const Edge& second) { return first.w < second.w; }

int Mst(int n, std::vector<Edge>& g) {
  int ans = 0;
  Dsu dsu(n + 1);
  std::sort(g.begin(), g.end(), Comp);
  for (auto [u, v, w] : g) {
    if (dsu.Root(u) != dsu.Root(v)) {
      ans += w;
      dsu.Unite(u, v);
    }
  }
  return ans;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Edge> g;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;
      g.emplace_back(i + 1, j + 1, w);
    }
  }
  for (int i = 0; i < n; ++i) {
    int cost;
    std::cin >> cost;
    g.emplace_back(0, i + 1, cost);
  }
  std::cout << Mst(n, g);
}