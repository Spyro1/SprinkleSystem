// ******** point.ino ********

/**
 * @brief Represents a point in 2D space.
 */
struct Point {
  int x, y; /**< The x and y coordinates of the point. */
  /**
    * @brief Default constructor.
    * Initializes the point to the given coordinates. If no coordinates are provided, initializes the point to (0, 0).
    * @param x_ The x coordinate. Default is 0.
    * @param y_ The y coordinate. Default is 0.
    */
  Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
  /**
   * @brief Copy constructor.
   * Initializes the point to the same coordinates as another point.
   * @param p The point to copy.
   */
  Point(const Point& p) : x(p.x), y(p.y) {}
   /**
   * @brief Equality operator. Compares two points for equality.
   * @param p The point to compare with.
   * @return True if the points have the same coordinates, false otherwise.
   */
  bool operator==(const Point &p) const { return this->x == p.x && this->y == p.y; }
  /**
   * @brief Inequality operator. Compares two points for inequality.
   * @param p The point to compare with.
   * @return True if the points have different coordinates, false otherwise.
   */
  bool operator!=(const Point &p) const { return this->x != p.x || this->y != p.y; }
  /**
   * @brief Assignment operator. Assigns the coordinates of one point to another.
   * @param p The point to assign from.
   * @return A reference to the assigned point.
   */
  Point& operator=(const Point &p) {
    if (this != &p) {
      this->x = p.x;
      this->y = p.y;
    }
    return *this;
  }
};


// ================== DECLARATIONS ==============

const Point SUBMENU_ICON_POS(4, 0);
const Point SUBMENU_HOME_POS(284, 0);
// MainMenu button locations
const Point MAIN_1(48, 8);
const Point MAIN_2(128, 8);
const Point MAIN_3(208, 8);
const Point MAIN_4(48, 168);
const Point MAIN_5(128, 168);
const Point MAIN_6(208, 168);
// Submenu table corners
const Point SLOT_1_1(8, 36);
const Point SLOT_1_2(88, 36);
const Point SLOT_1_3(168, 36);
const Point SLOT_1_4(248, 36);
const Point SLOT_2_1(8, 104);
const Point SLOT_2_2(88, 104);
const Point SLOT_2_3(168, 104);
const Point SLOT_2_4(248, 104);
const Point SLOT_3_1(8, 172);
const Point SLOT_3_2(88, 172);
const Point SLOT_3_3(168, 172);
const Point SLOT_3_4(248, 172);
const Point SLOTS[] = {SLOT_1_1, SLOT_1_2, SLOT_1_3, SLOT_1_4, SLOT_2_1, SLOT_2_2, SLOT_2_3, SLOT_2_4, SLOT_3_1, SLOT_3_2, SLOT_3_3, SLOT_3_4 };
// SubMenu button identifiers
const Point BTN_1_1(0, 0);
const Point BTN_1_2(1, 0);
const Point BTN_1_3(2, 0);
const Point BTN_1_4(3, 0);
const Point BTN_2_1(0, 1);
const Point BTN_2_2(1, 1);
const Point BTN_2_3(2, 1);
const Point BTN_2_4(3, 1);
const Point BTN_3_1(0, 2);
const Point BTN_3_2(1, 2);
const Point BTN_3_3(2, 2);
const Point BTN_3_4(3, 2);
// Sizes
const Point ICONSIZE(x64, x64);

// SUBMENU NUM FIELD POSITIONS
const Point COL_1_CENTER(40, 120);
const Point COL_1_LABEL(40, 160);
const Point COL_2_CENTER(120, 120);
const Point COL_2_LABEL(120, 160);
const Point COL_3_CENTER(200, 120);
const Point COL_3_LABEL(200, 160);
const Point COL_1_2_SEPARATOR(80, 136);
const Point COL_2_3_SEPARATOR(160, 136);
const Point COL_3_4_SEPARATOR(240, 136);
const Point COL_4_LABEL_T(280, 110);
const Point COL_4_LABEL_B(280, 160);