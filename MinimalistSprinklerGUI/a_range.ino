// ******** range.ino ********

// template<int lowerLimit, int upperLimit>
// class Range{
// public:
//   int value;
//   Range(int value_ = 0) : value(value_) {}

//   int& operator()() { return value; }
//   void Increment(const int byValue) { value = (value + byValue >= upperLimit) ? lowerLimit + upperLimit - (value + byValue) : value + byValue; }
//   void Decrement(const int byValue) { value = (value + byValue <= lowerLimit) ? upperLimit - lowerLimit - (value + byValue) : value + byValue; }
// };