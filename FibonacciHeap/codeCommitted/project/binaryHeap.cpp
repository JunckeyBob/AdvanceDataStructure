#include "binaryHeap.hpp"

// Function to swap two nodes in the heap
void binaryHeap::swap(size_t place1, size_t place2) {
  ull tempValue = values[place1]; // Store value of place1
  values[place1] = values[place2]; // Assign value of place2 to place1
  values[place2] = tempValue; // Assign stored value of place1 to place2

  size_t index1 = indexes[place1]; // Get index corresponding to place1
  size_t index2 = indexes[place2]; // Get index corresponding to place2
  indexes[place1] = index2; // Update index of place1 with index2
  indexes[place2] = index1; // Update index of place2 with index1
  places[index1] = place2; // Update place of index1 with place2
  places[index2] = place1; // Update place of index2 with place1
}

// Function to adjust the heap downwards from a given place
void binaryHeap::swapDown(size_t place) {
  size_t l = left(place); // Get left child
  size_t r = right(place); // Get right child
  size_t smallest = place; // Initialize smallest as current place
  if (l < values.size() && values[l] < values[smallest]) smallest = l; // If left child is smaller, update smallest
  if (r < values.size() && values[r] < values[smallest]) smallest = r; // If right child is smaller, update smallest
  while (smallest != place) { // Repeat until smallest is the same as place
    swap(place, smallest); // Swap place with smallest
    place = smallest; // Update place
    l = left(place); // Get left child
    r = right(place); // Get right child
    if (l < values.size() && values[l] < values[smallest]) smallest = l; // If left child is smaller, update smallest
    if (r < values.size() && values[r] < values[smallest]) smallest = r; // If right child is smaller, update smallest
  }
}

// Function to adjust the heap upwards from a given place
void binaryHeap::swapUp(size_t place) {
  while (place != 0 && values[parent(place)] > values[place]) { // Repeat until place is root or parent is smaller
    swap(place, parent(place)); // Swap place with its parent
    place = parent(place); // Update place
  }
}

// Constructor
binaryHeap::binaryHeap() {}

// Destructor
binaryHeap::~binaryHeap() {}

// Function to pop the minimum element from the heap
pair<size_t, ull> binaryHeap::popMin() {
  if (values.size() == 0) return make_pair(-1, ULLONG_MAX); // If heap is empty, return invalid pair
  ull value = values[0]; // Get minimum value
  size_t index = indexes[0]; // Get index of minimum value
  values[0] = values[values.size()-1]; // Replace minimum value with last value
  indexes[0] = indexes[values.size()-1]; // Update index of minimum value
  places[indexes[0]] = 0; // Update place of the index of minimum value
  values.pop_back(); // Remove last value from heap
  indexes.erase(values.size()); // Remove index of last value from map
  places.erase(index); // Remove place of the index from map
  swapDown(0); // Adjust heap downwards from root
  return make_pair(index, value); // Return pair of index and value
}

// Function to push a new element into the heap
void binaryHeap::push(size_t index, ull value) {
  size_t place = values.size(); // Get new place for the element
  places[index] = place; // Update place of the index
  indexes[place] = index; // Update index of the place
  values.push_back(value); // Add value to the heap
  swapUp(place); // Adjust heap upwards from the new place
}

// Function to decrease the value of an element in the heap
void binaryHeap::decrease(size_t index, ull value) {
  size_t place = places[index]; // Get place of the index
  values[place] = value; // Update value at the place
  swapUp(place); // Adjust heap upwards from the place
}
