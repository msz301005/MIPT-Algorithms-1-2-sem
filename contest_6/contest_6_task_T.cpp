#include <bits/stdc++.h>
const long long kMod = 1e9 + 7;
struct Kar {
  long long aa;
  long long bb;
  long long cc;
};

class Matrix {
 public:
  long long num;
  long long mum;

  Matrix() = default;

  Matrix(long long nn, long long mm) {
    num = nn;
    mum = mm;
    matrix_.resize(num, std::vector<long long>(mum, 0));
  }

  std::vector<long long>& operator[](size_t pos) { return matrix_[pos]; }

  const std::vector<long long>& operator[](size_t pos) const {
    return matrix_[pos];
  }

  void PushBack(int val) {
    matrix_.push_back({val});
    ++num;
  }

  void PopBack() {
    matrix_.pop_back();
    --num;
  }

 private:
  std::vector<std::vector<long long>> matrix_;
};

Matrix operator*(const Matrix& first, const Matrix& second) {
  Matrix matrix(first.num, second.mum);
  for (long long i_m = 0; i_m < first.num; ++i_m) {
    for (long long i_n = 0; i_n < second.mum; ++i_n) {
      long long sum = 0;
      for (long long i_k = 0; i_k < first.mum; ++i_k) {
        sum = (sum + first[i_m][i_k] * second[i_k][i_n]) % kMod;
      }
      matrix[i_m][i_n] = sum;
    }
  }
  return matrix;
}

Matrix BinPow(Matrix num, long long cnt) {
  Matrix res(num.num, num.mum);
  for (int i = 0; i < num.num; ++i) {
    for (int j = 0; j < num.mum; ++j) {
      res[i][j] = (i == j ? 1 : 0);
    }
  }
  while (cnt != 0) {
    if (cnt % 2 != 0) {
      res = res * num;
    }
    num = num * num;
    cnt /= 2;
  }
  return res;
}

int main() {
  long long nn;
  long long kk;
  std::cin >> nn >> kk;
  std::vector<Kar> segments(nn);
  for (auto& elem : segments) {
    std::cin >> elem.aa >> elem.bb >> elem.cc;
  }
  segments[nn - 1].bb = kk;
  Matrix column(1, 1);
  column[0][0] = 1;
  for (auto segment : segments) {
    while (column.num <= segment.cc) {
      column.PushBack(0);
    }
    while (column.num > segment.cc + 1) {
      column.PopBack();
    }
    Matrix matrix(segment.cc + 1, segment.cc + 1);
    for (int i = 0; i <= segment.cc; ++i) {
      for (int j = 0; j <= segment.cc; ++j) {
        matrix[i][j] = (std::abs(i - j) <= 1 ? 1 : 0);
      }
    }
    column = BinPow(matrix, segment.bb - segment.aa) * column;
  }
  std::cout << column[0][0] % kMod;
}