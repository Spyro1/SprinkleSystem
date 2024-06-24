// ******** point.ino ********

typedef struct Point {
  int x, y;
  Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
  Point(const Point& p) : x(p.x), y(p.y) {}
  bool operator==(const Point &p) const { return this->x == p.x && this->y == p.y; }
  bool operator!=(const Point &p) const { return this->x != p.x || this->y != p.y; }
  Point& operator=(const Point &p) {
    if (this != &p) {
      this->x = p.x;
      this->y = p.y;
    }
    return *this;
  }

  Point operator+(int pusher){
    return Point(x+pusher, y+pusher);
  }
} Point;


// ================== DECLARATIONS ==============

const Point SUBMENU_ICON_POS(4, 0);
const Point SUBMENU_HOME_POS(284, 0);
// MainMenu button locations
const Point MAIN_1(8, 8);
const Point MAIN_2(88, 8);
const Point MAIN_3(168, 8);
const Point MAIN_4(248, 8);
const Point MAIN_5(48, 168);
const Point MAIN_6(128, 168);
const Point MAIN_7(208, 168);
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
// SubMenu button identifiers
const Point BTN_1_1(1, 1);
const Point BTN_1_2(2, 1);
const Point BTN_1_3(3, 1);
const Point BTN_1_4(4, 1);
const Point BTN_2_1(1, 2);
const Point BTN_2_2(2, 2);
const Point BTN_2_3(3, 2);
const Point BTN_2_4(4, 2);
const Point BTN_3_1(1, 3);
const Point BTN_3_2(2, 3);
const Point BTN_3_3(3, 3);
const Point BTN_3_4(4, 3);
// Sizes
const Point ICONSIZE(x64, x64);

// SUBMENU NUM FIELD POSITIONS
const Point COL_1_CENTER(40, 120);
const Point COL_1_LABEL(40, 154);
const Point COL_2_CENTER(120, 120);
const Point COL_2_LABEL(120, 154);
const Point COL_3_CENTER(200, 120);
const Point COL_3_LABEL(200, 154);
const Point COL_1_2_SEPARATOR(80, 120);
const Point COL_2_3_SEPARATOR(160, 120);
const Point COL_4_LABEL_T(280, 104);
const Point COL_4_LABEL_B(280, 154);