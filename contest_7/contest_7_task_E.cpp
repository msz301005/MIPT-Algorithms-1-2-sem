#include <bits/stdc++.h>

struct Graph {
  std::vector<std::vector<int>> graph;
  std::vector<char> used;
  std::vector<int> tin;
  std::vector<int> ret;
  std::vector<int> ans;
  std::unordered_map<std::string, int> numbers;
  std::unordered_map<std::string, int> cnt;
  int timer = 0;
  Graph() = default;

  Graph(int number) {
    graph.resize(number);
    used.resize(number);
    tin.resize(number);
    ret.resize(number);
  }
  std::vector<int>& operator[](int pos) { return graph[pos]; }

  void Input(int cnt_edges) {
    for (int i = 0; i < cnt_edges; ++i) {
      int first;
      int second;
      std::cin >> first >> second;
      if (first == second) {
        continue;
      }
      graph[--first].push_back(--second);
      graph[second].push_back(first);
      numbers[std::to_string(first) + " " + std::to_string(second)] = i + 1;
      numbers[std::to_string(second) + " " + std::to_string(first)] = i + 1;
      cnt[std::to_string(first) + " " + std::to_string(second)]++;
      cnt[std::to_string(second) + " " + std::to_string(first)]++;
    }
  }

  void Dfs(int ver, int parent = -1) {
    used[ver] = 1;
    tin[ver] = ret[ver] = ++timer;
    for (auto too : graph[ver]) {
      if (too == parent) {
        continue;
      }
      if (used[too] == 1) {
        ret[ver] = std::min(ret[ver], tin[too]);
      } else {
        Dfs(too, ver);
        ret[ver] = std::min(ret[ver], ret[too]);
        if (ret[too] > tin[ver] &&
            cnt[std::to_string(ver) + " " + std::to_string(too)] == 1) {
          ans.push_back(
              numbers[std::to_string(ver) + " " + std::to_string(too)]);
        }
      }
    }
  }

  void Output(int number) {
    for (int i = 0; i < number; ++i) {
      if (used[i] == 0) {
        Dfs(i);
      }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (auto& elem : ans) {
      std::cout << elem << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number;
  int cnt_edges;
  std::cin >> number >> cnt_edges;
  Graph graph(number);
  graph.Input(cnt_edges);
  graph.Output(number);
}