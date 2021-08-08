//
// Created by Yusuf Pisan on 4/18/18.
//

#include "maze.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// print maze object
ostream &operator<<(ostream &out, const Maze &maze) {
  for (int row = 0; row < maze.height; ++row) {
    for (int col = 0; col < maze.width; ++col) {
      out << maze.field[row][col];
    }
    out << endl;
  }
  out << endl;
  return out;
}

// default constructor
Maze::Maze() = default;

// Load maze file from current directory
bool Maze::load(const string &fileName) {
  ifstream inFile;
  inFile.open(fileName);
  if (!inFile) {
    cerr << "Unable to open file: " << fileName << endl;
    return false;
  }
  inFile >> width >> height;
  inFile >> exitRow >> exitColumn;
  inFile >> startRow >> startColumn;
  // ignore leftover charcaters up to newline
  inFile.ignore(INT_MAX, '\n');
  string line;
  for (int row = 0; row < height; ++row) {
    getline(inFile, line);
    field.push_back(line);
  }
  return true;
}

bool Maze::step(int row, int col,
                string p) { // additional step function which take row, column
                            // and string variable that will be updated for path
  if (!isInside(row, col)) { // don't step if we are not inside the maze
    return false;
  }
  if (!isClear(row, col)) { // don't step if path is not clear
    return false;
  }
  if (atExit(row, col)) { // if we are at the exit location
    markAsPath(row, col); // mark as visited last location
    path = std::move(p);  // I had a warning for "path = p" and std::move()
                          // was a solution to get rid of it
    return true;
  }
  markAsVisited(row, col); // mark location as visited for other cases
  if (step(row, col + 1, p + "E") || step(row, col - 1, p + "W") ||
      step(row + 1, col, p + "S") ||
      step(row - 1, col,
           p + "N")) { // step in one of ways and add it in 'p' string value
    markAsPath(row, col);
    return true;
  }
  return false;
}

// // true if maze can be solved
bool Maze::solve() {
  return step(startRow, startColumn, "");
} // get all steps done and
  // return either solved or not

// path to exit
string Maze::getPath() const { return path; }

// true if row, column is the exit
bool Maze::atExit(int row, int column) const {
  return row == exitRow && column == exitColumn;
}

// true if row, column is inside the maze
bool Maze::isInside(int row, int col) const {
  return row >= 0 && col >= 0 && row < field.size() && col < field[row].size();
}

// true if row, column is clear to move
bool Maze::isClear(int row, int col) const {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  return field[row][col] == CLEAR;
}

// mark location as part of the path to exit
void Maze::markAsPath(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = PATH;
}

// mark location as visited, not part of the path to exit
void Maze::markAsVisited(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = VISITED;
}
