#include "color.h"

color::color() :r(0), g(0), b(0) {}
color::color(const int &_r, const int &_g, const int &_b) :r(_r), g(_g), b(_b) {}
color::color(const vec3 &v) :r(static_cast<int>(v[0])), g(static_cast<int>(v[1])), b(static_cast<int>(v[2])) {}

color average_color(std::initializer_list<color> list) {
    int r = 0, g = 0, b = 0;
    for (auto &c : list)
        r += c.r, b += c.b, g += c.g;
    int size = list.size();
    return color(r / size, g / size, b / size);
}
std::ostream &operator<<(std::ostream &out, const color &c) { return out << c.r << ' ' << c.g << ' ' << c.b << '\n'; }