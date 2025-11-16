#include <bits/stdc++.h>
const int kInf = INT_MAX;
template <typename Type>
void NonincreasingSubsequence(const Type& arr, Type& dp, Type& parent,
                              Type& pos) {
  int num = arr.size();
  dp[0] = -kInf;
  for (int ind = 0; ind < num; ++ind) {
    int len = std::upper_bound(dp.begin(), dp.end(), arr[ind]) - dp.begin();
    if (dp[len - 1] <= arr[ind] && arr[ind] <= dp[len]) {
      dp[len] = arr[ind];
      pos[len] = ind;
      parent[ind] = pos[len - 1];
    }
  }
}

template <typename Type>
void GetAnswer(const Type& arr, const Type& dp, const Type& parent,
               const Type& pos) {
  int num = arr.size();
  int ans = 0;
  for (int ind = num; ind > 0; --ind) {
    if (dp[ind] < kInf) {
      ans = ind;
      break;
    }
  }
  int ind = pos[ans];
  std::cout << ans << '\n';
  std::vector<int> index;
  while (ind != kInf) {
    index.push_back(num - ind);
    ind = parent[ind];
  }
  for (auto& elem : index) {
    std::cout << elem << ' ';
  }
}
int main() {
  int num;
  std::cin >> num;
  std::vector<int> arr(num);
  for (auto& elem : arr) {
    std::cin >> elem;
  }
  reverse(arr.begin(), arr.end());
  std::vector<int> dp(num + 1, kInf);
  std::vector<int> pos(num + 1, kInf);
  std::vector<int> parent(num + 1, kInf);
  NonincreasingSubsequence(arr, dp, parent, pos);
  GetAnswer(arr, dp, parent, pos);
}