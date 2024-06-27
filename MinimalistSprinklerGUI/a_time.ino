// ******** time.ino ********

struct Time {
  Range24 hour;
  Range60 minute;

  Time(int h = 0, int m = 0) { hour = Range24(h); minute = Range60(m); }

  int hours() const { return hour.getValue(); }
  int minutes() const { return minute.getValue(); }

  Time& operator+=(int plusMin) {
    if (minute.getValue() + plusMin > Range60::maxLimit) hour += (minute.getValue() + plusMin) / Range60::range;
    minute += plusMin;
    return *this;
  }
  Time& operator-=(int subMin) {
    if (minute.getValue() - subMin <= Range60::minLimit) hour -= (minute.getValue() - subMin) / Range60::range;
    minute -= subMin;
    return *this;
  }
  Time operator+(int plusMin) {
    Time t(hours(), minutes());
    if (t.minutes() + plusMin > Range60::maxLimit) t.hour += (t.minutes() + plusMin) / Range60::range;
    t.minute += plusMin;
    return t;
  }
  Time operator-(int subMin) {
    Time t(hours(), minutes());
    if (t.minutes() - subMin <= Range60::minLimit) t.hour -= (t.minutes() - subMin) / Range60::range;
    t.minute -= subMin;
    return t;
  }
};