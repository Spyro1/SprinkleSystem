#ifndef POINT_H
#define POINT_H

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};
struct Size
{
    int width, height;
    Size(int width = 0, int height = 0) : width(width), height(height) {}
};

#endif