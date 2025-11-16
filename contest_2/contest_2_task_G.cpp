#include <bits/stdc++.h>
const long long kMod = (1 << 30);
void SiftUp(std::vector<int>& heap, int vertex) {
  if (vertex == 1) {
    return;
  }
  int parent = vertex / 2;
  if (heap[vertex] > heap[parent]) {
    std::swap(heap[vertex], heap[parent]);
    SiftUp(heap, parent);
  }
}
void SiftDown(std::vector<int>& heap, int vertex, int& size) {
  if (2 * vertex > size) {
    return;
  }
  int child = 2 * vertex;
  if (2 * vertex + 1 <= size && heap[2 * vertex + 1] > heap[2 * vertex]) {
    child = 2 * vertex + 1;
  }
  if (heap[child] > heap[vertex]) {
    std::swap(heap[vertex], heap[child]);
    SiftDown(heap, child, size);
  }
}
long long GetMax(std::vector<int>& heap) { return heap[1]; }
void ExtractMax(std::vector<int>& heap, int& size) {
  std::swap(heap[1], heap[size--]);
  SiftDown(heap, 1, size);
}
void Insert(std::vector<int>& heap, int& value, int& size) {
  ++size;
  if (size >= (int)heap.size()) {
    heap.push_back(value);
  } else {
    heap[size] = value;
  }
  SiftUp(heap, size);
}
void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}
void PrintFirstElems(std::vector<int>& heap, int& size, int& k_elems) {
  while (k_elems-- > 0) {
    ExtractMax(heap, size);
  }
  for (int ind = 1; ind < (int)heap.size(); ++ind) {
    std::cout << heap[ind] << ' ';
  }
}
int main() {
  Speed();
  std::vector<int> heap(1);
  int size = 0;
  int number;
  int k_elems;
  long long first_elem;
  long long const_x;
  long long const_y;
  std::cin >> number >> k_elems >> first_elem >> const_x >> const_y;
  for (int ind = 1; ind <= number; ++ind) {
    int current_elem = (const_x * first_elem + const_y) % kMod;
    if (ind <= k_elems) {
      Insert(heap, current_elem, size);
    } else if (current_elem < GetMax(heap)) {
      ExtractMax(heap, size);
      Insert(heap, current_elem, size);
    }
    first_elem = current_elem;
  }
  PrintFirstElems(heap, size, k_elems);
}