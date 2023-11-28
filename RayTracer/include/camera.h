#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class camera {
public:
    camera();

    point3 get_position() const;
    vec3 get_direction() const;
    double get_focal_length() const;
    double get_aspect_ratio() const;
    int get_image_width() const;
    int get_image_height() const;
    double get_viewport_width() const;
    double get_viewport_height() const;
    int get_sample_per_pixel() const;

    void set_position(const point3 &_position);
    void set_direction(const vec3 &_direction);
    void set_focal_length(const double &_focal_length);
    void set_aspect_ratio(const double &_aspect_ratio); // Follow image_width
    void set_image_width(const int &_image_width);
    void set_image_height(const int &_image_height);
    void set_viewport_width(const double &_viewport_width);
    void set_viewport_height(const double &_viewpost_height);
    void set_sample_per_pixel(const int &_sample_per_pixel);

private:
    point3 position;
    vec3 direction;
    double focal_length;
    double aspect_ratio;
    int image_width, image_height;
    double viewport_width, viewport_height;
    int sample_per_pixel;
};

#endif