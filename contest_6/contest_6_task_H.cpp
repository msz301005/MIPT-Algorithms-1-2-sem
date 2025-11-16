#include <bits/stdc++.h>
int main() {
  std::string dance_a;
  std::string dance_b;
  std::cin >> dance_a >> dance_b;
  int size_a = dance_a.size();
  int size_b = dance_b.size();
  std::vector<std::vector<int>> dp(size_a + 1, std::vector<int>(size_b + 1, 0));
  for (int i = 1; i <= size_a; i++) {
    for (int j = 1; j <= size_b; j++) {
      if (dance_a[i - 1] == dance_b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  std::vector<int> pos_a;
  std::vector<int> pos_b;
  for (int i = size_a, j = size_b; i > 0 && j > 0;) {
    if (dance_a[i - 1] == dance_b[j - 1]) {
      pos_a.push_back(i--);
      pos_b.push_back(j--);
    } else if (dp[i - 1][j] == dp[i][j]) {
      --i;
    } else {
      --j;
    }
  }
  reverse(pos_a.begin(), pos_a.end());
  reverse(pos_b.begin(), pos_b.end());
  std::cout << pos_b.size() << '\n';
  for (auto& elem : pos_a) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
  for (auto& elem : pos_b) {
    std::cout << elem << ' ';
  }
}