#include <bits/stdc++.h>
std::vector<long long> MinInWindow(std::vector<long long>& sum_player2,
                                   long long len, long long number) {
  std::vector<long long> ans;
  std::deque<long long> window;
  for (long long ind = 0; ind < number; ++ind) {
    if (ind >= len && window.front() == ind - len) {
      window.pop_front();
    }
    while (!window.empty() && sum_player2[window.back()] >= sum_player2[ind]) {
      window.pop_back();
    }
    window.push_back(ind);
    if (ind >= len - 1) {
      ans.push_back(sum_player2[window.front()]);
    }
  }
  return ans;
}
void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}
int main() {
  Speed();
  long long number;
  std::cin >> number;
  std::vector<long long> cycle(number);
  for (auto& ind : cycle) {
    std::cin >> ind;
  }
  for (int ind = 0; ind < number; ++ind) {
    cycle.push_back(cycle[ind]);
  }
  std::vector<long long> pref_cycle(2 * number + 1);
  for (int ind = 1; ind <= 2 * number; ++ind) {
    pref_cycle[ind] = pref_cycle[ind - 1] + cycle[ind - 1];
  }
  long long cnt_player2 = number / 2;
  std::vector<long long> sum_player2;
  for (int ind = 1; ind + cnt_player2 - 1 <= 2 * number; ++ind) {
    if ((long long)sum_player2.size() == number) {
      break;
    }
    sum_player2.push_back(pref_cycle[ind + cnt_player2 - 1] -
                          pref_cycle[ind - 1]);
  }
  for (int ind = 0; ind < number; ++ind) {
    sum_player2[ind] *= -1;
    sum_player2.push_back(sum_player2[ind]);
  }
  auto min = MinInWindow(sum_player2, cnt_player2, 2 * number);
  auto ans =
      MinInWindow(min, number - 2 * cnt_player2 + 1, (long long)min.size());
  long long min_elem = LONG_LONG_MAX;
  for (auto& elem : ans) {
    min_elem = std::min(min_elem, -elem);
  }
  std::cout << pref_cycle[number] - min_elem << ' ' << min_elem;
}