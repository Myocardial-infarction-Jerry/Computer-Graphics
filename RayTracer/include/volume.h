#ifndef VOLUME_H
#define VOLUME_H

#include <vector>

#include "vec3.h"
#include "color.h"

class surface {
public:
    surface();
protected:
    std::vector<vec3> ver;

    void add_vertex(const vec3 &vertex);
    virtual color shader(const int &index) const;
};

class sphere :public surface {
public:
    sphere(const point3 &_center, const double &_radius, color(*_shader)(const vec3 &), const int &_div);
    color(*shader)(const vec3 &);
};

#endif