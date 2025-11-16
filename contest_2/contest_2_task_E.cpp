#include <bits/stdc++.h>
struct Type {
  int value;
  int number_smaller_right;
  int index;
};
bool operator<(const Type& elem1, const Type& elem2) {
  return elem1.value > elem2.value;
}
void Merge(std::vector<Type>& arr, int left, int right) {
  std::vector<Type> left_part;
  std::vector<Type> right_part;
  std::vector<Type> merge_arr(right - left);
  int mid = (left + right) / 2;
  for (int ind = left; ind < mid; ind++) {
    left_part.push_back(arr[ind]);
  }
  for (int ind = mid; ind < right; ind++) {
    right_part.push_back(arr[ind]);
  }
  int len_l = (int)left_part.size();
  int len_r = (int)right_part.size();
  for (int ind_l = 0, ind_r = 0; ind_l < len_l || ind_r < len_r;) {
    if (ind_l < len_l && ind_r < len_r &&
        left_part[ind_l].value > right_part[ind_r].value) {
      left_part[ind_l].number_smaller_right += len_r - ind_r;
    }
    if (ind_r == len_r ||
        (ind_l < len_l && left_part[ind_l] < right_part[ind_r])) {
      merge_arr[ind_l + ind_r] = left_part[ind_l];
      ++ind_l;
    } else {
      merge_arr[ind_l + ind_r] = right_part[ind_r];
      ++ind_r;
    }
  }
  for (long long ind = left; ind < right; ind++) {
    arr[ind] = merge_arr[ind - left];
  }
}
void MergeSort(std::vector<Type>& arr, int left, int right) {
  if (right - left <= 1) {
    return;
  }
  int mid = (left + right) / 2;
  MergeSort(arr, left, mid);
  MergeSort(arr, mid, right);
  Merge(arr, left, right);
}
bool Comp(const Type& elem1, const Type& elem2) {
  return elem1.index < elem2.index;
}
int main() {
  int number;
  std::cin >> number;
  std::vector<Type> arr(number);
  for (int ind = 0; ind < number; ++ind) {
    std::cin >> arr[ind].value;
    arr[ind].number_smaller_right = 0;
    arr[ind].index = ind;
  }
  MergeSort(arr, 0, number);
  std::sort(arr.begin(), arr.end(), Comp);
  for (auto& elem : arr) {
    std::cout << elem.number_smaller_right << ' ';
  }
}