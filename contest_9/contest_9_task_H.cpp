#include <bits/stdc++.h>

std::vector<std::vector<long long>> g;
std::vector<bool> used;
std::vector<long long> match;

long long NumberOfVertex(long long m, long long i, long long j) {
  return i * m + j;
}

bool Augment(long long v) {
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

void Kuhn(long long n, long long m) {
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < m; ++j) {
      if (Augment(NumberOfVertex(m, i, j))) {
        used.assign(n * m, false);
      }
    }
  }
}

int main() {
  long long n;
  long long m;
  long long a;
  long long b;
  long long cnt = 0;
  std::cin >> n >> m >> a >> b;
  std::vector<std::string> table(n);
  g.resize(n * m);
  used.resize(n * m);
  for (auto& str : table) {
    std::cin >> str;
    for (auto& elem : str) {
      elem = (elem == '.' ? '*' : '.');
    }
    cnt += std::count(str.begin(), str.end(), '.');
  }
  if (2 * b <= a) {
    std::cout << cnt * b;
    return 0;
  }
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < m; ++j) {
      if (table[i][j] == '*' || (i + j) % 2 != 0) {
        continue;
      }
      if (j + 1 < m && table[i][j + 1] == '.') {
        g[NumberOfVertex(m, i, j)].push_back(NumberOfVertex(m, i, j + 1));
      }
      if (j - 1 >= 0 && table[i][j - 1] == '.') {
        g[NumberOfVertex(m, i, j)].push_back(NumberOfVertex(m, i, j - 1));
      }
      if (i + 1 < n && table[i + 1][j] == '.') {
        g[NumberOfVertex(m, i, j)].push_back(NumberOfVertex(m, i + 1, j));
      }
      if (i - 1 >= 0 && table[i - 1][j] == '.') {
        g[NumberOfVertex(m, i, j)].push_back(NumberOfVertex(m, i - 1, j));
      }
    }
  }
  used.assign(n * m, false);
  match.resize(n * m, -1);
  Kuhn(n, m);
  long long cnt1 =
      static_cast<long long>(std::count(match.begin(), match.end(), -1));
  std::cout << (n * m - cnt1) * a + (cnt - 2 * (n * m - cnt1)) * b;
}