// defines execute_commands for reading commands for library

#include "library.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

void execute_commands(const string &filename) {
  ifstream ifs(filename);
  if (!ifs.good()) {
    cout << "Failed to open " << filename << endl;
    return;
  }
  Library lib;
  while (ifs.good()) {
    string command;
    ifs >> command;
    // single word commands
    if (command == "size") {
      cout << "Executing: " << command << endl;
      cout << lib.size() << endl;
    } else if (command == "max_size") {
      cout << "Executing: " << command << endl;
      cout << lib.max_size() << endl;
    } else if (command == "empty") {
      cout << "Executing: " << command << endl;
      cout << lib.empty() << endl;
    } else if (command == "front") {
      cout << "Executing: " << command << endl;
      cout << lib.front() << endl;
    } else if (command == "back") {
      cout << "Executing: " << command << endl;
      cout << lib.back() << endl;
    } else if (command == "pop_back") {
      // no output
      cout << "Executing: " << command << endl;
      lib.pop_back();
    } else if (command == "print") {
      // call insertion operator
      cout << "Executing: " << command << endl;
      cout << lib << endl;
    } else if (command == "at") {
      int num;
      ifs >> num;
      cout << "Executing: " << command << " " << num << endl;
      cout << lib.at(num) << endl;
    } else if (command == "push_back") {
      // no output
      string book;
      // skip the space after num
      ifs.ignore();
      // read the whole line, not just up to the first space
      getline(ifs, book);
      cout << "Executing: " << command << " " << book << endl;
      lib.push_back(book);
    } else if (command == "erase") {
      // no output
      int num;
      ifs >> num;
      cout << "Executing: " << command << " " << num << endl;
      lib.erase(num);
    } else if (command == "insertAt") {
      // no output
      int num;
      string book;
      ifs >> num;
      // skip the space after num
      ifs.ignore();
      getline(ifs, book);
      cout << "Executing: " << command << " " << num << " " << book << endl;
      lib.insertAt(num, book);
    } else if (command.empty()) {
      // skip
    } else {
      cout << "Invalid command: " << command << endl;
    }
  }
  ifs.close();
}
