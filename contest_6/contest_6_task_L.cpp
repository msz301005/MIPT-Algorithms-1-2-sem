#include <bits/stdc++.h>
struct Kar {
  Kar() {}
  Kar(int k0, int v0) {
    kk = k0;
    vv = v0;
  }
  int kk;
  int vv;
  int gg;
};
int main() {
  int nn;
  int gg;
  int kk;
  std::cin >> nn >> gg >> kk;
  std::vector<int> g0;
  std::vector<Kar> algo(nn);
  for (auto& elem : algo) {
    std::cin >> elem.kk >> elem.vv >> elem.gg;
    g0.push_back(elem.gg);
  }
  sort(g0.begin(), g0.end());
  g0.resize(std::unique(g0.begin(), g0.end()) - g0.begin());
  int cnt_g = (int)g0.size();
  for (auto& elem : algo) {
    elem.gg = std::lower_bound(g0.begin(), g0.end(), elem.gg) - g0.begin();
  }
  std::vector<std::vector<Kar>> group(cnt_g);
  for (auto& elem : algo) {
    group[elem.gg].emplace_back(elem.kk, elem.vv);
  }
  std::vector<std::vector<int>> dp(cnt_g + 1, std::vector<int>(kk + 1));
  for (int gr = 1; gr <= cnt_g; ++gr) {
    for (int k = 1; k <= kk; ++k) {
      int ma = dp[gr - 1][k];
      for (auto& elem : group[gr - 1]) {
        if (k >= elem.kk) {
          ma = std::max(ma, dp[gr - 1][k - elem.kk] + elem.vv);
        }
      }
      dp[gr][k] = ma;
    }
  }
  std::cout << *std::max_element(dp[cnt_g].begin(), dp[cnt_g].end());
}