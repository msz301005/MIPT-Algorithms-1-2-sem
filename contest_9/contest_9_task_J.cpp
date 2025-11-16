#include <bits/stdc++.h>

std::vector<std::vector<int>> g;
std::vector<bool> used;
std::vector<int> match;

bool Augment(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (auto to : g[v]) {
    if (match[to] == -1 || Augment(match[to])) {
      match[to] = v;
      return true;
    }
  }
  return false;
}

void Kuhn(int n) {
  for (int i = 0; i < n; ++i) {
    if (Augment(i)) {
      used.assign(n, false);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  g.resize(n);
  match.resize(n, -1);
  used.resize(n);
  while (m-- > 0) {
    int u;
    int v;
    std::cin >> u >> v;
    g[--u].push_back(--v);
  }
  Kuhn(n);
  std::cout << std::count(match.begin(), match.end(), -1);
}