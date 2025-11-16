#include <bits/stdc++.h>
void Solve(int number, int cnt_airplanes) {
  std::vector<int> dp(cnt_airplanes + 1);
  dp[0] = dp[1] = 1;
  for (int ans = 2; ans <= number; ++ans) {
    int sum = 0;
    for (auto& elem : dp) {
      sum += elem;
    }
    if (sum >= number) {
      std::cout << ans - 1;
      return;
    }
    std::vector<int> new_dp(cnt_airplanes + 1);
    new_dp[0] = 1;
    for (int i = 1; i <= cnt_airplanes; ++i) {
      new_dp[i] = dp[i] + dp[i - 1];
    }
    dp = new_dp;
  }
}
int main() {
  int number;
  int cnt_airplanes;
  std::cin >> number >> cnt_airplanes;
  if (number == 1) {
    std::cout << 0;
  } else if (cnt_airplanes == 0) {
    std::cout << -1;
  } else {
    Solve(number, cnt_airplanes);
  }
}