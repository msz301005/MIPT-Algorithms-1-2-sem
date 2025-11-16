#include <bits/stdc++.h>
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> ans;
std::vector<bool> used;
std::vector<int> comp;
void Dfs(int ver) {
  used[ver] = true;
  comp.push_back(ver + 1);
  for (auto uuu : graph[ver]) {
    if (!used[uuu]) {
      Dfs(uuu);
    }
  }
}
int main() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  graph.resize(nnn);
  used.resize(nnn);
  for (int i = 0; i < mmm; i++) {
    int first;
    int second;
    std::cin >> first >> second;
    graph[--first].push_back(--second);
    graph[second].push_back(first);
  }
  for (int i = 0; i < nnn; i++) {
    if (!used[i]) {
      comp.clear();
      Dfs(i);
      ans.push_back(comp);
    }
  }
  std::cout << ans.size() << '\n';
  for (auto& elem : ans) {
    std::cout << elem.size() << '\n';
    for (auto elem1 : elem) {
      std::cout << elem1 << ' ';
    }
    std::cout << '\n';
  }
}