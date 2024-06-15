// ******** button.ino ********

struct TouchButton {
    Point pos;       // Position of top left corner
    Point size;       // Size of the button

    // -- Constructors --
    /** Default constructor of TocuhButton. Used for arrays. */
    TouchButton() : pos(0, 0), size(0, 0) {}
    /**
     * Constructor with basic parameters
     * @param x top left corner of button
     * @param y top left corner of button
     * @param width width of the button
     * @param height height of the button
     */
    TouchButton(const int x, const int y, const int width, const int height) : pos(x, y), size(width, height) {}
    /**
     * Constructor with advanced parameters
     * @param position top left corner of button
     * @param size width and height of the button
     */
    TouchButton(const Point& position, const Point& size) : pos(position), size(size) {}
    /**
     * Tests if the given coordinate is inside the button
     * @param x x coordinate
     * @param y y coordinate
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(const int x, const int y) const { return (x >= pos.x && x <= pos.x + size.x) && (y >= pos.y && y <= pos.y + size.y); }
    /**
     * Tests if the given coordinate is inside the button
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(const Point& p) const { return isPressed(p.x, p.y); }

};

const TouchButton mainBtns[mainScreenButtonCount] = { TouchButton(MAIN_1, ICONSIZE), TouchButton(MAIN_2, ICONSIZE), TouchButton(MAIN_3, ICONSIZE), TouchButton(MAIN_4, ICONSIZE), TouchButton(MAIN_5, ICONSIZE), TouchButton(MAIN_6, ICONSIZE), TouchButton(MAIN_7, ICONSIZE) };

const TouchButton subMenuBtns[subMenuButtonCount] = {
  TouchButton(SLOT_1_1, ICONSIZE), TouchButton(SLOT_1_2, ICONSIZE), TouchButton(SLOT_1_3, ICONSIZE), TouchButton(SLOT_1_4, ICONSIZE),
  TouchButton(SLOT_2_1, ICONSIZE), TouchButton(SLOT_2_2, ICONSIZE), TouchButton(SLOT_2_3, ICONSIZE), TouchButton(SLOT_2_4, ICONSIZE),
  TouchButton(SLOT_3_1, ICONSIZE), TouchButton(SLOT_3_2, ICONSIZE), TouchButton(SLOT_3_3, ICONSIZE), TouchButton(SLOT_3_4, ICONSIZE)
};

const TouchButton homeBtn(SUBMENU_HOME_POS, {x32, x32});

