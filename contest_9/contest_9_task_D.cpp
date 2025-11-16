#include <bits/stdc++.h>
std::vector<std::vector<int>> g;
std::vector<std::vector<int>> up;
std::vector<int> tin;
std::vector<int> tout;
int timer;
int l = 1;

void Dfs(int v, int p = 0) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (int i = 1; i <= l; i++) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (auto u : g[v]) {
    if (u != p) {
      Dfs(u, v);
    }
  }
  tout[v] = timer;
}

bool Upper(int a, int b) { return tin[a] <= tin[b] && tout[a] >= tout[b]; }

int MinPath(int v, int u) {
  int res = 0;
  int ok1 = 0;
  int ok2 = 0;
  if (!Upper(v, u)) {
    ok1 = 1;
    for (int i = l; i >= 0; --i) {
      if (!Upper(up[v][i], u)) {
        res += (1 << i);
        v = up[v][i];
      }
    }
  }
  if (!Upper(u, v)) {
    ok2 = 1;
    for (int i = l; i >= 0; --i) {
      if (!Upper(up[u][i], v)) {
        res += (1 << i);
        u = up[u][i];
      }
    }
  }
  return res + ok1 + ok2;
}

int main() {
  int n;
  std::cin >> n;
  g.resize(n);
  tin.resize(n);
  tout.resize(n);
  up.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int first;
    int second;
    std::cin >> first >> second;
    g[--first].push_back(--second);
    g[second].push_back(first);
  }
  while ((1 << l) <= n) {
    ++l;
  }
  for (int i = 0; i < n; i++) {
    up[i].resize(l + 1);
  }
  Dfs(0);
  int q;
  std::cin >> q;
  while (q-- > 0) {
    int u;
    int v;
    std::cin >> u >> v;
    std::cout << MinPath(--u, --v) << '\n';
  }
}