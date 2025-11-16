#include <bits/stdc++.h>
long long Bit(long long mask, long long pos) { return (mask >> pos) & 1; }
long long CheckProfiles(long long nn, long long profile1, long long profile2) {
  for (long long i = 0; i + 1 < nn; ++i) {
    if (Bit(profile1, i) == Bit(profile2, i) &&
        Bit(profile1, i) == Bit(profile1, i + 1) &&
        Bit(profile1, i) == Bit(profile2, i + 1)) {
      return 0;
    }
  }
  return 1;
}
int main() {
  long long nn;
  long long mm;
  std::cin >> nn >> mm;
  if (nn > mm) {
    std::swap(nn, mm);
  }
  std::vector<std::vector<long long>> can((1 << nn),
                                          std::vector<long long>((1 << nn)));
  for (long long i = 0; i < (1 << nn); ++i) {
    for (long long j = 0; j < (1 << nn); ++j) {
      can[i][j] = CheckProfiles(nn, i, j);
    }
  }
  std::vector<std::vector<long long>> dp(mm, std::vector<long long>((1 << nn)));
  for (long long i = 0; i < (1 << nn); ++i) {
    dp[0][i] = 1;
  }
  for (long long k = 1; k < mm; ++k) {
    for (long long i = 0; i < (1 << nn); ++i) {
      for (long long j = 0; j < (1 << nn); ++j) {
        dp[k][i] += dp[k - 1][j] * can[j][i];
      }
    }
  }
  long long ans = 0;
  for (auto& elem : dp[mm - 1]) {
    ans += elem;
  }
  std::cout << ans;
}