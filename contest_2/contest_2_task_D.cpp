#include <bits/stdc++.h>

class IQ {
 public:
  void Move();

  int GetMin();

  bool EmptyAdd() const { return add_.empty(); }

  bool EmptyQuery() const { return query_.empty(); }

  auto TopAdd() const { return add_.top(); }

  auto TopQuery() const { return query_.top(); }

  void PopQuery() { query_.pop(); }

  size_t SizeAdd() const { return add_.size(); }

  size_t SizeQuery() const { return query_.size(); }

  void EmplaceAdd(int iq_freshman, int min_iq) {
    add_.emplace(iq_freshman, min_iq);
  }

  void Clear() { add_ = query_ = std::stack<std::pair<int, int>>(); }

 private:
  std::stack<std::pair<int, int>> add_;
  std::stack<std::pair<int, int>> query_;
};

void IQ::Move() {
  if (!query_.empty()) {
    return;
  }
  while (!add_.empty()) {
    int min_iq =
        (query_.empty() ? add_.top().first
                        : std::min(add_.top().first, query_.top().second));
    query_.emplace(add_.top().first, min_iq);
    add_.pop();
  }
}

int IQ::GetMin() {
  if (add_.empty()) {
    return query_.top().second;
  }
  if (query_.empty()) {
    return add_.top().second;
  }
  return std::min(query_.top().second, add_.top().second);
}

int main() {
  int number;
  std::cin >> number;
  IQ iq;
  while (number-- > 0) {
    std::string operation;
    std::cin >> operation;
    if (operation == "enqueue") {
      int iq_freshman;
      std::cin >> iq_freshman;
      int min_iq = (iq.EmptyAdd() ? iq_freshman
                                  : std::min(iq_freshman, iq.TopAdd().second));
      iq.EmplaceAdd(iq_freshman, min_iq);
      std::cout << "ok\n";
    } else if (operation == "dequeue") {
      if (iq.EmptyAdd() && iq.EmptyQuery()) {
        std::cout << "error\n";
        continue;
      }
      iq.Move();
      std::cout << iq.TopQuery().first << '\n';
      iq.PopQuery();
    } else if (operation == "front") {
      if (iq.EmptyAdd() && iq.EmptyQuery()) {
        std::cout << "error\n";
        continue;
      }
      iq.Move();
      std::cout << iq.TopQuery().first << '\n';
    } else if (operation == "size") {
      std::cout << iq.SizeQuery() + iq.SizeAdd() << '\n';
    } else if (operation == "clear") {
      iq.Clear();
      std::cout << "ok\n";
    } else if (operation == "min") {
      if (iq.EmptyAdd() && iq.EmptyQuery()) {
        std::cout << "error\n";
        continue;
      }
      std::cout << iq.GetMin() << '\n';
    }
  }
}