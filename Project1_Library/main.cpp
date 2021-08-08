
#include "library.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

// forward delaration, defined in library-commands.cpp
void execute_commands(const string &filename);

void test1() {
  Library lib;
  stringstream ss;
  // NOLINTNEXTLINE - would normally use empty
  assert(lib.size() == 0);
  assert(lib.empty());
  ss << lib;
  assert(ss.str() == "[]");
  cout << "test1 complete" << endl;
}

void test2() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  assert(lib.size() == 1);
  assert(!lib.empty());
  assert(lib.at(0) == "Ulysses");
  assert(lib.front() == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Ulysses]");
  cout << "test2 complete" << endl;
}

void test3() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  lib.push_back("Gatsby");
  assert(lib.size() == 2);
  assert(lib.at(0) == lib.front());
  assert(lib.at(1) == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Ulysses, Gatsby]");
  lib.erase(0);
  assert(lib.front() == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Gatsby]");
  cout << "test3 complete" << endl;
}

void test4() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  lib.push_back("Gatsby");
  lib.insertAt(lib.size(), "Harry Potter");
  lib.insertAt(0, "Don Quixote");
  ss << lib;
  assert(ss.str() == "[Don Quixote, Ulysses, Gatsby, Harry Potter]");
  lib.erase(1);
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Don Quixote, Gatsby, Harry Potter]");
  cout << "test4 complete" << endl;
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();
  if (argc >= 1) {
    for (int i = 1; i < argc; ++i) {
      string commandFile = argv[i];
      cout << "*** Executing commands from " << commandFile << endl;
      execute_commands(commandFile);
    }
  }
  cout << "Done." << endl;
}
