#include <bits/stdc++.h>

std::mt19937 gen(time(nullptr));

const int kC1 = 123;
const int kC2 = 45;
const int kMod = 10004321;

std::pair<int, int> Partition(std::vector<long long>& arr, int left, int right, long long pivot) {
  int sep = left - 1;
  for (int ind = left; ind < right; ind++) {
    if (arr[ind] < pivot) {
      std::swap(arr[sep + 1], arr[ind]);
      ++sep;
    }
  }
  int count_pivots = 0;
  for (int ind = left; ind < right; ind++) {
    if (arr[ind] == pivot) {
      std::swap(arr[sep + 1], arr[ind]);
      ++sep;
      ++count_pivots;
    }
  }
  return {sep - count_pivots, sep};
}

int RandomPosition(int left, int right) {
  std::uniform_int_distribution<int> distribution(left, right - 1);
  return distribution(gen);
}

long long QuickSelect(std::vector<long long>& arr, int left, int right, int kth) {
  long long pivot = arr[RandomPosition(left, right)];
  auto [sep_left, sep_right] = Partition(arr, left, right, pivot);
  ++sep_left;
  ++sep_right;
  int len_less_pivot = sep_left - left;
  int len_equal_pivot = sep_right - sep_left;
  if (kth < len_less_pivot) {
    return QuickSelect(arr, left, sep_left, kth);
  }
  if (len_less_pivot <= kth && kth < len_less_pivot + len_equal_pivot) {
    return pivot;
  }
  return QuickSelect(arr, sep_right, right, kth - len_less_pivot - len_equal_pivot);
}

void FillArr(std::vector<long long>& arr, int& number, int& first_elem, int& second_elem) {
  arr[0] = first_elem;
  arr[1] = second_elem;
  for (int ind = 2; ind < number; ind++) {
    arr[ind] = (arr[ind - 1] * kC1 + arr[ind - 2] * kC2) % kMod;
  }
}

int main() {
  int number;
  int kth;
  int first_elem;
  int second_elem;
  std::vector<long long> arr;
  std::cin >> number >> kth >> first_elem >> second_elem;
  arr.resize(number);
  if (number == 1) {
    std::cout << first_elem;
    return 0;
  }
  FillArr(arr, number, first_elem, second_elem);
  std::cout << QuickSelect(arr, 0, number, kth - 1);
}
