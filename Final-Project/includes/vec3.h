#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3 {
public:
    vec3();
    vec3(double e0, double e1, double e2);
    vec3(const vec3 &v);

    vec3 &operator=(const vec3 &v);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);
    double length() const;
    vec3 unit() const;

    vec3 operator+(const vec3 &v) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator*(const vec3 &v) const;
    vec3 operator/(const double &v) const;

    vec3 &operator+=(const vec3 &v);
    vec3 &operator-=(const vec3 &v);
    vec3 &operator*=(const vec3 &v);
    vec3 &operator*=(const double &v);
    vec3 &operator/=(const double &v);
private:
    double e[3];
};

inline double dot(const vec3 &a, const vec3 &b);
inline vec3 cross(const vec3 &a, const vec3 &b);
inline vec3 operator*(const vec3 &e, const double &v);
inline vec3 operator*(const double &v, const vec3 &e);

using point3 = vec3;
using color = vec3;

#endif