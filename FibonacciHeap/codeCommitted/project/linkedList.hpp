#include <cstddef>   // Provides definitions for size_t
#include <climits>   // Provides constants for limits of integral types
#include <utility>   // Provides std::pair and std::make_pair

#define ull unsigned long long   // Define ull as an alias for unsigned long long

using namespace std;   // Using the standard namespace

// Definition of the linkedList class
class linkedList {
private:
  // Definition of a private nested struct listNode
  struct listNode {
    size_t index = -1;          // Index of the node initialized to -1
    ull value = ULLONG_MAX;     // Value of the node initialized to maximum value of ull
    listNode* prev = nullptr;   // Pointer to the previous node initialized to nullptr
    listNode* next = nullptr;   // Pointer to the next node initialized to nullptr
  };
  listNode* head = nullptr;     // Pointer to the head of the linked list initialized to nullptr
public:
  linkedList();                 // Constructor declaration
  ~linkedList();                // Destructor declaration
  pair<size_t, ull> popMin();   // Method to remove and return the node with minimum value
  void push(size_t index, ull value);   // Method to insert a new node at the beginning
  void decrease(size_t index, ull value);   // Method to update the value of a node given its index
};
