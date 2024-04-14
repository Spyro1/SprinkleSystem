// ---- relay.h ----

#ifndef RELAY_H
#define RELAY_H
#include <RTClib.h>

class Relay
{
    static uint8_t idCounter;
    uint8_t id;  // Relay identifire
    uint8_t pin; // Connected pin on the arduino
    // -- Timed Sprinkleing --
    uint8_t duration; // Duration in minutes of sprinkleing
    TimeSpan start;   // Start time of sprinkleing
    TimeSpan end;     // End time of sprinkleing (calcualted)

public:
    // -- Constrcutors --
    /**
     *  Constructor for arrays
     * */
    Relay();
    /**
     *  Constructor for instances
     * @param ID Relays identifier
     * @param start Start time of automated sprinkling
     * @param duration Duration of the sprinkleing in minutes
     * @param pin Pin of the relay on board
     * */
    Relay(uint8_t ID, TimeSpan start = TimeSpan(0), uint8_t duration = 0, uint8_t pin = -1);
    // - Getters -
    uint8_t getID() const;
    uint8_t getPin() const;
    uint8_t getDuration() const;
    TimeSpan getStart() const;
    TimeSpan getEnd() const;
    // - Setters -
    void setID(uint8_t id);
    void setPin(uint8_t pinNumber);
    void setDuration(uint8_t duration);
    void setStart(TimeSpan startTime);
    void setStart(int8_t hour, int8_t minute);
    // - Functions -
    void SetRelayState(bool value);
    void ChangeStartHour(uint8_t byValue);
    void ChangeDuration(uint8_t byValue);
    void ChangeStartMinute(uint8_t byValue);

private:
    void UpdateEnd();
};

#endif // RELAY_H