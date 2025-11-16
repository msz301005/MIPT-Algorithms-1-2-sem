#include <bits/stdc++.h>

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

uint64_t Byte(uint64_t num, uint64_t kth_byte, const uint64_t& kByte) {
  uint64_t suff_bytes = std::min(kByte * kByte - 1, kByte * kth_byte);
  return ((num - ((num >> suff_bytes) << suff_bytes)) >> (kByte * (kth_byte - 1)));
}

void LSD(std::vector<uint64_t>& arr, const uint64_t& kLen, const uint64_t& kByte) {
  auto ans = arr;
  for (uint64_t kth_byte = 1; kth_byte <= kByte; ++kth_byte) {
    int cnt[kLen]{};
    for (const auto& elem : arr) {
      ++cnt[Byte(elem, kth_byte, kByte)];
    }
    for (uint64_t ind_cnt = 1; ind_cnt < kLen; ind_cnt++) {
      cnt[ind_cnt] += cnt[ind_cnt - 1];
    }
    for (int ind_arr = (int) arr.size() - 1; ind_arr >= 0; ind_arr--) {
      auto& elem = arr[ind_arr];
      ans[--cnt[Byte(elem, kth_byte, kByte)]] = elem;
    }
    std::swap(arr, ans);
  }
}

void Input(std::vector<uint64_t>& arr) {
  for (auto& elem : arr) {
    std::cin >> elem;
  }
}

void Print(const std::vector<uint64_t>& arr) {
  for (const auto& elem : arr) {
    std::cout << elem << '\n';
  }
}

int main() {
  Speed();

  const uint64_t kLen = 256;
  const uint64_t kByte = 8;

  int number;
  std::cin >> number;
  std::vector<uint64_t> arr(number);
  Input(arr);
  LSD(arr, kLen, kByte);
  Print(arr);
}
