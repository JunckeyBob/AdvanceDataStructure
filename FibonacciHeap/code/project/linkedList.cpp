#include "linkedList.hpp"

linkedList::linkedList() {}

linkedList::~linkedList() {
  listNode* current = this->head;
  while (current != nullptr) {
    this->head = current->next;
    delete current;
    current = this->head;
  }
}

pair<size_t, ull> linkedList::popMin() {
  listNode* minNode = nullptr;
  size_t minIndex = -1;
  ull minValue = ULLONG_MAX;
  for (listNode* current = this->head; current != nullptr; current = current->next) if (current->value < minValue) {
    minNode = current;
    minIndex = current->index;
    minValue = current->value;
  }
  if (minNode != nullptr) {
    if (minNode->prev != nullptr) minNode->prev->next = minNode->next;
    if (minNode->next != nullptr) minNode->next->prev = minNode->prev;
    if (minNode == this->head) this->head = minNode->next;
    delete minNode;
  }
  return make_pair(minIndex, minValue);
}

void linkedList::push(size_t index, ull value) {
  listNode* current = new listNode;
  current->index = index;
  current->value = value;
  if (this->head != nullptr) this->head->prev = current;
  current->next = this->head;
  this->head = current;
}

void linkedList::decrease(size_t index, ull value) {
  listNode* current = this->head;
  while (current != nullptr) {
    if (current->index == index) {
      current->value = value;
      break;
    }
    current = current->next;
  }
}
