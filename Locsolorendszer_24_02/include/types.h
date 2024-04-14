// ---- types.h ----

#ifndef TYPES_H
#define TYPES_H
#include "realay.h"

// DEBUG macro
#define DEBUG 1
#if DEBUG == 1
#define debug(str) Serial.print(F(str))
#define debugv(V) Serial.print(V)
#define debugln(str) Serial.println(F(str))
#define debugvln(V) Serial.println(V)
#else
#define debug(str)
#define debugv(V)
#define debugln(str)
#define debugvln(V)
#endif

#define PERIOD_COUNT 3
#define RELAY_COUNT 16
// Relay Pins: 22,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51

class Point
{
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point(const Point &p)
    {
        x = p.x;
        y = p.y;
    }
    bool operator==(const Point &p) { return x == p.x && y == p.y; }
    bool operator!=(const Point &p) { return x != p.x || y != p.y; }
    Point &operator=(const Point &p)
    {
        if (this != &p)
        {
            x = p.x;
            y = p.y;
        }
        return *this;
    }
};
struct Size
{
    int width, height;
    Size(int width = 0, int height = 0) : width(width), height(height) {}
};

enum menuStates
{
    mainMenu,
    subPeriodsChoser,
    subChoseRelay,
    subTimingRelay,
    subAutomaticTiming,
    subRealTimeSetting,
    subChainSprinkle,
    subTesting,
    subHumiditySetting,
    subSettingsMenu
};
enum menuStyle
{
    quality,
    medium,
    easy,
};
struct Period
{
    bool isActive;             // !EEPROM!
    Relay realys[RELAY_COUNT]; // !EEPROM!
};

class menuHandeler
{
public:
    // ---- Menu Variables ----
    // -- Save config vars --
    menuStyle style;              // !EEPROM! How beautiful the menu should be
    bool mainSwitch;              // !EEPROM! If true, then timing is processed, if false, then no automatic sprinkleing
    uint16_t humiditySensitivity; // !EEPROM! Humidity sensitivity of the system
    Period periods[PERIOD_COUNT]; // !EEPROM! Time periods when automatic sprinkeling can happen

    // -- Running config vars --
    menuStates State;            // Current state of menusystem
    unsigned char page;          // Current page of submenu
    unsigned char currentPeriod; // Which period is edited currently
    unsigned char currentRelay;  // Which realy is edited currently
    Period temporalPeriod;
    TimeSpan temporalStart;
    uint8_t temporalDuration;

    menuHandeler()
    {
        style = quality;
        mainSwitch = false;
        humiditySensitivity = 0;

        temporalStart = TimeSpan(0);
        temporalDuration = 0;
        Reset();
    }
    void Reset()
    {
        State = mainMenu;
        page = 1;
        currentPeriod = 0;
        currentRelay = 0;
    }
    void UpdateRelays(TimeSpan currentTime)
    {
        for (int p = 0; p < PERIOD_COUNT; p++)
        {
            for (int r = 0; r < RELAY_COUNT; r++)
            {
                bool toActivate = currentTime.totalseconds() >= periods[p].realys[r].getStart().totalseconds() && currentTime.totalseconds() < periods[p].realys[r].getEnd().totalseconds();
                periods[p].realys[r].SetRelayState(toActivate);
                if (toActivate)
                {
                    debugv(p);
                    debug("/");
                    debugv(r);
                    debug("realy Activated");
                }
            }
        }
    }
    Relay &getCurrentRelay()
    {
        return periods[currentPeriod].realys[currentRelay];
    }
    void ChangeTempStartHour(uint8_t byValue)
    {
        temporalStart = temporalStart + TimeSpan(3600 * byValue);
    }
    void ChangeTempStartMinute(uint8_t byValue)
    {
        temporalStart = temporalStart + TimeSpan(60 * byValue);
    }
    void ChangeTempduration(uint8_t byValue)
    {
        temporalDuration += byValue;
    }
};

#endif