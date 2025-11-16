#include <bits/stdc++.h>
long long stupid(int& num) {
  std::vector<std::vector<long long>> dp(num + 1,
                                         std::vector<long long>(num + 1));
  std::vector<std::vector<long long>> prev(num + 1,
                                           std::vector<long long>(num + 1));
  for (long long j = 1; j <= num; ++j) {
    dp[j][j] = 1;
  }
  for (long long i = 1; i <= num; ++i) {
    for (long long j = 1; j <= num; ++j) {
      prev[i][j] = dp[i][j] + prev[i][j - 1];
    }
  }
  long long sum;
  for (long long i = 2; i <= num; ++i) {
    for (long long j = 2; j <= i; ++j) {
      dp[i][j] += prev[i - j][j / 2];
    }
    for (long long j = 1; j <= num; ++j) {
      prev[i][j] = dp[i][j] + prev[i][j - 1];
    }
  }
  sum = 0;
  for (long long j = 0; j <= num; ++j) {
    sum += dp[num][j];
  }
  /*for (int i = 1; i <= num; ++i) {
    for (int j = 1; j <= num; ++j) {
      std::cout << dp[i][j] << ' ';
    }
    std::cout << '\n';
  }*/
  return sum;
}
long long clever(int& num) {
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
  /*for (int i = 1; i <= num; ++i) {
    for (int j = 1; j <= num; ++j) {
      std::cout << dp[i][j] << ' ';
    }
    std::cout << '\n';
  }*/
  return sum;
}
int main() {
  for(int num = 1; num <= 1000; ++num) {
    int Stupid = stupid(num);
    int Clever = clever(num);
    if(Stupid != Clever) {
      std::cout << num;
      return 0;
    }
  }
}