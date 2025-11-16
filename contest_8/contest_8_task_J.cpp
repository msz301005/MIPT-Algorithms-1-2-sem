#include <bits/stdc++.h>
const long long cKMaxV = 1000010;
const long long cInf = 1e18;
void Dijkstra(
    const std::vector<std::vector<std::pair<long long, long long>>>& graph,
    std::vector<long long>& d, long long s) {
  auto n = static_cast<long long>(graph.size());
  std::priority_queue<std::pair<long long, long long>> q;
  std::vector<bool> used(n);
  d[s] = 0;
  q.emplace(0, s);
  while (!q.empty()) {
    long long v = q.top().second;
    q.pop();
    if (used[v]) {
      continue;
    }
    used[v] = true;
    for (auto [to, w] : graph[v]) {
      if (d[v] + w < d[to]) {
        d[to] = d[v] + w;
        q.emplace(-d[to], to);
      }
    }
  }
}
int main() {
  long long n;
  long long u;
  long long d;
  long long i;
  long long j;
  long long l;
  std::cin >> n >> u >> d >> i >> j >> l;
  std::vector<std::vector<std::pair<long long, long long>>> g(cKMaxV + 1);
  g[1].emplace_back(n, (n - 1) * u);
  g[n].emplace_back(1, (n - 1) * d);
  std::vector<long long> tp;
  while (l-- > 0) {
    long long count;
    std::cin >> count;
    std::vector<long long> k(count);
    for (auto& elem : k) {
      std::cin >> elem;
      tp.push_back(elem);
    }
    for (long long ii = 0; ii < count; ++ii) {
      for (long long jj = ii + 1; jj < count; ++jj) {
        g[k[ii]].emplace_back(k[jj], i + j);
        g[k[jj]].emplace_back(k[ii], i + j);
      }
    }
  }
  std::sort(tp.begin(), tp.end());
  for (size_t ii = 0; ii + 1 < tp.size(); ++ii) {
    if (tp[ii] != 1) {
      g[1].emplace_back(tp[ii], (tp[ii] - 1) * u);
      g[tp[ii]].emplace_back(1, (tp[ii] - 1) * d);
    }
    if (tp[ii] != n) {
      g[std::min(n, tp[ii])].emplace_back(std::max(n, tp[ii]),
                                          std::abs(n - tp[ii]) * u);
      g[std::max(n, tp[ii])].emplace_back(std::min(n, tp[ii]),
                                          std::abs(n - tp[ii]) * d);
    }
    if (tp[ii] != tp[ii + 1]) {
      g[tp[ii]].emplace_back(tp[ii + 1], (tp[ii + 1] - tp[ii]) * u);
      g[tp[ii + 1]].emplace_back(tp[ii], (tp[ii + 1] - tp[ii]) * d);
    }
  }
  if (tp.back() != 1) {
    g[1].emplace_back(tp.back(), (tp.back() - 1) * u);
    g[tp.back()].emplace_back(1, (tp.back() - 1) * d);
  }
  if (tp.back() != n) {
    g[std::min(n, tp.back())].emplace_back(std::max(n, tp.back()),
                                           std::abs(n - tp.back()) * u);
    g[std::max(n, tp.back())].emplace_back(std::min(n, tp.back()),
                                           std::abs(n - tp.back()) * d);
  }
  std::vector<long long> dist(cKMaxV + 1, cInf);
  Dijkstra(g, dist, 1);
  std::cout << dist[n];
}