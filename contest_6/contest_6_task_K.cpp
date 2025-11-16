#include <bits/stdc++.h>

template <typename Type>
void KnapsackProblem(int mass, std::vector<Type>& dp, const Type& weight,
                     const Type& cost) {
  int num = static_cast<int>(weight.size()) - 1;
  for (int i = 1; i <= num; i++) {
    for (int j = 1; j <= mass; j++) {
      if (j >= weight[i]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i]] + cost[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
}

template <typename Type>
void GetAnswer(int mass, const std::vector<Type>& dp, const Type& weight) {
  Type ans;
  int num = static_cast<int>(dp.size()) - 1;
  for (int i = num; i > 0; i--) {
    if (dp[i][mass] != dp[i - 1][mass]) {
      ans.push_back(i);
      mass -= weight[i];
    }
  }
  for (auto& elem : ans) {
    std::cout << elem << ' ';
  }
}

int main() {
  int num;
  int mass;
  std::cin >> num >> mass;
  std::vector<int> weight(num + 1);
  std::vector<int> cost(num + 1);
  for (int i = 1; i <= num; i++) {
    std::cin >> weight[i];
  }
  for (int i = 1; i <= num; i++) {
    std::cin >> cost[i];
  }
  std::vector<std::vector<int>> dp(num + 1, std::vector<int>(mass + 1));
  KnapsackProblem(mass, dp, weight, cost);
  GetAnswer(mass, dp, weight);
}