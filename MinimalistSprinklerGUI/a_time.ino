// ******** time.ino ********

struct Time {
  Range24 hour;
  Range60 minute;

  Time(int h = 0, int m = 0) : hour(h % 60), minute(m % 60) {}

  int hours() const { return hour.getValue(); }
  int minutes() const { return minute.getValue(); }

  Time& operator+=(int plusMin) {
    if (minute.getValue() + plusMin > Range60::maxLimit) hour += plusMin / Range60::range;
    minute += plusMin;
    return *this;
  }
  Time& operator-=(int subMin) {
    if (minute.getValue() - subMin <= Range60::minLimit) hour -= subMin / Range60::range;
    minute -= subMin;
    return *this;
  }  
  Time operator+(int plusMin) {
    Time t(*this);
    if (t.minute.getValue() + plusMin > Range60::maxLimit) t.hour += plusMin / Range60::range;
    t.minute += plusMin;
    return t;
  }
  Time operator-(int subMin) {
    Time t(*this);
    if (t.minute.getValue() - subMin <= Range60::minLimit) t.hour -= subMin / Range60::range;
    t.minute -= subMin;
    return t;
  }
};