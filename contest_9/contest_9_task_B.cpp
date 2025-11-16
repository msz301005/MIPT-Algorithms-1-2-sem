#include <bits/stdc++.h>
int Root(std::vector<int>& par, int a) {
  if (a == par[a]) {
    return a;
  }
  return par[a] = Root(par, par[a]);
}
void Unite(std::vector<int>& par, std::vector<int>& sz, int a, int b) {
  a = Root(par, a);
  b = Root(par, b);
  if (a == b) {
    return;
  }
  if (sz[a] < sz[b]) {
    std::swap(a, b);
  }
  par[b] = a;
}
int main() {
  int n;
  int m;
  int ans = 0;
  std::cin >> n >> m;
  std::vector<int> par(n + 1);
  std::vector<int> sz(n + 1);
  std::vector<std::pair<int, std::pair<int, int>>> arr(m);
  for (int i = 0; i < m; i++) {
    std::cin >> arr[i].second.first >> arr[i].second.second >> arr[i].first;
  }
  std::sort(arr.begin(), arr.end());
  for (int i = 0; i < n; i++) {
    par[i] = i;
  }
  for (int i = 0; i < m; i++) {
    int a = arr[i].second.first;
    int b = arr[i].second.second;
    int l = arr[i].first;
    if (Root(par, a) != Root(par, b)) {
      ans += l;
      Unite(par, sz, a, b);
    }
  }
  std::cout << ans;
}