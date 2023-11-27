#include "volume.h"

surface::surface() {}
void surface::add_vertex(const vec3 &_ver) { ver.push_back(_ver); }

sphere::sphere(const point3 &_center, const double &_radius, color(*_shader)(const vec3 &), const int &_div = 10000) :shader(_shader) {

}