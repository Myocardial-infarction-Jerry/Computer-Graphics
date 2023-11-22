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
    double length_squared() const;
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

    friend double dot(const vec3 &a, const vec3 &b);
    friend vec3 cross(const vec3 &a, const vec3 &b);
    friend vec3 operator*(const vec3 &e, const double &v);
    friend vec3 operator*(const double &v, const vec3 &e);

private:
    double e[3];
};

using point3 = vec3;
using color = vec3;

#endif