#include <cstddef>
#include <climits>
#include <utility>

#define ull unsigned long long

using namespace std;

class linkedList {
private:
  struct listNode {
    size_t index = -1;
    ull value = ULLONG_MAX;
    listNode* prev = nullptr;
    listNode* next = nullptr;
  };
  listNode* head = nullptr;
public:
  linkedList();
  ~linkedList();
  pair<size_t, ull> popMin();
  void push(size_t index, ull value);
  void decrease(size_t index, ull value);
};