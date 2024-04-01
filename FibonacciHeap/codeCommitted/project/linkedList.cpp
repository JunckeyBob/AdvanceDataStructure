#include "linkedList.hpp"

// Constructor definition
linkedList::linkedList() {}

// Destructor definition
linkedList::~linkedList() {
  listNode* current = this->head;   // Start from the head of the linked list
  while (current != nullptr) {      // Loop until the end of the list is reached
    this->head = current->next;     // Move head to the next node
    delete current;                 // Delete the current node
    current = this->head;           // Move to the next node
  }
}

// Method to remove and return the node with minimum value
pair<size_t, ull> linkedList::popMin() {
  listNode* minNode = nullptr;      // Pointer to the node with minimum value initialized to nullptr
  size_t minIndex = -1;             // Index of the node with minimum value initialized to -1
  ull minValue = ULLONG_MAX;        // Minimum value initialized to maximum value of ull
  // Iterate through the linked list to find the node with minimum value
  for (listNode* current = this->head; current != nullptr; current = current->next)
    if (current->value < minValue) {
      minNode = current;
      minIndex = current->index;
      minValue = current->value;
    }
  // If a node with minimum value is found, remove it from the list
  if (minNode != nullptr) {
    if (minNode->prev != nullptr) minNode->prev->next = minNode->next;
    if (minNode->next != nullptr) minNode->next->prev = minNode->prev;
    if (minNode == this->head) this->head = minNode->next;
    delete minNode;
  }
  // Return the index and value of the removed node as a pair
  return make_pair(minIndex, minValue);
}

// Method to insert a new node at the beginning of the linked list
void linkedList::push(size_t index, ull value) {
  listNode* current = new listNode;   // Create a new node
  current->index = index;             // Set its index
  current->value = value;             // Set its value
  if (this->head != nullptr) this->head->prev = current;   // Update the previous pointer of the current head
  current->next = this->head;         // Set the next pointer of the new node to the current head
  this->head = current;               // Update the head to point to the new node
}

// Method to update the value of a node given its index
void linkedList::decrease(size_t index, ull value) {
  listNode* current = this->head;     // Start from the head of the linked list
  // Iterate through the list to find the node with the given index
  while (current != nullptr) {
    if (current->index == index) {
      current->value = value;         // Update the value of the node if found
      break;
    }
    current = current->next;          // Move to the next node
  }
}
