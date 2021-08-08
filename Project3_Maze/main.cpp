#include <iostream>

#include "maze.h"

using namespace std;

void test(const string &mazeFile) {
  Maze m;
  cout << "*** Solving " << mazeFile << endl;
  if (!m.load(mazeFile)) {
    cerr << "Failed to load " << mazeFile << endl;
    return;
  }
  if (m.solve()) {
    cout << "Path: " << m.getPath() << endl;
  } else {
    cout << "Failed to solve: " << mazeFile << endl;
  }
  cout << m << endl;
}

// accepts multiple maze files from command line
// ./a.out maze0.txt maze1.txt maze2.txt maze3.txt badfile.txt
int main(int argc, char *argv[]) {
  if (argc >= 1) {
    for (int i = 1; i < argc; ++i) {
      string mazeFile = argv[i];
      test(mazeFile);
    }
  }
  cout << "Done!" << endl;
  return 0;
}