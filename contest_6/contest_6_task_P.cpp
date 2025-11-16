#include <bits/stdc++.h>

const long long kMod = 1e9 + 7;

template <class... Args>
std::pair<int, int> PlusesAndMinuses(Args... args) {
  int pluses = 0;
  int minuses = 0;
  for (auto& elem : {args...}) {
    if (elem == '+' || elem == 1) {
      pluses++;
    } else if (elem == '-' || elem == 0) {
      minuses++;
    }
  }
  return {pluses, minuses};
}

int Bit(long long mask, long long pos) { return (mask >> pos) & 1; }

long long ReturnPrevMask(long long nn, long long mask, int begin_bit) {
  std::vector<int> bits_prev_mask(nn);
  bits_prev_mask[0] = begin_bit;
  for (long long i = 1; i < nn; ++i) {
    auto [pluses, minuses] =
        PlusesAndMinuses(bits_prev_mask[i - 1], Bit(mask, i - 1), Bit(mask, i));
    if (pluses > 2 || minuses > 2) {
      return -1;
    }
    bits_prev_mask[i] = (pluses == 2 ? 0 : 1);
  }
  long long prev_mask = 0;
  for (long long i = 0; i < nn; ++i) {
    if (bits_prev_mask[i] == 1) {
      prev_mask += (1 << i);
    }
  }
  return prev_mask;
}

bool Check(long long nn, long long mask, long long column,
           std::vector<std::string>& city) {
  for (long long j = 0; j < nn; ++j) {
    if (city[j][column] == '.') {
      continue;
    }
    if (city[j][column] == '-' && Bit(mask, j) != 0) {
      return false;
    }
    if (city[j][column] == '+' && Bit(mask, j) != 1) {
      return false;
    }
  }
  return true;
}

int main() {
  long long nn;
  long long mm;
  std::cin >> nn >> mm;
  std::vector<std::string> city(nn);
  for (auto& elem : city) {
    std::cin >> elem;
  }
  std::vector<std::vector<long long>> dp(mm, std::vector<long long>((1 << nn)));
  for (long long i = 0; i < (1 << nn); ++i) {
    dp[0][i] = 1;
  }
  for (long long i = 1; i < mm; ++i) {
    for (long long mask = 0; mask < (1 << nn); ++mask) {
      long long prev_mask_0 = ReturnPrevMask(nn, mask, 0);
      long long prev_mask_1 = ReturnPrevMask(nn, mask, 1);
      if (prev_mask_0 != -1 && Check(nn, prev_mask_0, i - 1, city)) {
        dp[i][mask] += dp[i - 1][prev_mask_0];
      }
      if (prev_mask_1 != -1 && Check(nn, prev_mask_1, i - 1, city)) {
        dp[i][mask] += dp[i - 1][prev_mask_1];
      }
    }
  }
  long long ans = 0;
  for (long long mask = 0; mask < (1 << nn); ++mask) {
    if (Check(nn, mask, mm - 1, city)) {
      ans = (ans + dp[mm - 1][mask]) % kMod;
    }
  }
  std::cout << ans;
}