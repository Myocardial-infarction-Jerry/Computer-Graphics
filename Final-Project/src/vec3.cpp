#include "vec3.h"

vec3::vec3() :e{ 0,0,0 } {}
vec3::vec3(double e1, double e2, double e3) :e{ e1,e2,e3 } {}
vec3::vec3(const vec3 &v) :e{ v[0],v[1],v[2] } {}

vec3 &vec3::operator=(const vec3 &v) {
    if (&v != this)
        return *this;
    e[0] = v[0], e[1] = v[1], e[2] = v[2];
    return *this;
}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-()const { return vec3(-e[0], -e[1], -e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double &vec3::operator[](int i) { return e[i]; }
double vec3::length() const { return std::sqrt(length_squared()); }
double vec3::length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
vec3 vec3::unit() const { return *this / length(); }

vec3 vec3::operator+(const vec3 &v) const { return vec3(e[0] + v[0], e[1] + v[1], e[2] + v[2]); }
vec3 vec3::operator-(const vec3 &v) const { return vec3(e[0] - v[0], e[1] - v[1], e[2] - v[2]); }
vec3 vec3::operator*(const vec3 &v) const { return vec3(e[0] * v[0], e[1] * v[1], e[2] * v[2]); }
vec3 vec3::operator/(const double &v) const { return vec3(e[0] / v, e[1] / v, e[2] / v); }

vec3 &vec3::operator+=(const vec3 &v) { return *this = *this + v; }
vec3 &vec3::operator-=(const vec3 &v) { return *this = *this - v; }
vec3 &vec3::operator*=(const vec3 &v) { return *this = *this * v; }
vec3 &vec3::operator*=(const double &v) { return *this = *this * v; }
vec3 &vec3::operator/=(const double &v) { return *this = *this / v; }

double dot(const vec3 &a, const vec3 &b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
vec3 cross(const vec3 &a, const vec3 &b) { return vec3(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]); }
vec3 operator*(const vec3 &e, const double &v) { return vec3(e[0] * v, e[1] * v, e[2] * v); }
vec3 operator*(const double &v, const vec3 &e) { return e * v; }