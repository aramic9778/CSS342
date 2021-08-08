//
// Created by Yusuf Pisan on 4/2/18.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // add
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;
  
  TimeSpan& operator+=(const TimeSpan &ts);

  TimeSpan& operator-=(const TimeSpan &ts);

  bool operator<(const TimeSpan &ts) const;

  bool operator>(const TimeSpan &ts) const;
  
  bool operator>=(const TimeSpan &ts) const;

  bool operator<=(const TimeSpan &ts) const;

  
  

  // TODO(student)
  // to add operator+=, operator-=, operator<, operator>, operator<=, operator>=

  // hour component of timespan
  double getHour() const;

  // minute component of timespan
  double getMinute() const;

  // second component of timespan
  double getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

private: // private variables which we will use in timespan.cpp

double h;
double m;
double sec;
int totalsec;
};

#endif // ASS2_TIMESPAN_H
