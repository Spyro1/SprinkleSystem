// ---- button.h ----

#ifndef BUTTON_H
#define BUTTON_H

#include "Point.h"

class TouchButton{
    char name[20];
    Point pos; // Position of top left corner
    Size size; // Size of the button
    void (*func)();
public:
    TouchButton() { func = nullptr; }
    TouchButton(int x, int y, int width, int height, void (*clickevent)()) : pos(x,y), size(width, height), func(clickevent) {}
    TouchButton(Point position, Size size, void (*clickevent)()) : pos(position), size(size), func(clickevent) {}
    /**
     * Tests if the given coordinate is inside the button
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
    */
    bool isPressed(int x, int y) {
        return(x >= pos.x && x <= pos.x + size.width ) && (y >= pos.y && y <= pos.y + size.height);
    }
    /**
     * Tests if the given coordinate is inside the button
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
    */
    bool isPressed(Point p) {
         return isPressed(p.x, p.y); 
    }
    /**
     * Activates the buttons function
    */
    void activate(){
        func();
    }
    /**
     * Combines isPressed and activate functions. If the given coordinate is inside the button, then runs the button's function.
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
    */
    bool ifPressedThenActivate(int x, int y){
        if (isPressed(x,y)) {
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
    bool ifPressedThenActivate(Point p){
        return ifPressedThenActivate(p.x, p.y);
    }
};

#endif