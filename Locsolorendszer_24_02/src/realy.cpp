// ---- relay.cpp ----

#include "realay.h"
/* ---- Relay calss function definicions ---- */

uint8_t Relay::idCounter = 0;
/* -- Constructors -- */

Relay::Relay()
{
    id = idCounter++;
    start = TimeSpan(0);
    end = TimeSpan(0);
    duration = 0;
    pin = -1;
}
Relay::Relay(uint8_t ID, TimeSpan start, uint8_t duration, uint8_t pin)
{
    id = ID;
    this->start = start;
    this->duration = duration;
    this->pin = pin;
    UpdateEnd();
}

/* -- Getters -- */

uint8_t Relay::getID() const { return id; }
uint8_t Relay::getPin() const { return pin; }
uint8_t Relay::getDuration() const { return duration; }
TimeSpan Relay::getStart() const { return start; }
TimeSpan Relay::getEnd() const { return end; }

/* -- Setters -- */

void Relay::setID(uint8_t id) { this->id = id; }
void Relay::setPin(uint8_t pin) { this->pin = pin; }
void Relay::setDuration(uint8_t duration)
{
    this->duration = duration;
    UpdateEnd();
}
void Relay::setStart(TimeSpan startTime)
{
    this->start = TimeSpan(startTime);
    UpdateEnd();
}
void Relay::setStart(int8_t hour, int8_t minute)
{
    this->start = TimeSpan(0, hour, minute, 0);
    UpdateEnd();
}
void Relay::UpdateEnd()
{
    end = start + duration * 60; // Convert duration from inutes to seconds
}

/* -- Functions -- */
void Relay::SetRelayState(bool value)
{
    if (value)
        digitalWrite(pin, HIGH);
    else
        digitalWrite(pin, LOW);
}
void Relay::ChangeStartHour(uint8_t byValue)
{
    start = start + TimeSpan(byValue * 3600);
    UpdateEnd();
}
void Relay::ChangeStartMinute(uint8_t byValue)
{
    start = start + TimeSpan(byValue * 60);
    UpdateEnd();
}
void Relay::ChangeDuration(uint8_t byValue)
{
    duration += byValue;
    UpdateEnd();
}
