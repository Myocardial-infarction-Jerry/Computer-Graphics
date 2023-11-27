#ifndef SPHERE_H
#define SPHERE_H   

#include "hittable.h"
#include "vec3.h"

class sphere :public hittable {
public:
    sphere(point3 _center, double _radius);

    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override;

private:
    point3 center;
    double radius;
};

#endif