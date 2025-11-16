#include <bits/stdc++.h>
int main() {
  int num;
  int mum;
  std::cin >> num >> mum;
  std::vector<int> homes(num + 1);
  std::vector<int> pref(num + 1);
  for (int i = 1; i <= num; ++i) {
    std::cin >> homes[i];
    pref[i] = pref[i - 1] + homes[i];
  }
  std::vector<std::vector<int>> dp(num + 1, std::vector<int>(mum + 1, INT_MAX));
  std::vector<std::vector<int>> parent(num + 1, std::vector<int>(mum + 1, -1));
  for (int i = 1; i <= num; ++i) {
    dp[i][1] =
        i * homes[i] - pref[i] + pref[num] - pref[i] - (num - i) * homes[i];
  }
  for (int j = 2; j <= mum; ++j) {
    for (int i = j; i <= num; ++i) {
      for (int k = j - 1; k < i; ++k) {
        int mid = (homes[i] + homes[k]) / 2;
        int pos_l = std::upper_bound(homes.begin(), homes.end(), mid) -
                    homes.begin() - 1;
        int value = dp[k][j - 1] + (2 * i - num - pos_l) * homes[i] +
                    (num - pos_l) * homes[k] + 2 * pref[pos_l] - 2 * pref[i];
        if (value < dp[i][j]) {
          dp[i][j] = value;
          parent[i][j] = k;
        }
      }
    }
  }
  int ma = INT_MAX;
  int ii = 0;
  int jj = 0;
  for (int j = 1; j <= mum; ++j) {
    for (int i = 1; i <= num; ++i) {
      if (dp[i][j] < ma) {
        ma = dp[i][j];
        ii = i;
        jj = j;
      }
    }
  }

  std::cout << ma << '\n';
  std::vector<int> path;
  while (ii != -1) {
    path.push_back(homes[ii]);
    ii = parent[ii][jj--];
  }
  reverse(path.begin(), path.end());
  for (auto& elem : path) {
    std::cout << elem << ' ';
  }
}