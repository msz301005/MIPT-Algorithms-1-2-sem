#include <bits/stdc++.h>

std::random_device rd;
std::mt19937 gen(rd());

using Pair = std::pair<int,int>;

struct Node {
  int key;
  int prior;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
  Node(int key, int prior) : key(key), prior(prior) {}
};

void Delete(Node*& ver) {
  if (ver == nullptr) {
    return;
  }
  Delete(ver->left);
  Delete(ver->right);
  delete ver;
}

void Insert(Node*& last_ver, Node*& ver) {
  if(last_ver == nullptr) {
    last_ver = ver;
    return;
  }
  if(last_ver->prior > ver->prior) {

  }
}



void Speed() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Speed();
}
