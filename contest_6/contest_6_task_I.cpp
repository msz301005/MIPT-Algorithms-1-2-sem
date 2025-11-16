#include <bits/stdc++.h>
int main() {
  int nn;
  int mm;
  std::cin >> nn >> mm;
  std::vector<int> cj(nn);
  std::vector<int> dj(mm);
  for (auto& elem : cj) {
    std::cin >> elem;
  }
  for (auto& elem : dj) {
    std::cin >> elem;
  }
  std::vector<std::vector<int>> dp(nn + 1, std::vector<int>(mm + 1));
  for (int i = 1; i <= nn; ++i) {
    int best = 0;
    for (int j = 1; j <= mm; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (cj[i - 1] == dj[j - 1] && dp[i - 1][j] < best + 1) {
        dp[i][j] = best + 1;
      }
      if (cj[i - 1] > dj[j - 1] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
      }
    }
  }
  std::cout << *std::max_element(dp[nn].begin(), dp[nn].end());
}