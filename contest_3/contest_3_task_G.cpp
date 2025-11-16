#include <bits/stdc++.h>
struct Fenwick {
  Fenwick(long long size1, long long size2)
      : size_col_(size1), size_str_(size2) {
    tree_.resize(size1, std::vector<long long>(size2, 0));
  }

  void Update(long long id_i, long long id_j, long long delta) {
    for (long long pos_i = id_i; pos_i < size_col_; pos_i |= (pos_i + 1)) {
      for (long long pos_j = id_j; pos_j < size_str_; pos_j |= (pos_j + 1)) {
        tree_[pos_i][pos_j] += delta;
      }
    }
  }

  long long Sum(long long id_i, long long id_j) {
    long long res = 0;
    for (long long pos_i = id_i; pos_i >= 0;
         pos_i = (pos_i & (pos_i + 1)) - 1) {
      for (long long pos_j = id_j; pos_j >= 0;
           pos_j = (pos_j & (pos_j + 1)) - 1) {
        res += tree_[pos_i][pos_j];
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<long long>> tree_;
  long long size_col_;
  long long size_str_;
};

struct Type {
  long long pt_x;
  long long pt_y;
  long long weight;
};

void Input(int number, std::vector<long long>& coords_x,
           std::vector<long long>& coords_y, std::vector<Type>& points) {
  for (int ind = 0; ind < number; ++ind) {
    long long point_x;
    long long point_y;
    long long weight;
    std::cin >> point_x >> point_y >> weight;
    points[ind] = {point_x, point_y, weight};
    coords_x.push_back(point_x);
    coords_y.push_back(point_y);
  }
  std::sort(coords_x.begin(), coords_x.end());
  coords_x.resize(std::unique(coords_x.begin(), coords_x.end()) -
                 coords_x.begin());
  std::sort(coords_y.begin(), coords_y.end());
  coords_y.resize(std::unique(coords_y.begin(), coords_y.end()) -
                 coords_y.begin());
}

void BuildFenwich(Fenwick& tree, std::vector<long long>& coords_x,
                  std::vector<long long>& coords_y, std::vector<Type>& points) {
  for (auto elem : points) {
    long long comp_x =
        std::lower_bound(coords_x.begin(), coords_x.end(), elem.pt_x) -
        coords_x.begin();
    long long comp_y =
        std::lower_bound(coords_y.begin(), coords_y.end(), elem.pt_y) -
        coords_y.begin();
    tree.Update(comp_x, comp_y, elem.weight);
  }
}

int main() {
  int number;
  std::cin >> number;
  std::vector<Type> points(number);
  std::vector<long long> coords_x;
  std::vector<long long> coords_y;
  Input(number, coords_x, coords_y, points);
  int size = std::max((int)coords_x.size(), (int)coords_y.size());
  Fenwick tree(size, size);
  BuildFenwich(tree, coords_x, coords_y, points);
  int queries;
  std::cin >> queries;
  while (queries-- > 0) {
    std::string operation;
    std::cin >> operation;
    if (operation == "get") {
      long long pt_x;
      long long pt_y;
      std::cin >> pt_x >> pt_y;
      long long comp_x =
          std::upper_bound(coords_x.begin(), coords_x.end(), pt_x) -
          coords_x.begin() - 1;
      long long comp_y =
          std::upper_bound(coords_y.begin(), coords_y.end(), pt_y) -
          coords_y.begin() - 1;
      std::cout << tree.Sum(comp_x, comp_y) << '\n';
    } else {
      long long pos;
      long long new_weight;
      std::cin >> pos >> new_weight;
      --pos;
      long long comp_x =
          std::lower_bound(coords_x.begin(), coords_x.end(), points[pos].pt_x) -
          coords_x.begin();
      long long comp_y =
          std::lower_bound(coords_y.begin(), coords_y.end(), points[pos].pt_y) -
          coords_y.begin();
      tree.Update(comp_x, comp_y, new_weight - points[pos].weight);
      points[pos].weight = new_weight;
    }
  }
}