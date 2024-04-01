#include <cstddef>
#include <climits>
#include <map>
#include <queue>
#include <cmath>

#define ull unsigned long long

using namespace std;

class FibonacciHeap {
private:
  struct FibonacciNode {
    pair<size_t, ull> key = make_pair(-1, ULLONG_MAX);
    size_t degree = 0;
    FibonacciNode* left = this;
    FibonacciNode* right = this;
    FibonacciNode* parent = nullptr;
    FibonacciNode* child = nullptr;
    bool marked = false;
    FibonacciNode() {
      degree = 0;
      left = right = this;
      parent = child = nullptr;
    }
  };
  struct FibonacciHead {
    size_t keyNum = 0;
    size_t maxDegree = 0;
    FibonacciNode* min = nullptr;
  };
  FibonacciHead* head = nullptr;
  map<size_t, FibonacciNode*> nodes = {};

  void removeNode(FibonacciNode* node);
  void addNode(FibonacciNode* node, FibonacciNode* root);
  void eraseChildern(FibonacciNode* root);
public:
  FibonacciHeap();
  ~FibonacciHeap();
  pair<size_t, ull> popMin();
  void push(size_t index, ull value);
  void decrease(size_t index, ull value);
};
