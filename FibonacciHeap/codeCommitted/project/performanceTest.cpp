#include "linkedList.hpp"
#include "binaryHeap.hpp"
#include "FibonacciHeap.hpp"

#include <cstddef>        // For size_t
#include <vector>         // For vector
#include <cmath>          // For log2
#include <chrono>         // For timing
#include <random>         // For random number generation
#include <iostream>       // For input/output operations
#include <iomanip>        // For formatting output

#define ull unsigned long long   // Define ull as unsigned long long

using namespace std;

// Function to initialize the distance matrix with random values
void initial(vector<vector<ull>>& distance, size_t maxIndex) {
    default_random_engine randomNumberGenerator(time(0));  // Seed random number generator with current time
    uniform_int_distribution<ull> randomNumberDistribution(0, maxIndex);  // Define uniform distribution
    distance.resize(maxIndex);  // Resize the distance matrix
    for (size_t i = 0; i < maxIndex; ++i) {
      distance[i].resize(maxIndex);  // Resize each row of the distance matrix
      for (size_t j = 0; j < maxIndex; ++j)
        distance[i][j] = randomNumberDistribution(randomNumberGenerator);  // Assign random values to each cell
    }
}

// Function template to perform Dijkstra's algorithm using a specific priority queue implementation
template <class Container>
double dijkstra(vector<vector<ull>>& distance, size_t maxIndex) {
  vector<bool> touched(maxIndex, false);  // Initialize vector to keep track of touched nodes
  vector<ull> dis(maxIndex, ULLONG_MAX);  // Initialize vector to keep track of shortest distances
  auto start = chrono::high_resolution_clock::now();  // Start measuring execution time
  Container container;  // Create an instance of the priority queue container
  container.push(0, 0);  // Push the source node with distance 0 into the priority queue
  dis[0] = 0;  // Set distance of source node to 0
  while (true) {
    pair<size_t, ull> minNode = container.popMin();  // Extract the minimum distance node from the priority queue
    if (minNode.first == -1) break;  // If there are no more nodes to process, break the loop
    touched[minNode.first] = true;  // Mark the extracted node as touched
    // Update distances to adjacent nodes
    for (size_t i = 0; i < maxIndex; ++i) {
      if (!touched[i] && dis[i] > dis[minNode.first] + distance[minNode.first][i]) {
        // If the distance to node i through minNode is shorter than the current distance, update it
        if (dis[i] == ULLONG_MAX) 
          container.push(i, dis[minNode.first] + distance[minNode.first][i]);  // If i is not yet in the priority queue, push it
        else 
          container.decrease(i, dis[minNode.first] + distance[minNode.first][i]);  // If i is already in the priority queue, decrease its key
        dis[i] = dis[minNode.first] + distance[minNode.first][i];  // Update the shortest distance to node i
      }
    }
  }
  auto end = chrono::high_resolution_clock::now();  // Stop measuring execution time
  return chrono::duration_cast<chrono::duration<double>>(end-start).count();  // Return the elapsed time
}

// Main function
int main(void) {
  size_t n = 3072;  // Maximum index for testing
  size_t count = 24;  // Number of iterations for averaging
  for (size_t i = 1; i <= n; ++i) {
    double averageLinkedList = 0;  // Initialize average time for linked list
    double averageBinaryHeap = 0;   // Initialize average time for binary heap
    double averageFibonacci  = 0;   // Initialize average time for Fibonacci heap
    for (size_t j = 0; j < count; ++j) {
      size_t maxIndex = i;  // Set the size of the graph
      vector<vector<ull>> distance;  // Initialize distance matrix
      initial(distance, maxIndex);  // Initialize distance matrix with random values

      // Run Dijkstra's algorithm using linked list as priority queue
      averageLinkedList += dijkstra<linkedList>(distance, maxIndex);
      
      // Run Dijkstra's algorithm using binary heap as priority queue
      averageBinaryHeap += dijkstra<binaryHeap>(distance, maxIndex);
      
      // Run Dijkstra's algorithm using Fibonacci heap as priority queue
      averageFibonacci  += dijkstra<FibonacciHeap>(distance, maxIndex);
    }
    // Calculate average times
    averageLinkedList /= count;
    averageBinaryHeap /= count;
    averageFibonacci  /= count;
    
    // Output average times for each priority queue implementation
    cout << setw(12) << averageLinkedList << '\t';  // Linked list average time
    cout << setw(12) << averageBinaryHeap << '\t';  // Binary heap average time
    cout << setw(12) << averageFibonacci << endl;   // Fibonacci heap average time
  }
}
