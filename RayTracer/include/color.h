#ifndef COLOR_H
#define COLOR_H

#include <initializer_list>
#include <iostream>

#include "vec3.h"

class color {
public:
    color();
    color(const int &_r, const int &_g, const int &_b);
    color(const vec3 &v);

    friend color average_color(std::initializer_list<color> list);
    friend std::ostream &operator<<(std::ostream &out, const color &c);

private:
    int r, g, b;
};

#endif