#ifndef VOLUME_H
#define VOLUME_H

#include <vector>
#include <cmath>

#include "vec3.h"
#include "color.h"
#include "ray.h"

class volume {
public:
    color(*shader)(const vec3 &);

    volume(color(*_shader)(const vec3 &));
    virtual color ray_color(const ray &r, std::vector<ray> &subray);
};

class sphere :protected volume {
public:
    point3 center;
    double radius;

    sphere(const point3 &_center, const double &_radius, color(*_shader)(const vec3 &));
    color ray_color(const ray &r, std::vector<ray> &subray);
};

#endif