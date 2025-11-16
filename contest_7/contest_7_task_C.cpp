#include <bits/stdc++.h>
int nnn;
std::vector<int> used;
std::vector<std::vector<int>> graph;
std::vector<int> top_sort;
void Dfs(int ver) {
  used[ver] = 1;
  for (auto uuu : graph[ver]) {
    if (used[uuu] == 0) {
      Dfs(uuu);
    } else if (used[uuu] == 1) {
      std::cout << -1;
      exit(0);
    }
  }
  top_sort.push_back(ver);
  used[ver] = 2;
}

void TopologicalSort() {
  for (int i = 0; i < nnn; ++i) {
    if (used[i] == 0) {
      Dfs(i);
    }
  }
  reverse(top_sort.begin(), top_sort.end());
  for (auto& elem : top_sort) {
    std::cout << elem + 1 << ' ';
  }
}
int main() {
  int mmm;
  std::cin >> nnn >> mmm;
  used.resize(nnn);
  graph.resize(nnn);
  while (mmm-- > 0) {
    int first;
    int second;
    std::cin >> first >> second;
    graph[--first].push_back(--second);
  }
  TopologicalSort();
}