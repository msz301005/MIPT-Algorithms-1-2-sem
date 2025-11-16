#include <bits/stdc++.h>
const int kFix = 8;
const int kBase = 10;
void Input(std::vector<double>& arr) {
  for (auto& elem : arr) {
    std::cin >> elem;
    elem = log10(elem);
  }
}

void MakePref(const std::vector<double>& arr, std::vector<double>& pref,
              const int& number) {
  for (auto ind = 1; ind <= number; ind++) {
    pref[ind] = arr[ind - 1] + pref[ind - 1];
  }
}

void SolveQueries(const std::vector<double>& pref) {
  int queries;
  std::cin >> queries;
  while (queries-- > 0) {
    int left;
    int right;
    std::cin >> left >> right;
    ++right;
    std::cout << std::fixed << std::setprecision(kFix)
              << pow(kBase, (pref[right] - pref[left]) / (right - left))
              << std::endl;
  }
}

int main() {
  int number;
  std::cin >> number;
  std::vector<double> arr(number);
  std::vector<double> pref(number + 1);
  Input(arr);
  MakePref(arr, pref, number);
  SolveQueries(pref);
}
