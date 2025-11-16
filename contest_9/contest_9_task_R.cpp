#include <bits/stdc++.h>

const int cInf = INT_MAX;

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i + 1][j + 1];
    }
  }
  std::vector<int> u(n + 1);
  std::vector<int> v(n + 1);
  std::vector<int> p(n + 1);
  std::vector<int> way(n + 1);
  for (int i = 1; i <= n; ++i) {
    p[0] = i;
    int j0 = 0;
    std::vector<int> min_v(n + 1, cInf);
    std::vector<char> used(n + 1);
    do {
      used[j0] = 1;
      int i0 = p[j0];
      int delta = cInf;
      int col = 0;
      for (int j = 1; j <= n; ++j) {
        if (used[j] == 0) {
          int cur = a[i0][j] - u[i0] - v[j];
          if (cur < min_v[j]) {
            min_v[j] = cur;
            way[j] = j0;
          }
          if (min_v[j] < delta) {
            delta = min_v[j];
            col = j;
          }
        }
      }
      for (int j = 0; j <= n; ++j) {
        if (used[j] == 1) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          min_v[j] -= delta;
        }
      }
      j0 = col;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0 != 0);
  }
  std::cout << -v[0] << '\n';
  std::vector<int> ans(n + 1);
  for (int i = 1; i <= n; ++i) {
    ans[p[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << i << ' ' << ans[i] << '\n';
  }
}