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

struct Period
{
    bool isActive;
    Relay realys[RELAY_COUNT];
};

struct menuHandeler
{
    // ---- Menu Variables ----
    menuStates State;             // Current state of menusystem
    bool mainSwitch;              // If true, then timing is processed, if false, then no automatic sprinkleing
    unsigned char page;           // Current page of submenu
    Period periods[PERIOD_COUNT]; // Time periods when automatic sprinkeling can happen

    menuHandeler()
    {
        State = mainMenu;
        mainSwitch = false;
        page = 0;
    }
    void Reset()
    {
        State = mainMenu;
        page = 0;
    }
};

#endif