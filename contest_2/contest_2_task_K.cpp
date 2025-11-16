#include <bits/stdc++.h>

struct Type {
  std::stack<std::pair<int, int>> stack1;
  std::stack<std::pair<int, int>> stack2;
};

struct TypeLink {
  std::stack<std::pair<int, int>>& stack1_link;
  std::stack<std::pair<int, int>>& stack2_link;
};

void Move(std::stack<std::pair<int, int>>& stack1,
          std::stack<std::pair<int, int>>& stack2) {
  if (!stack2.empty()) {
    return;
  }
  while (!stack1.empty()) {
    int mi =
        (stack2.empty() ? stack1.top().first
                        : std::min(stack1.top().first, stack2.top().second));
    stack2.emplace(stack1.top().first, mi);
    stack1.pop();
  }
}

void Push(std::stack<std::pair<int, int>>& stack, int value) {
  int mi = (stack.empty() ? value : std::min(value, stack.top().second));
  stack.emplace(value, mi);
}

int Min(std::stack<std::pair<int, int>>& stack1,
        std::stack<std::pair<int, int>>& stack2) {
  if (stack1.empty()) {
    return stack2.top().second;
  }
  if (stack2.empty()) {
    return stack1.top().second;
  }
  return std::min(stack1.top().second, stack2.top().second);
}

int GetMinCol(TypeLink& col, std::vector<std::vector<int>>& arr, int& pos_i,
              int& pos_j, int& size) {
  if (pos_i < size) {
    for (int ind = 0; ind < size; ++ind) {
      Push(col.stack1_link, arr[ind][pos_j]);
    }
  } else {
    Move(col.stack1_link, col.stack2_link);
    col.stack2_link.pop();
    Push(col.stack1_link, arr[pos_i][pos_j]);
  }
  return Min(col.stack1_link, col.stack2_link);
}

int main() {
  int number;
  int size;
  std::cin >> number >> size;
  std::vector<std::vector<int>> arr(number, std::vector<int>(number));
  std::vector<Type> min_in_col(number);
  for (int i = 0; i < number; i++) {
    for (int j = 0; j < number; j++) {
      std::cin >> arr[i][j];
    }
  }
  for (int i = size - 1; i < number; ++i) {
    std::stack<std::pair<int, int>> stack_str1;
    std::stack<std::pair<int, int>> stack_str2;
    for (int j = 0; j < number; j++) {
      TypeLink col{min_in_col[j].stack1, min_in_col[j].stack2};
      int min_col = GetMinCol(col, arr, i, j, size);
      if (j < size) {
        Push(stack_str1, min_col);
        if (j == size - 1) {
          std::cout << Min(stack_str1, stack_str2) << ' ';
        }
      } else {
        Move(stack_str1, stack_str2);
        stack_str2.pop();
        Push(stack_str1, min_col);
        std::cout << Min(stack_str1, stack_str2) << ' ';
      }
    }
    std::cout << '\n';
  }
}