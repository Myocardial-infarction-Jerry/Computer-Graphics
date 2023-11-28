#include "volume.h"

volume::volume(color(*_shader)(const vec3 &) = nullptr) { shader = _shader; }

sphere::sphere(const point3 &_center, const double &_radius, color(*_shader)(const vec3 &) = nullptr) :center(_center), radius(_radius), volume(_shader) {}
color sphere::ray_color(const ray &r, std::vector<ray> &subray) {

}