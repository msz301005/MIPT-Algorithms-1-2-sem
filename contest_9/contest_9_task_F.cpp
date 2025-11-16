#include <bits/stdc++.h>

struct Kar {
  char type;
  int u;
  int v;
  Kar() = default;
  Kar(char type, int u, int v) : type(type), u(u), v(v) {}
};

std::vector<std::vector<int>> g;
std::vector<std::vector<int>> up;
std::vector<int> tin;
std::vector<int> tout;
std::vector<int> parent;
int timer;
int l = 1;

int Get(int a) {
  if (a == parent[a]) {
    return a;
  }
  return parent[a] = Get(parent[a]);
}

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

int Lca(int v, int u) {
  if (Upper(v, u)) {
    return v;
  }
  if (Upper(u, v)) {
    return u;
  }
  for (int i = l; i >= 0; --i) {
    if (!Upper(up[v][i], u)) {
      v = up[v][i];
    }
  }
  return up[v][0];
}

int main() {
  int n = 1;
  int q;
  std::cin >> q;
  std::vector<Kar> tree(q);
  for (auto& elem : tree) {
    std::cin >> elem.type;
    if (elem.type == '?') {
      std::cin >> elem.u;
      --elem.u;
    } else if (elem.type == '+') {
      ++n;
    }
    std::cin >> elem.v;
    --elem.v;
  }
  g.resize(n);
  tin.resize(n);
  tout.resize(n);
  up.resize(n);
  n = 1;
  for (auto& elem : tree) {
    if (elem.type == '+') {
      g[elem.v].push_back(n);
      g[n++].push_back(elem.v);
    }
  }

  while ((1 << l) <= n) {
    ++l;
  }
  for (int i = 0; i < n; i++) {
    up[i].resize(l + 1);
  }
  parent.resize(n);
  std::iota(parent.begin(), parent.end(), 0);
  Dfs(0);
  for (auto& elem : tree) {
    if (elem.type == '-') {
      parent[elem.v] = up[elem.v][0];
    } else if (elem.type == '?') {
      std::cout << Get(Lca(elem.v, elem.u)) + 1 << '\n';
    }
  }
}