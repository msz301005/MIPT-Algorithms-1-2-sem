#include <bits/stdc++.h>

const long long cInf = INT64_MAX;

struct Edge {
  long long w = cInf;
  long long cap = 0;
};

class Graph {
 public:
  Graph(long long n) : n_(n) {
    used_.resize(n);
    g_.resize(n, std::vector<Edge>(n));
    adj_.resize(n);
    d_.resize(n, cInf);
    potential_.resize(n);
    parent_.resize(n);
  }

  std::vector<Edge>& operator[](size_t ind) { return g_[ind]; }

  const std::vector<Edge>& operator[](size_t ind) const { return g_[ind]; }

  void ShortestPath(long long s) {
    d_.assign(n_, cInf);
    d_[s] = 0;
    used_.assign(n_, 0);
    std::queue<long long> q;
    q.push(s);
    parent_.assign(n_, -1);
    while (!q.empty()) {
      long long u = q.front();
      q.pop();
      used_[u] = 0;
      for (auto v : adj_[u]) {
        if (g_[u][v].cap > 0 && d_[v] > d_[u] + g_[u][v].w) {
          d_[v] = d_[u] + g_[u][v].w;
          parent_[v] = u;
          if (used_[v] == 0) {
            used_[v] = 1;
            q.push(v);
          }
        }
      }
    }
  }

  void MinCostMaxFlow(long long s, long long t) {
    long long flow = 0;
    long long cost = 0;
    while (flow < cInf) {
      ShortestPath(s);
      if (d_[t] == cInf) {
        break;
      }
      long long f = cInf - flow;
      for (long long cur = t; cur != s; cur = parent_[cur]) {
        f = std::min(f, g_[parent_[cur]][cur].cap);
      }
      flow += f;
      cost += f * d_[t];
      for (long long cur = t; cur != s; cur = parent_[cur]) {
        g_[parent_[cur]][cur].cap -= f;
        g_[cur][parent_[cur]].cap += f;
      }
    }
    std::cout << cost;
  }

  std::vector<std::vector<long long>>& GetAdj() { return adj_; }

 private:
  long long n_;
  std::vector<char> used_;
  std::vector<long long> d_;
  std::vector<long long> potential_;
  std::vector<long long> parent_;
  std::vector<std::vector<Edge>> g_;
  std::vector<std::vector<long long>> adj_;
};

int main() {
  long long n;
  long long m;
  std::cin >> n >> m;
  Graph graph(n);
  while (m-- > 0) {
    long long u;
    long long v;
    long long cap;
    long long w;
    std::cin >> u >> v >> cap >> w;
    --u;
    --v;
    graph[u][v] = {w, cap};
    graph[v][u] = {-w, 0};
    graph.GetAdj()[u].push_back(v);
  }
  graph.MinCostMaxFlow(0, n - 1);
}