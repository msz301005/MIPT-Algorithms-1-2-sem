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
std::vector<long long> level;
std::vector<long long> ptr;
std::queue<long long> q;

void Add(long long v, long long u, long long cap) {
  g[v].emplace_back(edges.size());
  edges.emplace_back(u, cap);
  g[u].emplace_back(edges.size());
  edges.emplace_back(v, 0);
}

bool Bfs() {
  while (!q.empty()) {
    long long v = q.front();
    q.pop();
    for (auto& i : g[v]) {
      if (edges[i].ResidualCap() < 1 || level[edges[i].v] != -1) {
        continue;
      }
      level[edges[i].v] = level[v] + 1;
      q.push(edges[i].v);
    }
  }
  return level[t] != -1;
}

long long Dfs(long long v, long long min_cap = INT_MAX) {
  if (min_cap == 0) {
    return 0;
  }
  if (v == t) {
    return min_cap;
  }
  for (long long& i = ptr[v]; i < (long long)g[v].size(); ++i) {
    long long id = g[v][i];
    long long u = edges[id].v;
    if (level[v] + 1 != level[u] || edges[id].ResidualCap() < 1) {
      continue;
    }
    long long x = Dfs(u, std::min(min_cap, edges[id].ResidualCap()));
    if (x != 0) {
      edges[id].flow += x;
      edges[id ^ 1].flow -= x;
      return x;
    }
  }
  return 0;
}

int main() {
  long long n;
  long long m;
  std::cin >> n >> m;
  s = 0;
  t = n - 1;
  g.resize(n);
  level.resize(n, -1);
  ptr.resize(n);
  while (m-- > 0) {
    long long v;
    long long u;
    long long cap;
    std::cin >> v >> u >> cap;
    Add(v - 1, u - 1, cap);
  }
  long long ans = 0;
  for (;;) {
    std::fill(level.begin(), level.end(), -1);
    level[s] = 0;
    q.push(s);
    if (!Bfs()) {
      break;
    }
    std::fill(ptr.begin(), ptr.end(), 0);
    for (long long min_cap = Dfs(s); min_cap != 0; min_cap = Dfs(s)) {
      ans += min_cap;
    }
  }
  std::cout << ans << '\n';
  for (long long i = 0; i < (int)edges.size(); i += 2) {
    std::cout << edges[i].flow << '\n';
  }
}