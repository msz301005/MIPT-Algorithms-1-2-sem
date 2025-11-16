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
  int l;
  int r;
  std::cin >> l >> r;
  g.resize(l);
  match.resize(r, -1);
  used.resize(l);
  for (int i = 0; i < l; ++i) {
    int word;
    while (std::cin >> word && word != 0) {
      g[i].push_back(word - 1);
    }
  }
  Kuhn(l);
  std::cout << r - std::count(match.begin(), match.end(), -1) << '\n';
  for (int i = 0; i < r; ++i) {
    if (match[i] != -1) {
      std::cout << match[i] + 1 << ' ' << i + 1 << '\n';
    }
  }
}