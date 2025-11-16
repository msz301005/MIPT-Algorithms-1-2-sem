#include <bits/stdc++.h>
const int kNum = 4;
struct Kar {
  int time = INT_MIN;
  std::vector<std::string> boys;
  std::vector<std::string> girls;
};

Kar operator+(const Kar& first, const Kar& second) {
  Kar res;
  res.time = std::max(first.time, second.time);
  for (auto& elem : first.boys) {
    res.boys.push_back(elem);
  }
  for (auto& elem : second.boys) {
    res.boys.push_back(elem);
  }
  for (auto& elem : first.girls) {
    res.girls.push_back(elem);
  }
  for (auto& elem : second.girls) {
    res.girls.push_back(elem);
  }
  return res;
}
void Input(std::vector<std::pair<std::string, int>>& map) {
  for (int i = 1; i < (int)map.size(); ++i) {
    std::cin >> map[i].first >> map[i].second;
  }
}
template <typename Type>
bool Comp(Type first, Type second) {
  return first.second < second.second;
}

int main() {
  int nn;
  int mm;
  std::cin >> nn;
  std::vector<std::pair<std::string, int>> boys(nn + 1);
  Input(boys);
  std::cin >> mm;
  std::vector<std::pair<std::string, int>> girls(mm + 1);
  Input(girls);
  std::sort(boys.begin(), boys.end(), Comp<std::pair<std::string, int>>);
  std::sort(girls.begin(), girls.end(), Comp<std::pair<std::string, int>>);
  std::vector<std::vector<Kar>> dp(nn + 1, std::vector<Kar>(mm + 1));
  dp[1][0].time = boys.begin()->second;
  dp[1][0].boys.push_back(boys.begin()->first);
  for (int j = 1; j < kNum; ++j) {
    dp[1][j] = dp[1][j - 1];
    dp[1][j].girls.push_back(girls[j].first);
    dp[1][j].time = std::max(dp[1][j].time, girls[j].second);
  }
  for (int i = 2; i <= nn; ++i) {
    for (int j = 1; j <= mm; ++j) {
      if (i == 1 && j == 0) {
        continue;
      }
      Kar max_time;
      for (int boy = 1; boy < i && boy <= kNum; ++boy) {
        for (int girl = 0; girl < j && girl + boy <= kNum; ++girl) {
          Kar ma;
          for (int ii = i - boy + 1; ii <= i; ++ii) {
            ma.time = std::max(ma.time, boys[ii].second);
            ma.boys.push_back(boys[ii].first);
          }
          for (int jj = j - girl + 1; jj <= j; ++jj) {
            ma.time = std::max(ma.time, girls[jj].second);
            ma.girls.push_back(girls[jj].first);
          }
          if (ma.time < max_time.time || max_time.time == INT_MIN) {
            max_time = ma;
          }
        }
      }
      int boy = (int)max_time.boys.size();
      int girl = (int)max_time.girls.size();
      if (dp[i - boy][j - girl].time + max_time.time < dp[i][j].time) {
        dp[i][j] = dp[i - boy][j - girl] + max_time;
      }
    }
  }
  std::cout << dp[nn][mm].time;
}
