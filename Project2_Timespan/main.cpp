#include <cassert>
#include <iostream>
#include <sstream>

#include "timespan.h"

using namespace std;

// testing constructor
void test1() {
  TimeSpan ts(1, 20, 30);
  stringstream ss;
  ss << ts;
  assert(ss.str() == "1:20:30");

  TimeSpan ts2(4, -20, -90);
  ss.str("");
  ss << ts2;
  assert(ss.str() == "3:38:30");

  TimeSpan ts3(1.5, 30.5, -90);
  ss.str("");
  ss << ts3;
  assert(ss.str() == "1:59:00");

  TimeSpan ts4(0, 0.07, 0);
  ss.str("");
  ss << ts4;
  assert(ss.str() == "0:00:04");
  cout << "test1 complete" << endl;
}

// testing equality, addition, subtraction, multiplication
void test2() {
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  TimeSpan ts4(2, 40, 15);
  TimeSpan ts5(2, 40, 15);
  TimeSpan ts7(-1, 19, 45); // ts7 for negative subtract
  TimeSpan tss;
  tss = ts2 - ts4;
  assert((ts2 - ts4) == ts7); // new test
  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  assert((ts + ts + ts) == (ts2 * 3));
  assert((ts * 5) == (ts2 * 4) + ts2);
  assert((ts * 5) == (ts2 * 6) - ts2);
  assert((ts + ts - ts) == ((ts2 * 2) - ts));
  assert((ts - ts2) == ts3);
  assert((ts3 * 5) == ts3);
  cout << "test2 complete" << endl;
}

void test3() {
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;
  assert(ts1.isPositive() && !ts2.isPositive());
  stringstream ss;
  ss << ts2;
  assert(ss.str() == "-0:00:10");
  cout << "test3 complete" << endl;
}

void test4() { // new tests for > < >= <= += and -= operators
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(3, 5, 7);
  TimeSpan tss;
  TimeSpan ts4(2, 41, 0);
  TimeSpan ts5(4, 25, 37);
  TimeSpan ts6(1, 44, 37);
  TimeSpan ts7(-1, 44, 37);
  assert(!(ts < ts2));
  assert(ts <= ts2);
  assert(ts < ts3);
  assert(ts <= ts3);
  assert(!(ts > ts3));
  assert(ts >= ts2);
  ts += ts2;
  assert(ts == ts4);
  ts5 -= ts4;
  assert(ts5 == ts6);
  ts2 -= ts3;
  assert(ts2 == ts7);
  cout << "test4 complete" << endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  cout << "Done." << std::endl;
  return 0;
}