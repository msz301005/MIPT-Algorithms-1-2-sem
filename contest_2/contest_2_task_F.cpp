#include <bits/stdc++.h>

class Heap {
 public:

  Heap() { heap_.resize(1); }

  void SiftUp(long long vertex) {
    if (vertex == 1) {
      return;
    }
    long long parent = vertex / 2;
    if (heap_[vertex].first < heap_[parent].first) {
      std::swap(*heap_[vertex].second, *heap_[parent].second);
      std::swap(heap_[vertex], heap_[parent]);
      SiftUp(parent);
    }
  }

  void SiftDown(long long vertex) {
    if (2 * vertex > size_) {
      return;
    }
    long long child = 2 * vertex;
    if (2 * vertex + 1 <= size_ &&
        heap_[2 * vertex + 1].first < heap_[2 * vertex].first) {
      child = 2 * vertex + 1;
    }
    if (heap_[child].first < heap_[vertex].first) {
      std::swap(*heap_[vertex].second, *heap_[child].second);
      std::swap(heap_[vertex], heap_[child]);
      SiftDown(child);
    }
  }

  long long GetMin() { return heap_[1].first; }

  void ExtractMin() {
    std::swap(*heap_[1].second, *heap_[size_].second);
    std::swap(heap_[1], heap_[size_--]);
    SiftDown(1);
  }

  void Insert(std::vector<long long>::iterator& ptr,
              long long& value) {
    ++size_;
    if (size_ >= (long long)heap_.size()) {
      heap_.emplace_back(value, ptr);
    } else {
      heap_[size_] = {value, ptr};
    }
    *ptr = size_;
    SiftUp(size_);
  }

  void DecreaseKey(std::vector<long long>::iterator& ptr, long long& delta) {
    heap_[*ptr].first -= delta;
    SiftUp(*ptr);
  }

 private:
  std::vector<std::pair<long long, std::vector<long long>::iterator>> heap_;
  long long size_ = 0;
};

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
  Heap heap;
  long long queries;
  std::cin >> queries;
  std::vector<long long> pointers(queries);
  for (long long ind = 0; ind < queries; ++ind) {
    std::string operation;
    std::cin >> operation;
    if (operation == "insert") {
      long long value;
      std::cin >> value;
      auto it = pointers.begin() + ind;
      heap.Insert(it, value);
    } else if (operation == "getMin") {
      std::cout << heap.GetMin() << '\n';
    } else if (operation == "extractMin") {
      heap.ExtractMin();
    } else if (operation == "decreaseKey") {
      long long ptr;
      long long delta;
      std::cin >> ptr >> delta;
      --ptr;
      auto it = pointers.begin() + ptr;
      heap.DecreaseKey(it, delta);
    }
  }
}