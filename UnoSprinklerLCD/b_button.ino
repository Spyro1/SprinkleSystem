// ******** button.ino ********

/**
 * @brief Represents a touch button on the user interface. 
 * The TouchButton struct defines the position and size of a button and provides methods to determine if the button is pressed.
 */
struct TouchButton {
  Point pos;   /**< The position of the top left corner of the button. */
  Point size;  /**< The size of the button. */

  /** 
   * @brief Default constructor for TouchButton. 
   * Initializes the button position and size to (0, 0). 
   * This constructor is mainly used for creating arrays of buttons.
   */
  TouchButton() : pos(0, 0), size(0, 0) {}
  /**
   * @brief Constructor with basic parameters. 
   * Initializes the button with the given position and size. 
   * @param x The x-coordinate of the top left corner of the button.
   * @param y The y-coordinate of the top left corner of the button.
   * @param width The width of the button.
   * @param height The height of the button.
   */
  TouchButton(const int x, const int y, const int width, const int height) : pos(x, y), size(width, height) {}
  /**
   * @brief Constructor with advanced parameters.
   * Initializes the button with the given position and size. 
   * @param position The top left corner of the button.
   * @param size The width and height of the button.
   */
  TouchButton(const Point& position, const Point& size) : pos(position), size(size) {}
  /**
   * @brief Tests if the given coordinate is inside the button.
   * @param x The x-coordinate to test.
   * @param y The y-coordinate to test.
   * @return True if the coordinate is inside the button, false otherwise.
   */
  bool isPressed(const int x, const int y) const { return (x >= pos.x && x <= pos.x + size.x) && (y >= pos.y && y <= pos.y + size.y); }
  /**
   * @brief Tests if the given coordinate is inside the button. 
   * @param p The coordinate point to test.
   * @return True if the coordinate is inside the button, false otherwise.
   */
  bool isPressed(const Point& p) const { return isPressed(p.x, p.y); }
};

/**
 * @brief Array of main screen buttons.
 */
const TouchButton mainBtns[mainScreenButtonCount] = { TouchButton(MAIN_1, ICONSIZE), TouchButton(MAIN_2, ICONSIZE), TouchButton(MAIN_3, ICONSIZE), TouchButton(MAIN_4, ICONSIZE), TouchButton(MAIN_5, ICONSIZE), TouchButton(MAIN_6, ICONSIZE) };
/**
 * @brief Array of submenu buttons.
 */
const TouchButton subMenuBtns[subMenuButtonCount] = {
  TouchButton(SLOT_1_1, ICONSIZE), TouchButton(SLOT_1_2, ICONSIZE), TouchButton(SLOT_1_3, ICONSIZE), TouchButton(SLOT_1_4, ICONSIZE),
  TouchButton(SLOT_2_1, ICONSIZE), TouchButton(SLOT_2_2, ICONSIZE), TouchButton(SLOT_2_3, ICONSIZE), TouchButton(SLOT_2_4, ICONSIZE),
  TouchButton(SLOT_3_1, ICONSIZE), TouchButton(SLOT_3_2, ICONSIZE), TouchButton(SLOT_3_3, ICONSIZE), TouchButton(SLOT_3_4, ICONSIZE)
};
/**
 * @brief Home button for the submenu.
 */
const TouchButton homeBtn(SUBMENU_HOME_POS, {x32, x32});

