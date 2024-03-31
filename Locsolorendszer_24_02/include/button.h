// ---- button.h ----

#ifndef BUTTON_H
#define BUTTON_H

#include "types.h"

typedef void (*ClickEvent)(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);

class TouchButton
{
    Point pos;          // Position of top left corner
    Size size;          // Size of the button
    ClickEvent func;    // Function to call when button is pressed
    MCUFRIEND_kbv &tft; // TFT Display reference
    SdFat &SD;          // SD card reference
    menuHandeler &MH;   // Menu Handeling struct for menu fields

public:
    // -- Constructors --
    TouchButton() : tft(*(MCUFRIEND_kbv *)0), SD(*(SdFat *)0), MH(*(menuHandeler *)0) {}
    TouchButton(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH, int x, int y, int width, int height, ClickEvent clickevent) : pos(x, y), size(width, height), func(clickevent), tft(tft), SD(SD), MH(MH) {}
    TouchButton(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH, Point position, Size size, ClickEvent clickevent) : pos(position), size(size), func(clickevent), tft(tft), SD(SD), MH(MH) {}
    /**
     * Tests if the given coordinate is inside the button
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(int x, int y)
    {
        debug("Tested");
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
    void activate()
    {
        debug(" Activated ");
        func(tft, SD, MH);
    }
    /**
     * Combines isPressed and activate functions. If the given coordinate is inside the button, then runs the button's function.
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
     */
    bool ifPressedThenActivate(int x, int y)
    {
        if (isPressed(x, y))
        {
            activate();
            return true;
        }
        return false;
    }
    /**
     * Combines isPressed and activate functions. If the given coordinate is inside the button, then runs the button's function.
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
     */
    bool ifPressedThenActivate(Point p) { return ifPressedThenActivate(p.x, p.y); }
    TouchButton &operator=(TouchButton &&TB)
    {
        if (this != &TB)
        {
            pos = TB.pos;
            size = TB.size;
            func = TB.func;
            tft = TB.tft;
            // SD = TB.SD;
            MH = TB.MH;
        }
        return *this;
    }
};

#endif