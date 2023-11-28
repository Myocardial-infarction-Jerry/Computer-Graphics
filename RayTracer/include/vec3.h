#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class vec3 {
public:
    vec3();
    vec3(const vec3 &v);
    vec3(const double &x, const double &y, const double &z);

    vec3 &operator=(const vec3 &v);
    double operator[](const int &index) const;
    double &operator[](const int &index);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;

    vec3 operator+(const vec3 &v) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator*(const double &val) const;
    friend vec3 operator*(const double &val, const vec3 &v);
    vec3 operator/(const double &val) const;

    vec3 &operator+=(const vec3 &v);
    vec3 &operator-=(const vec3 &v);
    vec3 &operator*=(const double &val);
    vec3 &operator/=(const double &val);

    friend double dot(const vec3 &u, const vec3 &v);
    friend vec3 cross(const vec3 &u, const vec3 &v);

    double length() const;
    double squared_length() const;
    vec3 unit() const;

private:
    double e[3];
};

using point3 = vec3;

#endif