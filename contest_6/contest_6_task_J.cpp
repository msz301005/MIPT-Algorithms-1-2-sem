#include <bits/stdc++.h>
const long long kMod = 1e9 + 7;
const long long kMax = 1e6 + 7;
int main() {
  long long nn;
  std::cin >> nn;
  std::vector<long long> arr(nn);
  for (auto& elem : arr) {
    std::cin >> elem;
  }
  std::vector<long long> pos(kMax, -1);
  std::vector<long long> dp(nn, 1);
  long long sum = 1;
  pos[arr[0]] = 0;
  for (int i = 1; i < nn; ++i) {
    dp[i] = (1 + sum + kMod) % kMod;
    if (pos[arr[i]] != -1) {
      sum -= dp[pos[arr[i]]];
      dp[pos[arr[i]]] = 0;
    }
    pos[arr[i]] = i;
    sum = (sum + dp[i] + kMod) % kMod;
  }
  sum = 0;
  for (auto& elem : dp) {
    sum = (sum + elem + kMod) % kMod;
  }
  std::cout << sum;
}