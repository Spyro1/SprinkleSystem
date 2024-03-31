// ---- types.h ----

#ifndef TYPES_H
#define TYPES_H

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