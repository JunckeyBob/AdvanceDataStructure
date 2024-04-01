#include "binaryHeap.hpp"

void binaryHeap::swap(size_t place1, size_t place2) {
  ull tempValue = values[place1];
  values[place1] = values[place2];
  values[place2] = tempValue;

  size_t index1 = indexes[place1];
  size_t index2 = indexes[place2];
  indexes[place1] = index2;
  indexes[place2] = index1;
  places[index1] = place2;
  places[index2] = place1;
}

void binaryHeap::swapDown(size_t place) {
  size_t l = left(place);
  size_t r = right(place);
  size_t smallest = place;
  if (l < values.size() && values[l] < values[smallest]) smallest = l;
  if (r < values.size() && values[r] < values[smallest]) smallest = r;
  while (smallest != place) {
    swap(place, smallest);
    place = smallest;
    l = left(place);
    r = right(place);
    if (l < values.size() && values[l] < values[smallest]) smallest = l;
    if (r < values.size() && values[r] < values[smallest]) smallest = r;
  }
}

void binaryHeap::swapUp(size_t place) {
  while (place != 0 && values[parent(place)] > values[place]) {
    swap(place, parent(place));
    place = parent(place);
  }
}

binaryHeap::binaryHeap() {}

binaryHeap::~binaryHeap() {}

pair<size_t, ull> binaryHeap::popMin() {
  if (values.size() == 0) return make_pair(-1, ULLONG_MAX);
  ull value = values[0];
  size_t index = indexes[0];
  values[0] = values[values.size()-1];
  indexes[0] = indexes[values.size()-1];
  places[indexes[0]] = 0;
  values.pop_back();
  indexes.erase(values.size());
  places.erase(index);
  swapDown(0);
  return make_pair(index, value);
}

void binaryHeap::push(size_t index, ull value) {
  size_t place = values.size();
  places[index] = place;
  indexes[place] = index;
  values.push_back(value);
  swapUp(place);
}

void binaryHeap::decrease(size_t index, ull value) {
  size_t place = places[index];
  values[place] = value;
  swapUp(place);
}
