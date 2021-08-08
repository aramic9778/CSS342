
#include "library.h"
#include <iostream>

using namespace std;
// implementing << function
ostream &operator<<(ostream &out, const Library &lib) {
  out << "[";
  for (int i = 0; i < lib.size(); i++) {
    out << lib.at(i);
    // don't use comma for last book
    if (i < (lib.size() - 1)) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}

// Use the compiler generated constructor
Library::Library() = default;

// Return size
int Library::size() const { return libooks; }

// Return maximum size
int Library::max_size() const { return MAX; }

// Test whether Library is empty
bool Library::empty() const { return (libooks == 0); }

// Access element
const string &Library::at(int n) const {
  if ((n > -1) && (libooks > n)) {
    return Books[n];
  }
  // error message for invalid parameter
  std::cout << "Error: Cannot access element at " << n << endl;
  return error;
}

// Access first element
const string &Library::front() const {
  if (!empty()) {
    return Books[0];
  }
  // error message for invalid parameter
  std::cout << "Error: Cannot access front for empty Library" << endl;
  return error;
}

// Access last element (public member function )
const string &Library::back() const {
  if (!empty()) {
    return Books[libooks - 1];
  }
  // error message for invalid parameter
  std::cout << "Error: Cannot access back for empty Library" << endl;
  return error;
}

// Add element at the end
void Library::push_back(const string &book) {
  if (libooks < MAX) {
    Books[libooks] = book;
    libooks++;
  }
  // error message for invalid parameter
  else {
    std::cout << "Error: Cannot add any more elements to Library" << endl;
  }
}

// Delete last
void Library::pop_back() {
  if (!empty()) {
    libooks--;
  }
  // error message for invalid parameter
  else {
    std::cout << "Error: Cannot pop_back for empty Library" << endl;
  }
}

// Erase element at location
void Library::erase(int n) {
  if (n >= 0 && n < libooks) {
    for (int i = n; i < libooks - 1; i++) {
      Books[i] = Books[i + 1];
    }
    libooks--;
  }
  // error message for invalid parameter
  else {
    std::cout << "Error: Cannot erase element at " << n << endl;
  }
}

// Insert element at location, moves other elements as needed
void Library::insertAt(int n, const string &book) {
  // valid parameters
  if ((libooks < MAX) && (n <= libooks)) {
    if ((n >= 0) && (n <= libooks)) {
      // changing order of items if this is not going to be last item
      for (int i = libooks; i > n; i--) {
        Books[i] = Books[i - 1];
      }
      Books[n] = book;
      libooks++;
    }
  }
  // error message for invalid parameter
  else {
    std::cout << "Error: Cannot insert element at " << n << endl;
  }
}