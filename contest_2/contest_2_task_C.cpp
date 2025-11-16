#include <bits/stdc++.h>
void SwapGoblins(std::deque<int>& leaving_goblins,
                 std::deque<int>& coming_goblins) {
  if (coming_goblins.size() > leaving_goblins.size()) {
    leaving_goblins.push_back(coming_goblins.front());
    coming_goblins.pop_front();
  }
  if (leaving_goblins.size() > coming_goblins.size() + 1) {
    coming_goblins.push_front(leaving_goblins.back());
    leaving_goblins.pop_back();
  }
}
int main() {
  int number;
  std::cin >> number;
  std::deque<int> leaving_goblins;
  std::deque<int> coming_goblins;
  while (number-- > 0) {
    char operation;
    std::cin >> operation;
    if (operation == '+') {
      int goblin;
      std::cin >> goblin;
      coming_goblins.push_back(goblin);
    } else if (operation == '-') {
      std::cout << leaving_goblins.front() << '\n';
      leaving_goblins.pop_front();
    } else {
      int goblin;
      std::cin >> goblin;
      leaving_goblins.push_back(goblin);
    }
    SwapGoblins(leaving_goblins, coming_goblins);
  }
}