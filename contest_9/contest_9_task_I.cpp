#include <bits/stdc++.h>

struct Edge {
  int v;
  int u;
  Edge(int v, int u) : v(v), u(u) {}
};

class Graph {
 public:
  Graph(int n, int m) : n_(n), m_(m) {
    g_.resize(n + m);
    used_left_.resize(m);
    used_right_.resize(n);
  }

  std::vector<int>& operator[](size_t ind) { return g_[ind]; }

  const std::vector<int>& operator[](size_t ind) const { return g_[ind]; }

  void DfsForLeft(const std::vector<int>& matching) {
    for (int i = 0; i < m_; ++i) {
      if (matching[i] == 0 && !GetUsedLeft(i)) {
        Dfs(i);
      }
    }
  }

  bool GetUsedLeft(int i) const { return used_left_[i]; }

  bool GetUsedRight(int i) const { return used_right_[i]; }

  void Print(const std::vector<int>& matching) const {
    std::cout << m_ - std::count(matching.begin(), matching.end(), 0) << '\n';
    std::vector<int> left_minus;
    std::vector<int> right_plus;
    for (int i = 0; i < m_; ++i) {
      if (!GetUsedLeft(i)) {
        left_minus.push_back(i);
      }
    }
    for (int i = 0; i < n_; ++i) {
      if (GetUsedRight(i)) {
        right_plus.push_back(i);
      }
    }

    std::cout << left_minus.size() << ' ';
    for (auto& elem : left_minus) {
      std::cout << ++elem << ' ';
    }
    std::cout << '\n';

    std::cout << right_plus.size() << ' ';
    for (auto& elem : right_plus) {
      std::cout << ++elem << ' ';
    }
  }

 private:
  std::_Bit_reference UsedElem(int v, int part) {
    return (part == 0 ? used_left_[v] : used_right_[v - m_]);
  }

  void Dfs(int v, int part = 0) {
    UsedElem(v, part) = true;
    for (auto u : g_[v]) {
      if (!UsedElem(u, (part + 1) % 2)) {
        Dfs(u, (part + 1) % 2);
      }
    }
  }
  std::vector<std::vector<int>> g_;
  std::vector<bool> used_left_;
  std::vector<bool> used_right_;
  int n_;
  int m_;
};

int main() {
  int m;
  int n;
  std::cin >> m >> n;
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int k;
    std::cin >> k;
    while (k-- > 0) {
      int u;
      std::cin >> u;
      edges.emplace_back(i, --u + m);
    }
  }
  std::vector<int> matching(m);
  for (auto& elem : matching) {
    std::cin >> elem;
    if (elem != 0) {
      elem += m - 1;
    }
  }
  Graph g(n, m);
  for (auto edge : edges) {
    if (matching[edge.v] != edge.u) {
      g[edge.v].push_back(edge.u);
    } else {
      g[edge.u].push_back(edge.v);
    }
  }
  g.DfsForLeft(matching);
  g.Print(matching);
}