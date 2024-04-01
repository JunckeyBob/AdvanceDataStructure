#include "FibonacciHeap.hpp"

// Helper method to remove a node from the linked list of nodes
void FibonacciHeap::removeNode(FibonacciNode* node) {
  node->left->right = node->right;  // Adjust the pointers to skip the node being removed
  node->right->left = node->left;
}

// Helper method to add a node to the list of children of another node
void FibonacciHeap::addNode(FibonacciNode* node, FibonacciNode* root) {
  node->left = root;            // Set the left pointer of the new node to the root
  node->right = root->right;    // Set the right pointer of the new node to the right of the root
  root->right->left = node;     // Adjust the left pointer of the root's right neighbor to point to the new node
  root->right = node;           // Adjust the right pointer of the root to point to the new node
}

// Helper method to erase the children of a given node
void FibonacciHeap::eraseChildren(FibonacciNode* root) {
  for (size_t i = 0; i < root->degree; ++i) {
    FibonacciNode* current = root->child;  // Get the child of the root
    root->child = current->right;          // Update the child pointer of the root
    current->parent = nullptr;             // Reset the parent pointer of the child
    removeNode(current);                   // Remove the child from the linked list
    if (head->min == nullptr) {            // If there is no minimum node in the heap
      head->min = current;                 // Set the current child as the new minimum
      current->left = current->right = current;  // Update the pointers to make it a circular list
    } else {
      addNode(current, head->min);         // Add the current child to the list of roots
    }
    current = current->right;               // Move to the next child
  }
  root->degree = 0;                        // Reset the degree of the root
  root->child = nullptr;                   // Reset the child pointer of the root
}

// Constructor definition
FibonacciHeap::FibonacciHeap() {
  head = new FibonacciHead;   // Create a new FibonacciHead object and assign its address to head
}

// Destructor definition
FibonacciHeap::~FibonacciHeap() {
  if (head->min == nullptr) {  // If the heap is empty
    delete head;               // Delete the head
    return;                    // Exit the function
  }
  queue<FibonacciNode*> current;   // Create a queue to perform breadth-first traversal
  current.push(head->min);         // Push the minimum node into the queue
  while (!current.empty()) {       // Continue until the queue becomes empty
    FibonacciNode* temp = current.front();  // Get the front node from the queue
    current.pop();                          // Remove the front node from the queue
    if (temp->right != temp) current.push(temp->right);  // Push the right sibling into the queue if it exists
    if (temp->child != nullptr) current.push(temp->child);  // Push the child into the queue if it exists
    removeNode(temp);  // Remove the current node from the linked list
    delete temp;       // Delete the current node
  }
  delete head;  // Delete the head
}

// This part of the code defines the methods of the FibonacciHeap class: popMin, push, and decrease.
// These methods perform operations on the Fibonacci heap data structure, including removing the minimum element,
// inserting a new element, and decreasing the value of an existing element.

// Method to remove and return the minimum key from the heap
pair<size_t, ull> FibonacciHeap::popMin() {
  if (head->min == nullptr) return make_pair(-1, ULLONG_MAX);  // If the heap is empty, return a sentinel value

  FibonacciNode* minNode = head->min;  // Get the minimum node from the heap
  eraseChildren(minNode);              // Erase the children of the minimum node
  if (minNode->right == minNode) head->min = nullptr;  // If there is only one node in the heap, set min to nullptr
  else {
    FibonacciNode* minSibling = minNode->right;  // Get the right sibling of the minimum node
    ull minValue = ULLONG_MAX;                   // Initialize the minimum value to the maximum possible value
    while (minSibling != minNode) {              // Iterate over the siblings of the minimum node
      if (minValue > minSibling->key.second) {  // Update the minimum value if a smaller value is found
        minValue = minSibling->key.second;
        head->min = minSibling;  // Update the min pointer to point to the new minimum node
      }
      minSibling = minSibling->right;  // Move to the next sibling
    }
  }
  removeNode(minNode);       // Remove the minimum node from the linked list
  --(head->keyNum);          // Decrease the number of keys in the heap
  pair<size_t, ull> minKey = minNode->key;  // Get the key of the minimum node
  nodes.erase(minKey.first);  // Erase the node from the map of nodes
  delete minNode;             // Delete the minimum node

  if (head->min != nullptr) {  // If the heap is not empty after removing the minimum node
    FibonacciNode* minNode = head->min;  // Get the new minimum node
    vector<FibonacciNode*> cons(size_t(log2(head->keyNum)) + 1, nullptr);  // Create an array to store nodes with the same degree
    FibonacciNode* minSibling = minNode;  // Initialize the sibling pointer to the minimum node
    FibonacciNode* next = minNode->right; // Get the next node in the circular list
    do {
      FibonacciNode* occupied = cons[minSibling->degree];  // Get the node with the same degree as the current node
      while (occupied != nullptr) {   // Merge nodes with the same degree until no more nodes with the same degree are found
        cons[minSibling->degree] = nullptr;  // Reset the entry in the array
        if (occupied->key.second <= minSibling->key.second) {  // If the occupied node has a smaller key
          ++(occupied->degree);  // Increase the degree of the occupied node
          removeNode(minSibling);  // Remove the current node from the linked list
          minSibling->parent = occupied;  // Set the parent pointer of the current node
          if (occupied->child == nullptr) {  // If the occupied node has no children
            occupied->child = minSibling;  // Make the current node its child
            minSibling->left = minSibling->right = minSibling;  // Make the current node a circular list
          } else {
            addNode(minSibling, occupied->child);  // Add the current node to the list of children of the occupied node
          }
        } else {  // If the current node has a smaller key
          ++(minSibling->degree);
          removeNode(occupied);
          occupied->parent = minSibling;
          if (minSibling->child == nullptr) {
            minSibling->child = occupied;
            occupied->left = occupied->right = occupied;
          } else
            addNode(occupied, minSibling->child);
        }
      }
      minSibling = next;
      next = next->right;
    } while (next != minNode);
  }

  // Return the minimum key
  return minKey;
}

// Method to insert a key-value pair into the heap
void FibonacciHeap::push(size_t index, ull value) {
  // Create a new FibonacciNode with the given key-value pair
  FibonacciNode* current = new FibonacciNode;
  current->key = make_pair(index, value);

  // Store the node in the map of nodes
  nodes[index] = current;

  // Insert the node into the heap
  if (head->min == nullptr)
    head->min = current; // If the heap is empty, set the current node as the minimum
  else {
    addNode(current, head->min); // Add the current node to the list of roots
    // Update the minimum pointer if necessary
    if (head->min->key.second > current->key.second)
      head->min = current;
  }

  // Increment the number of keys in the heap
  ++(head->keyNum);
}

// Method to decrease the value of a key in the heap
void FibonacciHeap::decrease(size_t index, ull value) {
  // Get the node associated with the given index
  FibonacciNode* current = nodes[index];

  // Update the value of the key
  current->key.second = value;

  // Cascade up to maintain heap order property
  while (current->parent != nullptr && current->parent->key.second > current->key.second) {
    // Swap the keys of the current node and its parent
    pair<size_t, ull> temp = current->key;
    current->key = current->parent->key;
    current->parent->key = temp;

    // Update the node in the map of nodes
    nodes[current->key.first] = current;

    // Move to the parent node
    current = current->parent;

    // Update the node in the map of nodes
    nodes[current->key.first] = current;
  }

  // Update the minimum pointer if necessary
  if (head->min->key.second > value)
    head->min = current;
}