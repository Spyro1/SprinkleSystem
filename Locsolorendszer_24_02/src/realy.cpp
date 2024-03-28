// ---- relay.cpp ----

#include "realay.h"
/* ---- Relay calss function definicions ---- */
/* -- Constructors -- */

Relay::Relay()
{
    id = 0;
    start = TimeSpan(0);
    end = TimeSpan(0);
    duration = 0;
    pin = -1;
}
Relay::Relay(int ID, TimeSpan start, int duration, int pin)
{
    id = ID;
    this->start = start;
    this->duration = duration;
    this->pin = pin;
    UpdateEnd();
}

/* -- Getters -- */

int Relay::getID() const { return id; }
int Relay::getPin() const { return pin; }
int Relay::getDuration() const { return duration; }
TimeSpan Relay::getStart() const { return start; }
TimeSpan Relay::getEnd() const { return end; }

/* -- Setters -- */

void Relay::setID(int id) { this->id = id; }
void Relay::setPin(int pin) { this->pin = pin; }
void Relay::setDuration(int duration)
{
    this->duration = duration;
    UpdateEnd();
}
void Relay::setStart(TimeSpan startTime)
{
    this->start = TimeSpan(startTime);
    UpdateEnd();
}
void Relay::setStart(int hour, int minute)
{
    this->start = TimeSpan(0, hour, minute, 0);
    UpdateEnd();
}
void Relay::UpdateEnd()
{
    end = start + duration * 60; // Convert duration from inutes to seconds
}
