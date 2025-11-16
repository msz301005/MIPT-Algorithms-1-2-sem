#include <bits/stdc++.h>
const long long cKInf = 30000;
int main() {
  long long n;
  long long m;
  std::cin >> n >> m;
  std::vector<std::vector<long long>> d(n,
                                        std::vector<long long>(n, INT64_MAX));
  while (m-- > 0) {
    long long first;
    long long second;
    long long weight;
    std::cin >> first >> second >> weight;
    --first;
    --second;
    d[first][second] = std::min(d[first][second], weight);
  }
  for (long long i = 0; i < n; ++i) {
    d[i][i] = 0;
  }
  for (long long k = 0; k < n; ++k) {
    for (long long i = 0; i < n; ++i) {
      for (long long j = 0; j < n; ++j) {
        if (d[i][k] < INT64_MAX && d[k][j] < INT64_MAX) {
          d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }
  for (auto& elem : d[0]) {
    std::cout << (elem == INT64_MAX ? cKInf : elem) << ' ';
  }
}