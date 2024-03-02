// ---- relay.h ----

#ifndef RELAY_H
#define RELAY_H
#include <RTClib.h>

class Relay
{
    int id;  // Relay identifire
    int pin; // Connected pin on the arduino
    // -- Timed Sprinkleing --
    int duration;   // Duration in minutes of sprinkleing
    TimeSpan start; // Start time of sprinkleing
    TimeSpan end;   // End time of sprinkleing (calcualted)

public:
    Relay();                                                                     // Constructor for arrays
    Relay(int ID, TimeSpan start = TimeSpan(0), int duration = 0, int pin = -1); // Constructor for instances
    // - Getters -
    int getID();
    int getPin();
    int getDuration();
    TimeSpan getStart();
    TimeSpan getEnd();
    // - Setters -
    void setID(int id);
    void setPin(int pinNumber);
    void setDuration(int duration);
    void setStart(TimeSpan startTime);
    void setStart(int hour, int minute);

private:
    void UpdateEnd();
};

#endif // RELAY_H