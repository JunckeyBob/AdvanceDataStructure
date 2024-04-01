#include <cstddef>
#include <climits>
#include <utility>
#include <vector>
#include <map>

#define ull unsigned long long

using namespace std;

class binaryHeap {
private:
  vector<ull> values = {}; // Vector to store values in the heap
  map<size_t, size_t> indexes = {}; // Map to store indexes corresponding to their places in the heap
  map<size_t, size_t> places = {}; // Map to store places corresponding to their indexes in the heap
  size_t parent(size_t place) { return (place-1)/2; } // Function to find the parent of a node in the heap
  size_t left(size_t place) { return 2*place+1; } // Function to find the left child of a node in the heap
  size_t right(size_t place) { return 2*place+2; } // Function to find the right child of a node in the heap
  void swap(size_t place1, size_t place2); // Function to swap two nodes in the heap
  void swapDown(size_t place); // Function to adjust the heap downwards from a given place
  void swapUp(size_t place); // Function to adjust the heap upwards from a given place
public:
  binaryHeap(); // Constructor
  ~binaryHeap(); // Destructor
  pair<size_t, ull> popMin(); // Function to pop the minimum element from the heap
  void push(size_t index, ull value); // Function to push a new element into the heap
  void decrease(size_t index, ull value); // Function to decrease the value of an element in the heap
};