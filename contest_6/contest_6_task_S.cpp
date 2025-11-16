#include <bits/stdc++.h>
long long mod;
long long Bit(long long mask, long long pos) { return (mask >> pos) & 1; }
int CheckProfiles(long long nn, long long profile1, long long profile2) {
  for (long long i = 0; i + 1 < nn; ++i) {
    if (Bit(profile1, i) == Bit(profile2, i) &&
        Bit(profile1, i) == Bit(profile1, i + 1) &&
        Bit(profile1, i) == Bit(profile2, i + 1)) {
      return 0;
    }
  }
  return 1;
}

class BigInteger {
 public:
  BigInteger() = default;

  BigInteger(const BigInteger&) = default;

  BigInteger& operator=(const BigInteger& other) = default;

  BigInteger(const std::string& other) {
    for (int i = other.size(); i > 0; i -= kLenBlock) {
      if (i < kLenBlock) {
        num_.push_back(std::stoi(other.substr(0, i)));
      } else {
        num_.push_back(std::stoi(other.substr(i - kLenBlock, kLenBlock)));
      }
    }
  }

  BigInteger(int other) {
    BigInteger res = std::to_string(other);
    *this = res;
  }

  BigInteger& operator+=(const BigInteger& other) {
    int carry = 0;
    for (int i = 0;
         i < std::max((int)num_.size(), (int)other.num_.size()) || carry != 0;
         ++i) {
      if (i == (int)num_.size()) {
        num_.push_back(0);
      }
      num_[i] += carry + (i < (int)other.num_.size() ? other.num_[i] : 0);
      carry = (num_[i] >= kBase ? 1 : 0);
      if (carry != 0) {
        num_[i] -= kBase;
      }
    }
    return *this;
  }

  BigInteger& operator-=(const BigInteger& other) {
    int carry = 0;
    for (size_t i = 0; i < other.num_.size() || carry != 0; ++i) {
      num_[i] -= carry + (i < other.num_.size() ? other.num_[i] : 0);
      carry = (num_[i] < 0 ? 1 : 0);
      if (carry != 0) {
        num_[i] += kBase;
      }
    }
    while (num_.size() > 1 && num_.back() == 0) {
      num_.pop_back();
    }
    return *this;
  }

  BigInteger& operator*=(const BigInteger& other) {
    std::vector<long long> res(num_.size() + other.num_.size());
    for (int i = 0; i < (int)num_.size(); ++i) {
      for (int j = 0, carry = 0; j < (int)other.num_.size() || carry != 0;
           ++j) {
        long long cur =
            res[i + j] +
            num_[i] * 1LL * (j < (int)other.num_.size() ? other.num_[j] : 0) +
            carry;
        res[i + j] = int(cur % kBase);
        carry = int(cur / kBase);
      }
    }
    while (res.size() > 1 && res.back() == 0) {
      res.pop_back();
    }
    this->num_ = res;
    return *this;
  }

  BigInteger& operator/=(long long other) {
    int carry = 0;
    for (int i = (int)num_.size() - 1; i >= 0; --i) {
      long long cur = num_[i] + carry * 1LL * kBase;
      num_[i] = int(cur / other);
      carry = int(cur % other);
    }
    while (num_.size() > 1 && num_.back() == 0) {
      num_.pop_back();
    }
    return *this;
  }

  const std::vector<long long>& GetNum() const { return num_; }

  std::vector<long long>& GetNum() { return num_; }

  static long long GetBase() { return kBase; }

 private:
  std::vector<long long> num_;
  static const long long kBase = 1e9;
  static const int kLenBlock = 9;
};

bool operator==(const BigInteger& first, const BigInteger& second) {
  return first.GetNum() == second.GetNum();
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
  return !(first == second);
}

BigInteger operator+(const BigInteger& num1, const BigInteger& num2) {
  BigInteger result = num1;
  result += num2;
  return result;
}

BigInteger operator-(const BigInteger& num1, const BigInteger& num2) {
  BigInteger result = num1;
  result -= num2;
  return result;
}

BigInteger operator*(const BigInteger& num1, const BigInteger& num2) {
  BigInteger result = num1;
  result *= num2;
  return result;
}

std::istream& operator>>(std::istream& iss, BigInteger& num) {
  std::string str;
  iss >> str;
  BigInteger num1 = str;
  num = num1;
  return iss;
}

long long operator%(BigInteger num, long long other) {
  int carry = 0;
  for (int i = (int)num.GetNum().size() - 1; i >= 0; --i) {
    long long cur = num.GetNum()[i] + carry * 1LL * BigInteger::GetBase();
    num.GetNum()[i] = int(cur / other);
    carry = int(cur % other);
  }
  return carry;
}

class Matrix {
 public:
  long long num;
  long long mum;
  Matrix(long long nn, long long mm) {
    num = nn;
    mum = mm;
    matrix_.resize(num, std::vector<long long>(mum, 0));
  }

  std::vector<long long>& operator[](size_t pos) { return matrix_[pos]; }

  const std::vector<long long>& operator[](size_t pos) const {
    return matrix_[pos];
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
        sum = (sum + first[i_m][i_k] * second[i_k][i_n]) % mod;
      }
      matrix[i_m][i_n] = sum;
    }
  }
  return matrix;
}

Matrix BinPow(Matrix num, BigInteger cnt) {
  Matrix res(num.num, num.mum);
  for (int i = 0; i < num.num; ++i) {
    for (int j = 0; j < num.mum; ++j) {
      res[i][j] = (i == j ? 1 : 0);
    }
  }
  while (cnt != 0) {
    if (cnt.GetNum()[0] % 2 != 0) {
      res = res * num;
    }
    num = num * num;
    cnt /= 2;
  }
  return res;
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  long long nn;
  BigInteger mm;
  std::cin >> mm >> nn >> mod;
  Matrix can((1 << nn), (1 << nn));
  for (long long i = 0; i < (1 << nn); ++i) {
    for (long long j = 0; j < (1 << nn); ++j) {
      can[i][j] = CheckProfiles(nn, i, j);
    }
  }
  Matrix column((1 << nn), 1);
  for (int i = 0; i < (1 << nn); ++i) {
    column[i][0] = 1;
  }
  Matrix ans = BinPow(can, mm - 1) * column;
  long long res = 0;
  for (int i = 0; i < ans.num; ++i) {
    for (int j = 0; j < ans.mum; ++j) {
      res = (res + ans[i][j]) % mod;
    }
  }
  std::cout << res % mod;
}