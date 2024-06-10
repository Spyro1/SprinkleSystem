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
} Point;

// struct Size : Point {
//   Size(int width = 0, int height = 0) : Point(width, height) {}
//   Size(const Size& s) : Point(s) {}
//   Size(const Point& p) : Point(p) {}
// };