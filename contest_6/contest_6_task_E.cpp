#include <bits/stdc++.h>
int main() {
  int num;
  std::cin >> num;
  std::vector<std::vector<long long>> dp(num + 1,
                                         std::vector<long long>(num + 1));
  for (int i = 1; i <= num; ++i) {
    dp[i][i] = 1;
  }
  for (int i = 2; i <= num; ++i) {
    for (int j = 2; j <= i; ++j) {
      for (int k = 1; k <= j / 2; ++k) {
        dp[i][j] += dp[i - j][k];
      }
    }
  }
  long long sum = 0;
  for (auto& elem : dp[num]) {
    sum += elem;
  }
  std::cout << sum;
}