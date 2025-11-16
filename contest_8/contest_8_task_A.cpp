#include <bits/stdc++.h>
const int cKInf = 2009000999;
void Dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph,
              std::vector<int>& d, int s) {
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
void Solve() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  while (m-- > 0) {
    int first;
    int second;
    int weight;
    std::cin >> first >> second >> weight;
    graph[first].emplace_back(second, weight);
    graph[second].emplace_back(first, weight);
  }
  int s;
  std::cin >> s;
  std::vector<int> d(n, cKInf);
  Dijkstra(graph, d, s);
  for (auto& elem : d) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
int main() {
  int k;
  std::cin >> k;
  while (k-- > 0) {
    Solve();
  }
}