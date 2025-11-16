#include <bits/stdc++.h>
const int cKInf = 1e5;
struct Edge {
  int s;
  int to;
  int w;
  Edge(int s, int to, int w) : s(s), to(to), w(w) {}
};
void FordBellman(int n, const std::vector<Edge>& graph) {
  std::vector<int> d(n, cKInf);
  std::vector<int> p(n, -1);
  d[0] = 0;
  int v;
  bool updated = false;
  for (int i = 0; i < n; ++i) {
    updated = false;
    for (auto [s, to, w] : graph) {
      if (d[to] > d[s] + w) {
        d[to] = d[s] + w;
        p[to] = s;
        v = to;
        updated = true;
      }
    }
  }
  if (!updated) {
    std::cout << "NO";
  } else {
    std::cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      v = p[v];
    }
    std::vector<int> path;
    for (int u = v;; u = p[u]) {
      path.push_back(u);
      if (u == v && path.size() > 1) {
        break;
      }
    }
    reverse(path.begin(), path.end());
    std::cout << path.size() << '\n';
    for (auto& elem : path) {
      std::cout << elem + 1 << ' ';
    }
  }
}
int main() {
  int n;
  std::cin >> n;
  std::vector<Edge> graph;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;
      if (w != cKInf) {
        graph.emplace_back(i, j, w);
      }
    }
  }
  FordBellman(n, graph);
}