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
std::vector<std::vector<long long>> g;
std::vector<long long> used;
int timer = 1;

int DfsFordFulkerson(int v, int min_cap = INT_MAX) {
  if (v == t) {
    return min_cap;
  }
  used[v] = timer;
  for (auto& i : g[v]) {
    if (edges[i].ResidualCap() == 0 || used[edges[i].v] == timer) {
      continue;
    }
    int add_flow =
        DfsFordFulkerson(edges[i].v, std::min(min_cap, edges[i].ResidualCap()));
    if (add_flow != 0) {
      edges[i].flow += add_flow;
      edges[i ^ 1].flow -= add_flow;
      return add_flow;
    }
  }
  return 0;
}

int NumberOfVertex(int m, int i, int j) { return i * m + j; }

void Add(int v, int u, int cap) {
  g[v].emplace_back(edges.size());
  edges.emplace_back(u, cap);
  g[u].emplace_back(edges.size());
  edges.emplace_back(v, cap);
}

void Add1(int v, int u, int cap) {
  g[v].emplace_back(edges.size());
  edges.emplace_back(u, cap);
  g[u].emplace_back(edges.size());
  edges.emplace_back(v, 0);
}

std::set<int> res;
std::vector<int> can_blocked;
int n;
int m;
void Dfs(int v) {
  used[v] = 1;
  if (std::binary_search(can_blocked.begin(), can_blocked.end(), v)) {
    res.insert(v);
  }
  for (auto& i : g[v]) {
    if (used[edges[i].v] == 0 && edges[i].ResidualCap() > 0) {
      Dfs(edges[i].v);
    }
  }
}

int main() {
  int k;
  int l;
  std::cin >> m >> n >> k >> l;
  g.resize(2 * n * m);
  used.resize(2 * n * m);
  std::vector<std::pair<int, int>> blocked(k);
  for (auto& elem : blocked) {
    std::cin >> elem.first >> elem.second;
    --elem.first;
    --elem.second;
  }
  for (int i = 0; i < l; ++i) {
    int first;
    int second;
    std::cin >> first >> second;
    can_blocked.push_back(NumberOfVertex(n, --first, --second));
  }
  std::sort(can_blocked.begin(), can_blocked.end());
  std::sort(blocked.begin(), blocked.end());
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (std::binary_search(blocked.begin(), blocked.end(),
                             std::make_pair(i, j))) {
        continue;
      }
      Add(NumberOfVertex(n, i, j), n * m + NumberOfVertex(n, i, j), 1);
      if (j + 1 < n && !std::binary_search(blocked.begin(), blocked.end(),
                                           std::make_pair(i, j + 1))) {
        Add(n * m + NumberOfVertex(n, i, j), NumberOfVertex(n, i, j + 1), 1);
      }
      if (j - 1 >= 0 && !std::binary_search(blocked.begin(), blocked.end(),
                                            std::make_pair(i, j - 1))) {
        Add(n * m + NumberOfVertex(n, i, j), NumberOfVertex(n, i, j - 1), 1);
      }
      if (i + 1 < m && !std::binary_search(blocked.begin(), blocked.end(),
                                           std::make_pair(i + 1, j))) {
        Add(n * m + NumberOfVertex(n, i, j), NumberOfVertex(n, i + 1, j), 1);
      }
      if (i - 1 >= 0 && !std::binary_search(blocked.begin(), blocked.end(),
                                            std::make_pair(i - 1, j))) {
        Add(n * m + NumberOfVertex(n, i, j), NumberOfVertex(n, i - 1, j), 1);
      }
    }
  }
  std::pair<int, int> begin;
  std::pair<int, int> end;
  std::cin >> begin.first >> begin.second >> end.first >> end.second;
  s = n * m + NumberOfVertex(n, --begin.first, --begin.second);
  t = NumberOfVertex(n, --end.first, --end.second);
  while (DfsFordFulkerson(s) != 0) {
    ++timer;
  }
  int ans = 0;
  for (auto& i : g[s]) {
    ans += edges[i].flow;
  }
  if (ans > l) {
    std::cout << -1;
    return 0;
  }
  used.assign(2 * n * m, 0);
  Dfs(s);
  std::cout << ans << '\n';
  std::vector<int> res1(res.begin(), res.end());
  for (auto& elem : res1) {
    // if (std::binary_search(can_blocked.begin(), can_blocked.end(), elem)) {
    std::cout << elem / n + 1 << ' ' << elem % n + 1 << '\n';
    // }
  }
}