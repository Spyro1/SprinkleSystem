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
    bool isPressed(const int x, const int y) { return (x >= pos.x && x <= pos.x + size.x) && (y >= pos.y && y <= pos.y + size.y); }
    /**
     * Tests if the given coordinate is inside the button
     * @param p coordinate point
     * @return true if the coordinate is inside the button, false if outside
     */
    bool isPressed(const Point& p) { return isPressed(p.x, p.y); }

};
