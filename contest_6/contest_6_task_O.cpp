#include <bits/stdc++.h>
const int kInf = 1e9;
int num;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> path;
template <typename Type>
void FindShortest(Type& dp, int mask) {
  for (int mask0 = 1; mask0 <= mask; mask0++) {
    for (int i = 0; i < num; i++) {
      if ((mask0 & (1 << i)) != 0) {
        for (int j = 0; j < num; j++) {
          if ((mask0 & (1 << j)) != 0 &&
              dp[i][mask0] > dp[j][mask0 ^ (1 << i)] + graph[j][i]) {
            dp[i][mask0] = dp[j][mask0 ^ (1 << i)] + graph[j][i];
            path[i][mask0] = j;
          }
        }
      }
    }
  }
  int mi = kInf;
  int city = -1;
  for (int i = 0; i < num; ++i) {
    if (mi > dp[i][mask]) {
      mi = dp[i][mask];
      city = i;
    }
  }
  std::cout << dp[city][mask] << '\n';
  while (mask != 0) {
    if (city != 0) {
      std::cout << city << ' ';
    }
    int prev_city = path[city][mask];
    mask ^= (1 << city);
    city = prev_city;
  }
}
void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}
int main() {
  Speed();
  std::cin >> num;
  ++num;
  graph.resize(num, std::vector<int>(num));
  for (int i = 1; i < num; ++i) {
    for (int j = 1; j < num; ++j) {
      std::cin >> graph[i][j];
    }
  }
  std::vector<std::vector<int>> dp(num, std::vector<int>((1 << num), kInf));
  path.resize(num, std::vector<int>((1 << num), kInf));
  dp[0][0] = 0;
  FindShortest(dp, (1 << num) - 1);
}