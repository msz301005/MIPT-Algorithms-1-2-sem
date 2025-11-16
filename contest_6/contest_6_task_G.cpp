#include <bits/stdc++.h>
int num;
template <typename Type>
void SolveDp1(const Type& arr, Type& dp, Type& parent) {
  for (int i = 1; i < num; ++i) {
    int ma = 0;
    int pos = -1;
    for (int j = 0; j < i; ++j) {
      if ((dp[j] % 2 == 0 && arr[j] > arr[i]) ||
          (dp[j] % 2 != 0 && arr[j] < arr[i])) {
        if (dp[j] > ma) {
          ma = dp[j];
          pos = j;
        }
      }
    }
    if (pos != -1) {
      dp[i] = dp[pos] + 1;
      parent[i] = pos;
    }
  }
}
template <typename Type>
void SolveDp2(const Type& arr, Type& dp, Type& parent) {
  for (int i = 1; i < num; ++i) {
    int ma = 0;
    int pos = -1;
    for (int j = 0; j < i; ++j) {
      if ((dp[j] != -1 && dp[j] % 2 == 0 && arr[j] < arr[i]) ||
          (dp[j] != -1 && dp[j] % 2 != 0 && arr[j] > arr[i])) {
        if (dp[j] > ma) {
          ma = dp[j];
          pos = j;
        }
      }
    }
    if (pos != -1) {
      dp[i] = dp[pos] + 1;
      parent[i] = pos;
    }
  }
}
int main() {
  std::cin >> num;
  std::vector<int> arr(num);
  for (auto& elem : arr) {
    std::cin >> elem;
  }
  std::vector<int> dp1(num, -1);
  std::vector<int> parent1(num, -1);
  std::vector<int> dp2(num, -1);
  std::vector<int> parent2(num, -1);
  dp1[0] = dp2[0] = 1;
  SolveDp1(arr, dp1, parent1);
  SolveDp2(arr, dp2, parent2);
  int ma1 = *std::max_element(dp1.begin(), dp1.end());
  int pos1 = std::max_element(dp1.begin(), dp1.end()) - dp1.begin();
  int ma2 = *std::max_element(dp2.begin(), dp2.end());
  int pos2 = std::max_element(dp2.begin(), dp2.end()) - dp2.begin();
  if (ma1 > ma2) {
    std::cout << ma1 << '\n';
    std::vector<int> path;
    while (pos1 != -1) {
      path.push_back(arr[pos1]);
      pos1 = parent1[pos1];
    }
    for (int i = (int)path.size() - 1; i >= 0; --i) {
      std::cout << path[i] << ' ';
    }
  } else {
    std::cout << ma2 << '\n';
    std::vector<int> path;
    while (pos2 != -1) {
      path.push_back(arr[pos2]);
      pos2 = parent2[pos2];
    }
    for (int i = (int)path.size() - 1; i >= 0; --i) {
      std::cout << path[i] << ' ';
    }
  }
}