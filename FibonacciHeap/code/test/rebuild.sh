#!/bin/bash

(cd ../project && g++ linkedList.hpp linkedList.cpp binaryHeap.hpp binaryHeap.cpp FibonacciHeap.hpp FibonacciHeap.cpp performanceTest.cpp -o ./../bin/performanceTest)