// ******** time.ino ********

/**
 * @brief Represents a time with hours and minutes.
 */
struct Time {
  Range24 hour;   /**< The hour component of the time. */
  Range60 minute; /**< The minute component of the time. */

  /**
   * @brief Constructor to initialize the time. 
   * @param h The initial hour. Defaults to 0.
   * @param m The initial minute. Defaults to 0.
   */
  Time(int h = 0, int m = 0) { hour = Range24(h); minute = Range60(m); }
  /**
   * @brief Get the current hour. 
   * @return The current hour value.
   */
  int hours() const { return hour.getValue(); }
  /**
   * @brief Get the current minute. 
   * @return The current minute value.
   */
  int minutes() const { return minute.getValue(); }
  /**
   * @brief Adds a number of minutes to the current time, adjusting the hour and minute accordingly.
   * @param plusMin The number of minutes to add.
   * @return A reference to the updated Time object.
   */
  Time& operator+=(int plusMin) {
    if (minute.getValue() + plusMin > Range60::maxLimit) 
      hour += (minute.getValue() + plusMin) / Range60::range;
    minute += plusMin;
    return *this;
  }
  /**
   * @brief Subtracts a number of minutes from the current time, adjusting the hour and minute accordingly.
   * @param subMin The number of minutes to subtract.
   * @return A reference to the updated Time object.
   */
  Time& operator-=(int subMin) {
    if (minute.getValue() - subMin <= Range60::minLimit) 
      hour -= (minute.getValue() - subMin) / Range60::range;
    minute -= subMin;
    return *this;
  }
  /**
   * @brief Adds a number of minutes to the current time, adjusting the hour and minute accordingly, and returns a new Time object.
   * @param plusMin The number of minutes to add.
   * @return A new Time object with the updated time.
   */
  Time operator+(int plusMin) {
    Time t(hours(), minutes());
    if (t.minutes() + plusMin > Range60::maxLimit) 
      t.hour += (t.minutes() + plusMin) / Range60::range;
    t.minute += plusMin;
    return t;
  }
  /**
   * @brief Subtracts a number of minutes from the current time, adjusting the hour and minute accordingly, and returns a new Time object. 
   * @param subMin The number of minutes to subtract.
   * @return A new Time object with the updated time.
   */
  Time operator-(int subMin) {
    Time t(hours(), minutes());
    if (t.minutes() - subMin <= Range60::minLimit) 
        t.hour -= (t.minutes() - subMin) / Range60::range;
    t.minute -= subMin;
    return t;
  }
};