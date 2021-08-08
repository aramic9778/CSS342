//
// Created by Yusuf Pisan on 4/26/18.
//

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int d = skip.maxLevel - 1; d >= 0; d--) {
    out << d << ": ";
    auto *curr = skip.head->forward[d];
    if (curr != skip.tail) {
      out << curr->value;
      curr = curr->forward[d];
    }
    while (curr != nullptr && curr != skip.tail) {
      out << "-->" << curr->value;
      curr = curr->forward[d];
    }
    out << endl;
  }
  return out;
}

SNode::SNode(int value) : value{value} { // clear forward and backward nodes
  forward.clear();
  backward.clear();
}

// how many forward/backward pointers it has
int SNode::height() const { return forward.size(); }

// increase the number of forward/backward pointers it has
void SNode::increaseHeight() {
  forward.push_back(nullptr);  // pointer from the front
  backward.push_back(nullptr); // pointer from the back
}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 &&
         probability < 100); // if probability and max level legit go ahead
  head = new SNode(INT_MIN); // INT_MIN for head
  tail = new SNode(INT_MAX); // INT_MAX for tail
  for (int i = 0; i < maxLevel; i++) { // lop for all levels
    head->forward.push_back(tail);     // link head with tail
    head->backward.push_back(nullptr); // link head with backward pointer
    tail->forward.push_back(nullptr);  // link tail with forward pointer
    tail->backward.push_back(head);    // link tail with head
  }
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) {
  for (auto v : values) { // for all values in vector of Nodes
    if (!add(v)) {
      return false; // false if couldn't add
    }
  }
  return true; // true if added
}

bool SkipList::add(int value) {
  SNode *ptr = containsSNode(value); // create a node with value from argument
  if (ptr != nullptr) { // return false if this node exist in skiplist
    return false;
  }
  vector<SNode *> before =
      getBeforeNodes(value); // create vector of Snodes which shows nodes before
  int lvl = 0;
  auto newnode = new SNode(value); // create new node with value
  do {                             //
    newnode->increaseHeight();     // increase height of level
    SNode *b = before[lvl];
    SNode *d = before[lvl]->forward[lvl];
    connect3AtLevel(b, newnode, d,
                    lvl); // connect backward, newnode and forward
    lvl++;                // increase level
  } while (shouldInsertAtHigher() &&
           lvl < maxLevel); // while possible to add levels

  return true;
}

SkipList::~SkipList() {
  // need to delete individual nodes
  SNode *ptr = head;               // create new Node which refer to head
  while (ptr != nullptr) {         // while node address doesn't equal nullptr
    SNode *next = ptr->forward[0]; // next equals forward pointer
    ptr->forward.clear();          // clear forward
    ptr->backward.clear();         // clear backward
    delete ptr;                    // delete memory location
    ptr = next;                    // assign next to pointer
  }
}

bool SkipList::remove(int data) {
  SNode *ptr = containsSNode(
      data); // using method containsNode to check if list has this value
  if (ptr == nullptr) { // if not return false
    return false;
  }
  int levels = ptr->height();              // get a number of levels
  for (int lvl = 0; lvl < levels; lvl++) { // for all levels loop
    SNode *b = ptr->backward[lvl];         // taking a link of backward node
    SNode *d = ptr->forward[lvl];          // taking a link of forward node
    connect2AtLevel(b, d, lvl);            // connect backward and forward nodes
  }
  ptr->backward.clear(); // clear backward address
  ptr->forward.clear();  // clear forward address
  delete ptr;            // delete memory location of pointer
  return true;
}

// get the node that would be before this data
// at level-0
vector<SNode *> SkipList::getBeforeNodes(int data) const {
  vector<SNode *> v(maxLevel);
  for (int i = maxLevel - 1; i >= 0;
       i--) { // loop for all level from higher to lower
    SNode *ptr = head;
    while (ptr->forward[i]->value <
           data) {           // while node' s forward value less than data
      ptr = ptr->forward[i]; // go forward
    }
    v[i] = ptr; // write node to vector
  }
  return v; // return vector with all nodes before
}

SNode *SkipList::containsSNode(int data) const {
  SNode *ptr = head; // create new Node which refer to head
  for (int lvl = maxLevel - 1; lvl >= 0;
       lvl--) { // loop for all level from higher to lower
    while (ptr->forward[lvl]->value <=
           data) { // while node' s forward value less or equal than data
      if (ptr->forward[lvl]->value == data) { // if equals return node
        return ptr->forward[lvl];
      }
      ptr = ptr->forward[lvl]; // next node
    }
  }
  return nullptr; // return nullptr if didn't find
}

bool SkipList::contains(int data) const {
  SNode *ptr = head; // create new Node which refer to head
  for (int lvl = maxLevel - 1; lvl >= 0;
       lvl--) { // loop for all level from higher to lower
    while (ptr->forward[lvl]->value <=
           data) { // while node' s forward value less or equal than data
      if (ptr->forward[lvl]->value == data) { // if equals return true
        return true;
      }
      ptr = ptr->forward[lvl]; // next node
    }
  }
  return false; // return false if didn't find
}

void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {
  a->forward[level] = b;  // connect forward link of a to b
  b->backward[level] = a; // connect forward link of a to b
}

void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {
  connect2AtLevel(a, b, level);
  connect2AtLevel(b, c,
                  level); // connceting 3 nodes by using connect2AtLevel method
}