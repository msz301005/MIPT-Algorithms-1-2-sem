#include <bits/stdc++.h>
const long long kMod = 1e9 + 9;
struct Kar {
  long long xx;
  long long yy;
  long long kk;
};

struct Matrix {
  long long a11;
  long long a12;
  long long a21;
  long long a22;
  Matrix() = default;
  Matrix(long long a11, long long a12, long long a21, long long a22) {
    this->a11 = a11 % kMod;
    this->a12 = a12 % kMod;
    this->a21 = a21 % kMod;
    this->a22 = a22 % kMod;
  }
  Matrix operator*=(const Matrix& other) {
    Matrix clone;
    clone.a11 = (a11 * other.a11 + a12 * other.a21) % kMod;
    clone.a12 = (a11 * other.a12 + a12 * other.a22) % kMod;
    clone.a21 = (a21 * other.a11 + a22 * other.a21) % kMod;
    clone.a22 = (a21 * other.a12 + a22 * other.a22) % kMod;
    *this = clone;
    return *this;
  }

  Matrix operator%=(const long long& mod) {
    a11 %= mod;
    a12 %= mod;
    a21 %= mod;
    a22 %= mod;
    return *this;
  }
};

template <typename Type>
Type BinPow(Type num, long long cnt) {
  Type res(1, 0, 0, 1);
  num %= kMod;
  while (cnt != 0) {
    if (cnt % 2 != 0) {
      res *= num;
    }
    num *= num;
    cnt /= 2;
  }
  res %= kMod;
  return res;
}
long long Fib(long long num) {
  Matrix matrix(1, 1, 1, 0);
  return BinPow(matrix, num - 1).a11;
}
int main() {
  long long num;
  long long cnt_lines;
  std::cin >> num >> cnt_lines;
  std::vector<Kar> airports(num);
  for (auto& elem : airports) {
    std::cin >> elem.xx >> elem.yy >> elem.kk;
    elem.kk %= kMod;
  }
  std::vector<long long> lines(cnt_lines);
  for (auto& elem : lines) {
    std::cin >> elem;
  }
  for (auto& line : lines) {
    long long ans = 0;
    for (auto& airport : airports) {
      long long dist = airport.yy - airport.xx - line;
      if (dist < 0) {
        continue;
      }
      ans = (ans + airport.kk * Fib(dist + 1)) % kMod;
    }
    std::cout << ans << '\n';
  }
}