//
// Created by Yusuf Pisan on 4/2/18.
//

#include "timespan.h"

ostream &operator<<(ostream &out, const TimeSpan &ts) {
  if (!ts.isPositive() && (ts.h == 0)) {
    // adding a '-' if hour equal zero and timespan is not positive
    out << "-";
  }
  if ((ts.m < 10) && (ts.m > (-1))) {
    // for 0 to 10 adding extra 0 before minute digit
    out << ts.h << ":0" << abs(ts.m);
  } else {
    out << ts.h << ":" << abs(ts.m);
  }
  if ((ts.sec < 10) && (ts.sec > (-1))) {
    // for 0 to 10 adding extra 0 before second digit
    out << ":0" << abs(ts.sec);
  } else {
    out << ":" << abs(ts.sec);
  }
  return out;
}

// explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
TimeSpan::TimeSpan(double hour, double minute, double second) {
  totalsec = int((abs(hour) * 3600 + minute * 60 + second));
  // total seconds for object
  h = int(totalsec / 3600);
  // hours
  m = int((totalsec - h * 3600) / 60);
  // minutes
  sec = int(totalsec - h * 3600 - m * 60);
  // seconds
  if (hour < 0) {
    // if parameter hour < 0 making it negative
    h = -h;
  }
}

// hour component
double TimeSpan::getHour() const { return h; } // return hours

// minute component
double TimeSpan::getMinute() const { return m; } // return minutes

// second component
double TimeSpan::getSecond() const { return sec; } // return seconds

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const {
  return (totalsec > 0);
} // return bool value to check if object positive

// add
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {
  TimeSpan tsSum;
  tsSum.totalsec = (this->totalsec) + ts.totalsec;
  tsSum.h = int(tsSum.totalsec / 3600);
  tsSum.m = int((tsSum.totalsec - tsSum.h * 3600) / 60);
  tsSum.sec = tsSum.totalsec - tsSum.h * 3600 - tsSum.m * 60;
  tsSum.m = abs(tsSum.m);
  tsSum.sec = abs(tsSum.sec);
  return tsSum;
}

// add equal
TimeSpan &TimeSpan::operator+=(const TimeSpan &ts) {
  this->totalsec = this->totalsec + ts.totalsec;
  this->h = int(this->totalsec / 3600);
  this->m = int((this->totalsec - this->h * 3600) / 60);
  this->sec = this->totalsec - this->h * 3600 - this->m * 60;
  // making minutes positive for using == and != properly
  this->m = abs(this->m);
  // making seconds positive for using == and != properly
  this->sec = abs(this->sec);
  return *this;
}

// subtract equal
TimeSpan &TimeSpan::operator-=(const TimeSpan &ts) {
  this->totalsec = this->totalsec - ts.totalsec;
  this->h = int(this->totalsec / 3600);
  this->m = int((this->totalsec - this->h * 3600) / 60);
  this->sec = this->totalsec - this->h * 3600 - this->m * 60;
  // making minutes positive for using == and != properly
  this->m = abs(this->m);
  // making seconds positive for using == and != properly
  this->sec = abs(this->sec);
  return *this;
}

// subtract
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan tsSub;
  tsSub.totalsec = this->totalsec - ts.totalsec;
  tsSub.h = int(tsSub.totalsec / 3600);
  tsSub.m = int((tsSub.totalsec - tsSub.h * 3600) / 60);
  tsSub.sec = tsSub.totalsec - tsSub.h * 3600 - tsSub.m * 60;
  // making minutes positive for using == and != properly
  tsSub.m = abs(tsSub.m);
  // making seconds positive for using == and != properly
  tsSub.sec = abs(tsSub.sec);
  return tsSub;
}

// multiply with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const {
  TimeSpan tsLarge;
  tsLarge.totalsec = (this->totalsec) * number;
  tsLarge.h = int(tsLarge.totalsec / 3600);
  tsLarge.m = int((tsLarge.totalsec - tsLarge.h * 3600) / 60);
  tsLarge.sec = tsLarge.totalsec - tsLarge.h * 3600 - tsLarge.m * 60;
  // making minutes positive for using == and != properly
  tsLarge.m = abs(tsLarge.m);
  // making seconds positive for using == and != properly
  tsLarge.sec = abs(tsLarge.sec);
  return tsLarge;
}

// equality ==
bool TimeSpan::operator==(const TimeSpan &ts) const {
  return ((this->getHour() == ts.getHour()) &&
          (this->getMinute() == ts.getMinute()) &&
          (this->getSecond() == ts.getSecond()));
}

// less
bool TimeSpan::operator<(const TimeSpan &ts) const {
  return (this->totalsec < ts.totalsec);
}

// less or equal
bool TimeSpan::operator<=(const TimeSpan &ts) const {
  return (this->totalsec <= ts.totalsec);
}

// more
bool TimeSpan::operator>(const TimeSpan &ts) const {
  return (this->totalsec > ts.totalsec);
}

// more or equal
bool TimeSpan::operator>=(const TimeSpan &ts) const {
  return (this->totalsec >= ts.totalsec);
}

// inequality !=
bool TimeSpan::operator!=(const TimeSpan &ts) const {
  return !((this->getHour() == ts.getHour()) &&
           (this->getMinute() == ts.getMinute()) &&
           (this->getSecond() == ts.getSecond()));
}
