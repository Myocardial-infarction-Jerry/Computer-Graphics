#include "color.h"

std::ostream &operator<<(std::ostream &out, const color &c) {
    return out << static_cast<int>(255.999 * c[0]) << ' ' << static_cast<int>(255.999 * c[1]) << ' ' << static_cast<int>(255.999 * c[2]) << '\n';
}