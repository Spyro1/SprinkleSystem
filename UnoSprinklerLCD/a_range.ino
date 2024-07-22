// ******** range.ino ********

/**
 * @brief Template class for an integer range with wrap-around behavior.
 * 
 * The RangeInt class template allows for the creation of integer values that are constrained within a specified range.
 * When values are set or modified, they are automatically wrapped around within the range limits.
 * 
 * @tparam lowerLimit The lower limit of the range.
 * @tparam upperLimit The upper limit of the range.
 */
template <int lowerLimit, int upperLimit>
class RangeInt {

  int value; /**< The current value within the specified range. */

public:
  static const int minLimit = lowerLimit;               /**< The minimum limit of the range. */
  static const int maxLimit = upperLimit;               /**< The maximum limit of the range. */
  static const int range = upperLimit - lowerLimit + 1; /**< The size of the range. */

  /**
    * @brief Constructor to initialize the range and the initial value.
    * @param value The initial value to set. Defaults to 0.
    */
  RangeInt(int value = 0) { setValue(value); }

  /**
    * @brief Setter to assign value with range constraints.
    * This function sets the value within the specified range, wrapping around if necessary.
    * @param val The value to set.
    */
  void setValue(int val) {
    if (lowerLimit > upperLimit) { debugln("Min value must be less than or equal to upperLimit value."); }
    int rangeSize = upperLimit - lowerLimit + 1;
    if (rangeSize <= 0) { debugln("Invalid range size."); }
    val = (val - lowerLimit) % rangeSize;
    if (val < 0) { val += rangeSize; }
    this->value = val + lowerLimit;
  }
  /**
    * @brief Getter to get the current value.
    * @return The current value within the range.
    */
  int getValue() const { return value; }
  /**
    * @brief Function call operator to get the current value.
    * @return The current value within the range.
    */
  int operator()() const { return value; }
  /**
    * @brief Assigns a new value to the range, applying range constraints.
    * @param val The value to assign.
    * @return A reference to the updated RangeInt object.
    */
  RangeInt &operator=(int val) {
    setValue(val);
    return *this;
  }
  /**
    * @brief Adds an increment to the current value, applying range constraints. 
    * @param increment The value to add.
    * @return A reference to the updated RangeInt object.
    */
  RangeInt &operator+=(int increment) {
    setValue(value + increment);
    return *this;
  }
  /**
    * @brief Subtracts a decrement from the current value, applying range constraints.
    * @param decrement The value to subtract.
    * @return A reference to the updated RangeInt object.
    */
  RangeInt &operator-=(int decrement) {
    setValue(value - decrement);
    return *this;
  }
  /**
    * @brief Increments the current value by 1, applying range constraints.
    * @return A reference to the updated RangeInt object.
    */
  RangeInt &operator++() {
    setValue(value + 1);
    return *this;
  }
  /**
    * @brief Increments the current value by 1, applying range constraints, and returns the previous value.
    * @return A RangeInt object with the previous value.
    */
  RangeInt operator++(int) {
    RangeInt temp = *this;
    setValue(value + 1);
    return temp;
  }
  /**
    * @brief Decrements the current value by 1, applying range constraints.
    * @return A reference to the updated RangeInt object.
    */
  RangeInt &operator--() {
    setValue(value - 1);
    return *this;
  }
  /**
    * @brief Decrements the current value by 1, applying range constraints, and returns the previous value.
    * @return A RangeInt object with the previous value.
    */
  RangeInt operator--(int) {
    RangeInt temp = *this;
    setValue(value - 1);
    return temp;
  }
};

/**
 * @brief A specialization of RangeInt for values in the range 0 to 59.
 */
struct Range60 : RangeInt<0, 59> {
  /**
    * @brief Constructor to initialize the range with an optional initial value.
    * @param value The initial value to set. Defaults to 0.
    */
  Range60(int value = 0) : RangeInt<0, 59>(value) {}
};

/**
 * @brief A specialization of RangeInt for values in the range 0 to 23.
 */
struct Range24 : RangeInt<0, 23> {
  /**
    * @brief Constructor to initialize the range with an optional initial value.
    * @param value The initial value to set. Defaults to 0.
    */
  Range24(int value = 0) : RangeInt<0, 23>(value) {}
};