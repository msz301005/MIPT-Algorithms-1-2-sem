#include <bits/stdc++.h>
struct Edge {
  long long v;
  long long flow;
  long long cap;
  Edge() = default;
  Edge(long long v, long long cap) : v(v), flow(0), cap(cap) {}
  long long ResidualCap() const { return cap - flow; }
};

long long s;
long long t;
std::vector<Edge> edges;
std::vector<std::vector<long long>> g;
std::vector<long long> used;
long long timer = 1;

long long DfsFordFulkerson(long long v, long long min_cap = INT_MAX) {
  if (v == t) {
    return min_cap;
  }
  used[v] = timer;
  for (auto& i : g[v]) {
    if (edges[i].ResidualCap() == 0 || used[edges[i].v] == timer) {
      continue;
    }
    long long add_flow =
        DfsFordFulkerson(edges[i].v, std::min(min_cap, edges[i].ResidualCap()));
    if (add_flow != 0) {
      edges[i].flow += add_flow;
      edges[i ^ 1].flow -= add_flow;
      return add_flow;
    }
  }
  return 0;
}

std::set<long long> first;

void Dfs(long long v) {
  used[v] = 1;
  first.insert(v);
  for (auto& i : g[v]) {
    if (used[edges[i].v] == 0 && edges[i].flow < edges[i].cap) {
      Dfs(edges[i].v);
    }
  }
}

bool Find(long long value) { return first.find(value) != first.end(); }

int main() {
  long long n;
  long long m;
  std::cin >> n >> m;
  s = 0;
  t = n - 1;
  g.resize(n);
  used.resize(n);
  while (m-- > 0) {
    long long v;
    long long u;
    long long cap;
    std::cin >> v >> u >> cap;
    g[--v].emplace_back(edges.size());
    edges.emplace_back(--u, cap);
    g[u].emplace_back(edges.size());
    edges.emplace_back(v, cap);
  }
  while (DfsFordFulkerson(s) != 0) {
    ++timer;
  }
  long long ans = 0;
  for (auto& i : g[s]) {
    ans += edges[i].flow;
  }
  std::vector<long long> min_cut;
  used.assign(n, 0);
  Dfs(s);
  for (long long i = 0; i < static_cast<long long>(edges.size()); i += 2) {
    if ((Find(edges[i + 1].v) && !Find(edges[i].v)) ||
        (Find(edges[i].v) && !Find(edges[i + 1].v))) {
      min_cut.push_back(i / 2 + 1);
    }
  }
  std::cout << min_cut.size() << ' ' << ans << '\n';
  for (auto& elem : min_cut) {
    std::cout << elem << ' ';
  }
}