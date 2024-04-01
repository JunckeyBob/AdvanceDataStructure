#include <cstddef>   // Provides definitions for size_t
#include <climits>   // Provides constants for limits of integral types
#include <map>       // Provides std::map for associative arrays
#include <queue>     // Provides std::queue for breadth-first traversal
#include <cmath>     // Provides mathematical functions

#define ull unsigned long long   // Define ull as an alias for unsigned long long

using namespace std;   // Using the standard namespace

// Definition of the FibonacciHeap class
class FibonacciHeap {
private:
  // Definition of a private nested struct FibonacciNode representing nodes in the heap
  struct FibonacciNode {
    pair<size_t, ull> key = make_pair(-1, ULLONG_MAX);   // Key stored in the node, initialized to a sentinel value
    size_t degree = 0;                                   // Degree of the node (number of children)
    FibonacciNode* left = this;                          // Pointer to the left sibling node
    FibonacciNode* right = this;                         // Pointer to the right sibling node
    FibonacciNode* parent = nullptr;                     // Pointer to the parent node
    FibonacciNode* child = nullptr;                      // Pointer to the child node
    bool marked = false;                                 // Flag indicating if the node has lost a child since the last time it was made the child of another node
    // Constructor initializing the node
    FibonacciNode() {
      degree = 0;
      left = right = this;
      parent = child = nullptr;
    }
  };
  
  // Definition of a private nested struct FibonacciHead representing the head of the Fibonacci heap
  struct FibonacciHead {
    size_t keyNum = 0;             // Number of keys in the heap
    size_t maxDegree = 0;          // Maximum degree among all nodes in the heap
    FibonacciNode* min = nullptr;  // Pointer to the minimum node in the heap
  };

  FibonacciHead* head = nullptr;   // Pointer to the head of the Fibonacci heap
  map<size_t, FibonacciNode*> nodes = {};   // Map to store nodes by their index

  // Private helper method to remove a node from the heap
  void removeNode(FibonacciNode* node);
  // Private helper method to add a node to the list of children of another node
  void addNode(FibonacciNode* node, FibonacciNode* root);
  // Private helper method to erase the children of a given node
  void eraseChildren(FibonacciNode* root);

public:
  FibonacciHeap();                // Constructor declaration
  ~FibonacciHeap();               // Destructor declaration
  pair<size_t, ull> popMin();     // Method to remove and return the minimum key from the heap
  void push(size_t index, ull value);    // Method to insert a key-value pair into the heap
  void decrease(size_t index, ull value);  // Method to decrease the value of a key in the heap
};
