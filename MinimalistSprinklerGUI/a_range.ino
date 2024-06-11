// ******** range.ino ********

template<int lowerLimit, int upperLimit>
class RangeInt {
    int value;
public:
     static const int minLimit = lowerLimit;
     static const int maxLimit = lowerLimit;
     static const int range = upperLimit - lowerLimit + 1;
    // Constructor to initialize the range and the initial value
    RangeInt(int value = 0) { setValue(value); }

    // Setter to assign value with range constraints
    void setValue(int val) {
        if (lowerLimit > upperLimit) { debugln("Min value must be less than or equal to upperLimit value."); }
        int rangeSize = upperLimit - lowerLimit + 1;
        if (rangeSize <= 0) { debugln("Invalid range size."); }
        val = (val - lowerLimit) % rangeSize;
        if (val < 0) { val += rangeSize; }
        this->value = val + lowerLimit;
    }
    // Getter to get the current value
    int getValue() const {
        return value;
    }
    int operator()() const{
        return value;
    }
    // Overloading the assignment operator
    RangeInt& operator=(int value) {
        setValue(value);
        return *this;
    }
    // Overloading the addition assignment operator
    RangeInt& operator+=(int increment) {
        setValue(value + increment);
        return *this;
    }
    // Overloading the subtraction assignment operator
    RangeInt& operator-=(int decrement) {
        setValue(value - decrement);
        return *this;
    }
    // Overloading the prefix increment operator
    RangeInt& operator++() {
        setValue(value + 1);
        return *this;
    }
    // Overloading the postfix increment operator
    RangeInt operator++(int) {
        RangeInt temp = *this;
        setValue(value + 1);
        return temp;
    }
    // Overloading the prefix decrement operator
    RangeInt& operator--() {
        setValue(value - 1);
        return *this;
    }
    // Overloading the postfix decrement operator
    RangeInt operator--(int) {
        RangeInt temp = *this;
        setValue(value - 1);
        return temp;
    }
};

struct Range1024 : RangeInt<0,1023>{
    Range1024(int value = 0) : RangeInt<0,1023>(value) {}
};
struct Range60 : RangeInt<0,59>{
    Range60(int value = 0) : RangeInt<0,59>(value) {}
};
struct Range24 : RangeInt<0,23>{
    Range24(int value = 0) : RangeInt<0,23>(value) {}
};