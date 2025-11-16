#include <bits/stdc++.h>
std::vector<int> used;
std::vector<int> parent;
std::vector<std::vector<int>> graph;
void Dfs(int ver, int prr = -1) {
  used[ver] = 1;
  parent[ver] = prr;
  for (auto too : graph[ver]) {
    if (used[too] == 0) {
      Dfs(too, ver);
    } else if (used[too] == 1) {
      std::cout << "YES\n";
      parent[too] = ver;
      std::vector<int> path;
      path.push_back(too);
      for (int i = ver; i != too; i = parent[i]) {
        path.push_back(i);
      }
      reverse(path.begin(), path.end());
      for (auto& elem : path) {
        std::cout << elem + 1 << ' ';
      }
      exit(0);
    }
  }
  used[ver] = 2;
}
int main() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  used.resize(nnn);
  parent.resize(nnn);
  graph.resize(nnn);
  while (mmm-- > 0) {
    int first;
    int second;
    std::cin >> first >> second;
    graph[--first].push_back(--second);
  }
  for (int i = 0; i < nnn; i++) {
    if (used[i] == 0) {
      Dfs(i);
    }
  }
  std::cout << "NO";
}