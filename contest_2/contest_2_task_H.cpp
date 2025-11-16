#include <bits/stdc++.h>

void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

class Heap {
 public:
  int operator[](int pos) { return heap_[pos]; }

  int GetSize() const { return size_; }

  void Clear() {
    heap_.assign(1, 0);
    size_ = real_size = 0;
  }

  void SiftUpMax(int vertex) {
    if (vertex == 1) {
      return;
    }
    int parent = vertex / 2;
    if (heap_[vertex] > heap_[parent]) {
      std::swap(heap_[vertex], heap_[parent]);
      SiftUpMax(parent);
    }
  }

  void SiftUpMin(int vertex) {
    if (vertex == 1) {
      return;
    }
    int parent = vertex / 2;
    if (heap_[vertex] < heap_[parent]) {
      std::swap(heap_[vertex], heap_[parent]);
      SiftUpMin(parent);
    }
  }

  void SiftDownMax(int vertex) {
    if (2 * vertex > size_) {
      return;
    }
    int child = 2 * vertex;
    if (2 * vertex + 1 <= size_ && heap_[2 * vertex + 1] > heap_[2 * vertex]) {
      child = 2 * vertex + 1;
    }
    if (heap_[child] > heap_[vertex]) {
      std::swap(heap_[vertex], heap_[child]);
      SiftDownMax(child);
    }
  }

  void SiftDownMin(int vertex) {
    if (2 * vertex > size_) {
      return;
    }
    int child = 2 * vertex;
    if (2 * vertex + 1 <= size_ && heap_[2 * vertex + 1] < heap_[2 * vertex]) {
      child = 2 * vertex + 1;
    }
    if (heap_[child] < heap_[vertex]) {
      std::swap(heap_[vertex], heap_[child]);
      SiftDownMin(child);
    }
  }

  long long Get() { return heap_[1]; }

  void ExtractMin() {
    std::swap(heap_[1], heap_[size_--]);
    SiftDownMin(1);
  }

  void ExtractMax() {
    std::swap(heap_[1], heap_[size_--]);
    SiftDownMax(1);
  }

  void InsertInMax(int& value) {
    ++size_;
    if (size_ >= (int)heap_.size()) {
      heap_.push_back(value);
    } else {
      heap_[size_] = value;
    }
    SiftUpMax(size_);
  }

  void InsertInMin(int& value) {
    ++size_;
    if (size_ >= (int)heap_.size()) {
      heap_.push_back(value);
    } else {
      heap_[size_] = value;
    }
    SiftUpMin(size_);
  }

  static void SetRealSize(int delta) { real_size += delta; }

  static int GetRealSize() { return real_size; }

 private:
  std::vector<int> heap_{0};
  int size_ = 0;
  static int real_size;
};

int Heap::real_size = 0;

void SolveInsert(Heap& heap_max, Heap& heap_min) {
  int value;
  std::cin >> value;
  heap_max.InsertInMax(value);
  heap_min.InsertInMin(value);
  Heap::SetRealSize(1);
  std::cout << "ok\n";
}

void CleaningHeapMax(Heap& heap, Heap& heap_deleted) {
  while (heap.GetSize() > 0 && heap_deleted.GetSize() > 0 &&
         heap.Get() == heap_deleted.Get()) {
    heap.ExtractMax();
    heap_deleted.ExtractMax();
  }
}

void CleaningHeapMin(Heap& heap, Heap& heap_deleted) {
  while (heap.GetSize() > 0 && heap_deleted.GetSize() > 0 &&
         heap.Get() == heap_deleted.Get()) {
    heap.ExtractMin();
    heap_deleted.ExtractMin();
  }
}

void SolveExtractMin(Heap& heap_min, Heap& heap_max, Heap& heap_max_deleted,
                     Heap& heap_min_deleted) {
  if (Heap::GetRealSize() == 0) {
    std::cout << "error\n";
    return;
  }
  int value = heap_min.Get();
  heap_max_deleted.InsertInMax(value);
  CleaningHeapMax(heap_max, heap_max_deleted);
  heap_min.ExtractMin();
  CleaningHeapMin(heap_min, heap_min_deleted);
  Heap::SetRealSize(-1);
  std::cout << value << '\n';
}

void SolveGetMin(Heap& heap_min, Heap& heap_min_deleted) {
  if (Heap::GetRealSize() == 0) {
    std::cout << "error\n";
    return;
  }
  CleaningHeapMin(heap_min, heap_min_deleted);
  std::cout << heap_min.Get() << '\n';
}

void SolveExtractMax(Heap& heap_max, Heap& heap_min, Heap& heap_max_deleted,
                     Heap& heap_min_deleted) {
  if (Heap::GetRealSize() == 0) {
    std::cout << "error\n";
    return;
  }
  int value = heap_max.Get();
  heap_min_deleted.InsertInMin(value);
  CleaningHeapMin(heap_min, heap_min_deleted);
  heap_max.ExtractMax();
  CleaningHeapMax(heap_max, heap_max_deleted);
  Heap::SetRealSize(-1);
  std::cout << value << '\n';
}

void SolveGetMax(Heap& heap_max, Heap& heap_max_deleted) {
  if (Heap::GetRealSize() == 0) {
    std::cout << "error\n";
    return;
  }
  CleaningHeapMax(heap_max, heap_max_deleted);
  std::cout << heap_max.Get() << '\n';
}

int main() {
  Speed();
  Heap heap_min;
  Heap heap_max;
  Heap heap_min_deleted;
  Heap heap_max_deleted;
  int number;
  std::cin >> number;
  for (int ind = 0; ind < number; ++ind) {
    std::string operation;
    std::cin >> operation;
    if (operation == "insert") {
      SolveInsert(heap_max, heap_min);
    } else if (operation == "extract_min") {
      SolveExtractMin(heap_min, heap_max, heap_max_deleted, heap_min_deleted);
    } else if (operation == "get_min") {
      SolveGetMin(heap_min, heap_min_deleted);
    } else if (operation == "extract_max") {
      SolveExtractMax(heap_max, heap_min, heap_max_deleted, heap_min_deleted);
    } else if (operation == "get_max") {
      SolveGetMax(heap_max, heap_max_deleted);
    } else if (operation == "size") {
      std::cout << Heap::GetRealSize() << '\n';
    } else if (operation == "clear") {
      heap_min.Clear();
      heap_max.Clear();
      heap_min_deleted.Clear();
      heap_max_deleted.Clear();
      std::cout << "ok\n";
    }
  }
}
