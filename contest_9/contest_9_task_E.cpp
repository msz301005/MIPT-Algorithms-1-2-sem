#include <bits/stdc++.h>

struct Graph {
  std::vector<std::vector<int>> graph;
  std::vector<char> used;
  std::vector<int> tin;
  std::vector<int> ret;
  std::vector<int> colors;
  std::set<std::pair<int, int>> bridges;
  int timer = 0;
  int max_color = 0;
  Graph() = default;

  Graph(int number) {
    graph.resize(number);
    used.resize(number);
    tin.resize(number);
    ret.resize(number);
    colors.resize(number);
  }
  std::vector<int>& operator[](int pos) { return graph[pos]; }

  void Input(int cnt_edges) {
    for (int i = 0; i < cnt_edges; ++i) {
      int first;
      int second;
      std::cin >> first >> second;
      graph[--first].push_back(--second);
      graph[second].push_back(first);
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
        if (ret[too] > tin[ver]) {
          bridges.emplace(ver, too);
        }
      }
    }
  }

  void Paint(int v, int color) {
    colors[v] = color;
    for (auto u : graph[v]) {
      if (colors[u] == 0) {
        if (bridges.find({v, u}) != bridges.end()) {
          Paint(u, ++max_color);
        } else {
          Paint(u, color);
        }
      }
    }
  }

  void FindComponents(int n) {
    for (int i = 0; i < n; ++i) {
      if (used[i] == 0) {
        Dfs(i);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (colors[i] == 0) {
        Paint(i, ++max_color);
      }
    }
  }
};

std::vector<std::vector<int>> g;
std::vector<std::vector<int>> up;
std::vector<int> tin;
std::vector<int> tout;
std::vector<int> size;
int timer;
int l = 1;

void Dfs(int v, int p, int depth = 0) {
  tin[v] = ++timer;
  size[v] = depth;
  up[v][0] = p;
  for (int i = 1; i <= l; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (auto u : g[v]) {
    if (u != p) {
      Dfs(u, v, depth + 1);
    }
  }
  tout[v] = timer;
}

bool Upper(int a, int b) { return tin[a] <= tin[b] && tout[a] >= tout[b]; }

int Lca(int v, int u) {
  if (Upper(v, u)) {
    return v;
  }
  if (Upper(u, v)) {
    return u;
  }
  for (int i = l; i >= 0; --i) {
    if (!Upper(up[v][i], u)) {
      v = up[v][i];
    }
  }
  return up[v][0];
}

int main() {
  int n;
  int m;
  int f;
  std::cin >> n >> m >> f;
  Graph graph(n);
  graph.Input(m);
  graph.FindComponents(n);
  int sz = graph.max_color;
  g.resize(sz);
  tin.resize(sz);
  tout.resize(sz);
  up.resize(sz);
  size.resize(sz);
  for (auto& elem : graph.colors) {
    --elem;
  }
  for (const auto& edge : graph.bridges) {
    g[graph.colors[edge.first]].push_back(graph.colors[edge.second]);
    g[graph.colors[edge.second]].push_back(graph.colors[edge.first]);
  }
  while ((1 << l) <= sz) {
    ++l;
  }
  for (int i = 0; i < sz; ++i) {
    up[i].resize(l + 1);
  }
  Dfs(graph.colors[f - 1], graph.colors[f - 1]);
  int q;
  std::cin >> q;
  while (q-- > 0) {
    int a;
    int b;
    std::cin >> a >> b;
    std::cout << size[Lca(graph.colors[--a], graph.colors[--b])] << '\n';
  }
}