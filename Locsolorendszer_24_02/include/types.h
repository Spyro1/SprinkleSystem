// ---- types.h ----

#ifndef TYPES_H
#define TYPES_H

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

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
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

struct menuHandeler
{
    // ---- Menu Variables ----
    menuStates State;
    bool mainSwitch; // If true, then timing is processed, if false, then no automatic sprinkleing

    menuHandeler()
    {
        State = mainMenu;
        mainSwitch = false;
    }
};
#endif