#include "linkedList.hpp"
#include "binaryHeap.hpp"
#include "FibonacciHeap.hpp"

#include <cstddef>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>

#define ull unsigned long long

using namespace std;

void initial(vector<vector<ull>>& distance, size_t maxIndex) {
    default_random_engine randomNumberGenerator(time(0));
    uniform_int_distribution<ull> randomNumberDistribution(0, maxIndex);
    distance.resize(maxIndex);
    for (size_t i = 0; i < maxIndex; ++i) {
      distance[i].resize(maxIndex);
      for (size_t j = 0; j < maxIndex; ++j)
        distance[i][j] = randomNumberDistribution(randomNumberGenerator);
    }
}

template <class Container>
double dijkstra(vector<vector<ull>>& distance, size_t maxIndex) {
  vector<bool> touched(maxIndex, false);
  vector<ull> dis(maxIndex, ULLONG_MAX);
  auto start = chrono::high_resolution_clock::now();
  Container container;
  container.push(0, 0);
  dis[0] = 0;
  while (true) {
    pair<size_t, ull> minNode = container.popMin();
    if (minNode.first == -1) break;
    touched[minNode.first] = true;
    for (size_t i = 0; i < maxIndex; ++i) if (!touched[i] && dis[i] > dis[minNode.first] + distance[minNode.first][i]) {
      if (dis[i] == ULLONG_MAX) container.push(i, dis[minNode.first] + distance[minNode.first][i]);
      else container.decrease(i, dis[minNode.first] + distance[minNode.first][i]);
      dis[i] = dis[minNode.first] + distance[minNode.first][i];
    }
  }
  auto end = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::duration<double>>(end-start).count();
}

int main(void) {
  size_t n = 3072;
  size_t count = 24;
  for (size_t i = 1; i <= n; ++i) {
    double averageLinkedList = 0;
    double averageBinaryHeap = 0;
    double averageFibonacci  = 0;
    for (size_t j = 0; j < count; ++j) {
      size_t maxIndex = i;
      vector<vector<ull>> distance;
      initial(distance, maxIndex);

      averageLinkedList += dijkstra<linkedList>(distance, maxIndex);
      averageBinaryHeap += dijkstra<binaryHeap>(distance, maxIndex);
      averageFibonacci  += dijkstra<FibonacciHeap>(distance, maxIndex);
    }
    averageLinkedList /= count;
    averageBinaryHeap /= count;
    averageFibonacci  /= count;
    cout << setw(12) << averageLinkedList << '\t';
    cout << setw(12) << averageBinaryHeap << '\t';
    cout << setw(12) << averageFibonacci << endl;
  }
}