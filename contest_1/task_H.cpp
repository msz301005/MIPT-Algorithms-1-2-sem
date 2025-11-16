#include <bits/stdc++.h>

std::mt19937 gen(time(nullptr));

std::pair<int, int> Partition(std::vector<int>& arr, int left, int right, int pivot) {
  int sep = left - 1;
  for (int ind = left; ind < right; ind++) {
    if (arr[ind] >= pivot) {
      continue;
    }
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
  std::uniform_int_distribution distribution(left, right - 1);
  return distribution(gen);
}

void QuickSort(std::vector<int>& arr, int left, int right) {
  if (right - left <= 1) {
    return;
  }
  int pivot = arr[RandomPosition(left, right)];
  int sep_left = Partition(arr, left, right, pivot).first + 1;
  int sep_right = Partition(arr, left, right, pivot).second + 1;
  QuickSort(arr, left, sep_left);
  QuickSort(arr, sep_right, right);
}

void PrintArr(std::vector<int>& arr) {
  for (auto elem : arr) {
    std::cout << elem << ' ';
  }
}

int main() {
  int number;
  std::cin >> number;
  std::vector<int> arr(number);
  for (auto& elem : arr) {
    std::cin >> elem;
  }
  QuickSort(arr, 0, number);
  PrintArr(arr);
}