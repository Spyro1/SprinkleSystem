// ******** point.ino ********

typedef struct Point {
  int x, y;
  Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
  Point(const Point& p) : x(p.x), y(p.y) {}
  bool operator==(const Point &p) { return x == p.x && y == p.y; }
  bool operator!=(const Point &p) { return x != p.x || y != p.y; }
  Point& operator=(const Point &p) {
    if (this != &p) {
      x = p.x;
      y = p.y;
    }
    return *this;
  }

  Point operator+(int pusher){
    return Point(x+pusher, y+pusher);
  }
} Point;


// ================== DECLARATIONS ==============

Point SUBMENU_ICON_POS(4, 0);
Point SUBMENU_HOME_POS(284, 0);
// MainMenu button locations
Point MAIN_1(8, 8);
Point MAIN_2(88, 8);
Point MAIN_3(168, 8);
Point MAIN_4(248, 8);
Point MAIN_5(48, 168);
Point MAIN_6(128, 168);
Point MAIN_7(208, 168);
// Submenu table corners
Point SLOT_1_1(8, 36);
Point SLOT_1_2(88, 36);
Point SLOT_1_3(168, 36);
Point SLOT_1_4(248, 36);
Point SLOT_2_1(8, 104);
Point SLOT_2_2(88, 104);
Point SLOT_2_3(168, 104);
Point SLOT_2_4(248, 104);
Point SLOT_3_1(8, 172);
Point SLOT_3_2(88, 172);
Point SLOT_3_3(168, 172);
Point SLOT_3_4(248, 172);
// SubMenu button identifiers
Point BTN_1_1(1, 1);
Point BTN_1_2(2, 1);
Point BTN_1_3(3, 1);
Point BTN_1_4(4, 1);
Point BTN_2_1(1, 2);
Point BTN_2_2(2, 2);
Point BTN_2_3(3, 2);
Point BTN_2_4(4, 2);
Point BTN_3_1(1, 3);
Point BTN_3_2(2, 3);
Point BTN_3_3(3, 3);
Point BTN_3_4(4, 3);