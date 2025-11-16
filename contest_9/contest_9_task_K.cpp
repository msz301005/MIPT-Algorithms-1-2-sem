#include <bits/stdc++.h>
struct Edge {
  int v;
  int flow;
  int cap;
  Edge() = default;
  Edge(int v, int cap) : v(v), flow(0), cap(cap) {}
  int ResidualCap() const { return cap - flow; }
};

int s;
int t;
std::vector<Edge> edges;
std::vector<std::vector<int>> g;
std::vector<int> used;
int timer = 1;

int Dfs(int v, int min_cap = INT_MAX) {
  if (v == t) {
    return min_cap;
  }
  used[v] = timer;
  for (auto& i : g[v]) {
    if (edges[i].ResidualCap() == 0 || used[edges[i].v] == timer) {
      continue;
    }
    int add_flow = Dfs(edges[i].v, std::min(min_cap, edges[i].ResidualCap()));
    if (add_flow != 0) {
      edges[i].flow += add_flow;
      edges[i ^ 1].flow -= add_flow;
      return add_flow;
    }
  }
  return 0;
}
int main() {
  int n;
  int m;
  std::cin >> n >> m;
  s = 0;
  t = n - 1;
  g.resize(n);
  used.resize(n);
  while (m-- > 0) {
    int v;
    int u;
    int cap;
    std::cin >> v >> u >> cap;
    g[--v].emplace_back(edges.size());
    edges.emplace_back(--u, cap);
    g[u].emplace_back(edges.size());
    edges.emplace_back(v, 0);
  }
  while (Dfs(s) != 0) {
    ++timer;
  }
  int ans = 0;
  for (auto& i : g[s]) {
    ans += edges[i].flow;
  }
  std::cout << ans;
}