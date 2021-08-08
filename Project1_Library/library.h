/**
 * Library class
 * Books are represented as string objects
 * Can add and remove books, print library
 * 
 * Calling a function with invalid parameters causes undefined behavior.
 * For our puporposes, if a function has been called with invalid parameters
 * and needs to return a value, the first element in the library is returned.
 **/

#ifndef LIBRARY_H
#define LIBRARY_H

#include <ostream>
#include <string>

using namespace std;

class Library {
public:
  // constructor
  Library();

  // Return size
  int size() const;

  // Return maximum size
  int max_size() const;

  // Test whether Library is empty
  bool empty() const;

  // Access element
  const string &at(int n) const;

  // Access first element
  const string &front() const;

  // Access last element (public member function )
  const string &back() const;

  // Add element at the end
  void push_back(const string &book);

  // Delete last
  void pop_back();

  // Erase element at location, moves other elements as needed
  void erase(int n);

  // Insert element at location, moves other elements as needed
  void insertAt(int n, const string &book);

private:
  // maximum number of books
  static const int MAX = 10;
  int libooks{0};
  string error="Dummy";
  // books in library
  string Books[MAX];
};

// insertion operator, so we can use "cout << lib"
ostream &operator<<(ostream &out, const Library &lib);

#endif // LIBRARY_H
