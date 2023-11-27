#include "vec3.h"

vec3::vec3() :e{ .0,.0,.0 } {}
vec3::vec3(const vec3 &v) :e{ v[0],v[1],v[2] } {}
vec3::vec3(const double &x, const double &y, const double &z) :e{ x,y,z } {}

vec3 &vec3::operator=(const vec3 &v) { e[0] = v[0], e[1] = v[1], e[2] = v[2]; return *this; }
double vec3::operator[](const int &index) const { return e[index]; }
double &vec3::operator[](const int &index) { return e[index]; }

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

vec3 vec3::operator+(const vec3 &v) const { return vec3(e[0] + v[0], e[1] + v[1], e[2] + v[2]); }
vec3 vec3::operator-(const vec3 &v) const { return vec3(e[0] - v[0], e[1] - v[1], e[2] - v[2]); }
vec3 vec3::operator*(const double &val) const { return vec3(e[0] * val, e[1] * val, e[2] * val); }
vec3 operator*(const double &val, const vec3 &v) { return vec3(v[0] * val, v[1] * val, v[2] * val); }
vec3 vec3::operator/(const double &val) const { return vec3(e[0] / val, e[1] / val, e[2] / val); }

vec3 &vec3::operator+=(const vec3 &v) { e[0] += v[0], e[1] += v[1], e[2] += v[2]; return *this; }
vec3 &vec3::operator-=(const vec3 &v) { e[0] -= v[0], e[1] -= v[1], e[2] -= v[2]; return *this; }
vec3 &vec3::operator*=(const double &val) { e[0] *= val, e[1] *= val, e[2] *= val; return *this; }
vec3 &vec3::operator/=(const double &val) { e[0] /= val, e[1] /= val, e[2] /= val; return *this; }

double vec3::dot(const vec3 &v) const { return e[0] * v[0] + e[1] * v[1] + e[2] * v[2]; }
vec3 vec3::cross(const vec3 &v) const {
    return vec3(
        e[1] * v[2] - e[2] * v[1],
        e[2] * v[0] - e[0] * v[2],
        e[0] * v[1] - e[1] * v[0]
    );
}

double vec3::length() const { return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
double vec3::squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
vec3 vec3::unit() const { return *this / length(); }