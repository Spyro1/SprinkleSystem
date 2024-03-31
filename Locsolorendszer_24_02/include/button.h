// ---- button.h ----

#ifndef BUTTON_H
#define BUTTON_H

#include "types.h"

typedef void (*ClickEvent)(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);

class TouchButton
{
    Point pos;       // Position of top left corner
    Size size;       // Size of the button
    ClickEvent func; // Function to call when button is pressed

public:
    // -- Constructors --
    TouchButton() {}
    TouchButton(int x, int y, int width, int height, ClickEvent clickevent) : pos(x, y), size(width, height), func(clickevent) {}
    TouchButton(Point position, Size size, ClickEvent clickevent) : pos(position), size(size), func(clickevent) {}
    /**
     * Tests if the given coordinate is inside the button
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(int x, int y)
    {
        return (x >= pos.x && x <= pos.x + size.width) && (y >= pos.y && y <= pos.y + size.height);
    }
    /**
     * Tests if the given coordinate is inside the button
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(Point p) { return isPressed(p.x, p.y); }
    /**
     * Activates the buttons function
     */
    void activate(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
    {
        func(tft, SD, MH);
    }
    /**
     * Combines isPressed and activate functions. If the given coordinate is inside the button, then runs the button's function.
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
     */
    bool ifPressedThenActivate(int x, int y, MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
    {
        if (isPressed(x, y))
        {
            activate(tft, SD, MH);
            return true;
        }
        return false;
    }
    /**
     * Combines isPressed and activate functions. If the given coordinate is inside the button, then runs the button's function.
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
     */
    bool ifPressedThenActivate(Point p, MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH) { return ifPressedThenActivate(p.x, p.y, tft, SD, MH); }
    TouchButton &operator=(TouchButton &&TB)
    {
        if (this != &TB)
        {
            pos = TB.pos;
            size = TB.size;
            func = TB.func;
        }
        return *this;
    }
};

#endif