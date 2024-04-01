#include "FibonacciHeap.hpp"

void FibonacciHeap::removeNode(FibonacciNode* node) {
  node->left->right = node->right;
  node->right->left = node->left;
}

void FibonacciHeap::addNode(FibonacciNode* node, FibonacciNode* root) {
  node->left = root;
  node->right = root->right;
  root->right->left = node;
  root->right = node;
}

void FibonacciHeap::eraseChildern(FibonacciNode* root) {
  for (size_t i = 0; i < root->degree; ++i) {
    FibonacciNode* current = root->child;
    root->child = current->right;
    current->parent = nullptr;
    removeNode(current);
    if (head->min == nullptr) {
      head->min = current;
      current->left = current->right = current;
    }
    else addNode(current, head->min);
    current = current->right;
  }
  root->degree = 0;
  root->child = nullptr;
}

FibonacciHeap::FibonacciHeap() {
  head = new FibonacciHead;
}

FibonacciHeap::~FibonacciHeap() {
  if (head->min == nullptr) {
    delete head;
    return ;
  }
  queue<FibonacciNode*> current;
  current.push(head->min);
  while (!current.empty()) {
    FibonacciNode* temp = current.front();
    current.pop();
    if (temp->right != temp) current.push(temp->right);
    if (temp->child != nullptr) current.push(temp->child);
    removeNode(temp);
    delete temp;
  }
  delete head;
}

pair<size_t, ull> FibonacciHeap::popMin() {
  if (head->min == nullptr) return make_pair(-1, ULLONG_MAX);

  FibonacciNode* minNode = head->min;
  eraseChildern(minNode);
  if (minNode->right == minNode) head->min = nullptr;
  else {
    FibonacciNode* minSilbing = minNode->right;
    ull minValue = ULLONG_MAX;
    while (minSilbing != minNode) {
      if (minValue > minSilbing->key.second) {
        minValue = minSilbing->key.second;
        head->min = minSilbing;
      }
      minSilbing = minSilbing->right;
    }
  }
  removeNode(minNode);
  --(head->keyNum);
  pair<size_t, ull> minKey = minNode->key;
  nodes.erase(minKey.first);
  delete minNode;

  if (head->min != nullptr) {
    FibonacciNode* minNode = head->min;
    vector<FibonacciNode*> cons(size_t(log2(head->keyNum))+1, nullptr);
    FibonacciNode* minSilbing = minNode;
    FibonacciNode* next = minNode->right;
    do {
      FibonacciNode* occupied = cons[minSilbing->degree];
      while (occupied != nullptr) {
        cons[minSilbing->degree] = nullptr;
        if (occupied->key.second <= minSilbing->key.second) {
          ++(occupied->degree);
          removeNode(minSilbing);
          minSilbing->parent = occupied;
          if (occupied->child == nullptr) {
            occupied->child = minSilbing;
            minSilbing->left = minSilbing->right = minSilbing;
          } else addNode(minSilbing, occupied->child);
        } else {
          ++(minSilbing->degree);
          removeNode(occupied);
          occupied->parent = minSilbing;
          if (minSilbing->child == nullptr) {
            minSilbing->child = occupied;
            occupied->left = occupied->right = occupied;
          } else addNode(occupied, minSilbing->child);
        }
      }
      minSilbing = next;
      next = next->right;
    } while (next != minNode);
  }
  return minKey;
}

void FibonacciHeap::push(size_t index, ull value) {
  FibonacciNode* current = new FibonacciNode;
  current->key = make_pair(index, value);
  nodes[index] = current;
  if (head->min == nullptr) head->min = current;
  else {
    addNode(current, head->min);
    if (head->min->key.second > current->key.second)
      head->min = current;
  }
  ++(head->keyNum);
}

void FibonacciHeap::decrease(size_t index, ull value) {
  FibonacciNode* current = nodes[index];
  current->key.second = value;
  while (current->parent != nullptr && current->parent->key.second > current->key.second) {
    pair<size_t, ull> temp = current->key;
    current->key = current->parent->key;
    current->parent->key = temp;
    nodes[current->key.first] = current;
    current = current->parent;
    nodes[current->key.first] = current;
  }
  if (head->min->key.second > value) head->min = current;
}
