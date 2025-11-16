#include <bits/stdc++.h>
struct Kar {
  long long ans = INT_MIN;
  std::pair<long long, long long> parent = {-1, -1};
};
template <typename Type>
void RecountDp(long long ii, long long jj, Type& dp,
               std::vector<long long>& arr) {
  long long left = ii + 1;
  long long right = jj - 1;
  bool ok = false;
  for (; left < jj; ++left) {
    if (arr[left] % arr[ii] == 0) {
      ok = true;
      break;
    }
  }
  for (; right > ii; --right) {
    if (arr[jj] % arr[right] == 0) {
      ok = true;
      break;
    }
  }
  if (ok) {
    dp[ii][jj].ans = dp[left][right].ans + 2;
    dp[ii][jj].parent = {left, right};
  } else if (jj != ii && arr[jj] % arr[ii] == 0) {
    dp[ii][jj].ans = 2;
  }
}

template <typename Type>
void RecoveryResponse(long long num, Type& dp) {
  long long ans = 0;
  long long left = 0;
  long long right = 0;
  for (long long i = 0; i < num / 2; ++i) {
    for (long long j = i; j < num; ++j) {
      if (j - i + 1 > num / 2) {
        continue;
      }
      if (dp[i][j].ans > ans) {
        ans = dp[i][j].ans;
        left = i;
        right = j;
      }
    }
  }
  std::cout << ans << '\n';
  std::vector<long long> path(ans, -1);
  long long pos_l = 0;
  long long pos_r = ans - 1;
  while (left != -1 && right != -1) {
    auto val = dp[left][right];
    path[pos_l] = left;
    path[pos_r] = right;
    // if (val.parent.first - left != 0) {
    pos_l++;
    // }
    // if (right - val.parent.second != 0) {
    pos_r--;
    // }
    left = val.parent.first;
    right = val.parent.second;
  }
  for (auto& elem : path) {
    if (++elem > num / 2) {
      elem -= num / 2;
    }
    std::cout << elem << ' ';
  }
}
int main() {
  long long num;
  std::cin >> num;
  std::vector<long long> arr(num);
  for (auto& elem : arr) {
    std::cin >> elem;
  }
  for (long long i = 0; i < num; ++i) {
    arr.push_back(arr[i]);
  }
  num *= 2;
  std::vector<std::vector<Kar>> dp(num, std::vector<Kar>(num));

  for (long long i = 0; i < num; ++i) {
    dp[i][i].ans = 1;
  }

  for (long long i = num - 2; i >= 0; --i) {
    for (long long j = i + 1; j < num; ++j) {
      RecountDp(i, j, dp, arr);
    }
  }
  RecoveryResponse(num, dp);
}