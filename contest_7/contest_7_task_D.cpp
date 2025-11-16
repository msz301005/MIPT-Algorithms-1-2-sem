#include <bits/stdc++.h>

class Graph {
 public:
  Graph() = default;

  Graph(int number) {
    graph_.resize(number);
    used_.resize(number);
  }
  std::vector<int>& operator[](int pos) { return graph_[pos]; }

  void Dfs(int ver) {
    used_[ver] = 1;
    comp_.push_back(ver);
    for (auto too : graph_[ver]) {
      if (used_[too] == 0) {
        Dfs(too);
      }
    }
    top_sort_.push_back(ver);
    used_[ver] = 2;
  }

  std::vector<int>& GetUsed() { return used_; }

  std::vector<int>& GetTopSort() { return top_sort_; }

  std::vector<int>& GetComp() { return comp_; }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> used_;
  std::vector<int> top_sort_;
  std::vector<int> comp_;
};

int main() {
  int number;
  int cnt_edges;
  std::cin >> number >> cnt_edges;
  Graph graph(number);
  Graph reverse_graph(number);
  for (int i = 0; i < cnt_edges; ++i) {
    int first;
    int second;
    std::cin >> first >> second;
    graph[--first].push_back(--second);
    reverse_graph[second].push_back(first);
  }
  for (int i = 0; i < number; ++i) {
    if (graph.GetUsed()[i] == 0) {
      graph.Dfs(i);
    }
  }
  reverse(graph.GetTopSort().begin(), graph.GetTopSort().end());
  std::vector<std::vector<int>> components;
  for (int i = 0; i < number; ++i) {
    int ver = graph.GetTopSort()[i];
    if (reverse_graph.GetUsed()[ver] == 0) {
      reverse_graph.Dfs(ver);
      components.push_back(reverse_graph.GetComp());
      reverse_graph.GetComp().clear();
    }
  }
  std::cout << components.size() << std::endl;
  std::vector<int> ans(number);
  for (int i = 0; i < (int)components.size(); ++i) {
    for (int j = 0; j < (int)components[i].size(); ++j) {
      ans[components[i][j]] = i + 1;
    }
  }
  for (auto elem : ans) {
    std::cout << elem << ' ';
  }
}