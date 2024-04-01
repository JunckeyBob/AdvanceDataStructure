#include <cstddef>
#include <climits>
#include <utility>
#include <vector>
#include <map>

#define ull unsigned long long

using namespace std;

class binaryHeap {
private:
  vector<ull> values = {};
  map<size_t, size_t> indexes = {};
  map<size_t, size_t> places = {};
  size_t parent(size_t place) { return (place-1)/2; }
  size_t left(size_t place) { return 2*place+1; }
  size_t right(size_t place) { return 2*place+2; }
  void swap(size_t place1, size_t place2);
  void swapDown(size_t place);
  void swapUp(size_t place);
public:
  binaryHeap();
  ~binaryHeap();
  pair<size_t, ull> popMin();
  void push(size_t index, ull value);
  void decrease(size_t index, ull value);
};
