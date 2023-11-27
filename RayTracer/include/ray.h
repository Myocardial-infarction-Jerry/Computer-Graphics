#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray();
    ray(const point3 &_origin, const vec3 &_direction);

    point3 get_origin() const;
    vec3 get_direction() const;

    void set_origin(const point3 &_origin);
    void set_direction(const vec3 &_direction);

    point3 at(const double &t) const;

private:
    point3 origin;
    vec3 direction;
};

#endif