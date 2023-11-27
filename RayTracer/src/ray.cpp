#include "ray.h"

ray::ray() :origin(), direction() {}
ray::ray(const point3 &_origin, const vec3 &_direction) :origin(_origin), direction(_direction.unit()) {}

point3 ray::get_origin() const { return origin; }
vec3 ray::get_direction() const { return direction; }

void ray::set_origin(const point3 &_origin) { origin = _origin; }
void ray::set_direction(const vec3 &_direction) { direction = _direction.unit(); }