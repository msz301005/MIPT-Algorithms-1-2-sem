#include <bits/stdc++.h>
const long long cKInf = 1e18;
void Dijkstra(
    const std::vector<std::vector<std::pair<long long, long long>>>& graph,
    std::vector<long long>& d, long long s) {
  int n = static_cast<int>(graph.size());
  std::priority_queue<std::pair<int, int>> q;
  std::vector<bool> used(n);
  d[s] = 0;
  q.emplace(0, s);
  while (!q.empty()) {
    int v = q.top().second;
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
  long long m;
  long long k;
  std::cin >> n >> m >> k;
  std::vector<long long> a(k);
  for (auto& elem : a) {
    std::cin >> elem;
  }
  std::vector<std::vector<std::pair<long long, long long>>> graph(n);
  while (m-- > 0) {
    long long first;
    long long second;
    long long weight;
    std::cin >> first >> second >> weight;
    graph[--first].emplace_back(--second, weight);
    graph[second].emplace_back(first, weight);
  }
  long long s;
  long long t;
  std::cin >> s >> t;
  std::vector<long long> d(n, cKInf);
  Dijkstra(graph, d, --t);
  --s;
  long long mi = cKInf;
  for (auto& virus : a) {
    mi = std::min(mi, d[virus - 1]);
  }
  std::cout << (d[s] < mi ? d[s] : -1);
}