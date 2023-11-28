#include "camera.h"

camera::camera() {
    position = point3(0, 0, 0);
    direction = vec3(1, 0, 0);
    focal_length = 1.0;
    aspect_ratio = 16.0 / 9.0;
    image_width = 1920;
    image_height = 1080;
    viewport_width = 2.0;
    viewport_height = 1.125;
    sample_per_pixel = 1;
}

point3 camera::get_position() const { return position; }
vec3 camera::get_direction() const { return direction; }
double camera::get_focal_length() const { return focal_length; }
double camera::get_aspect_ratio() const { return aspect_ratio; }
int camera::get_image_width() const { return image_width; }
int camera::get_image_height() const { return image_height; }
double camera::get_viewport_width() const { return viewport_width; }
double camera::get_viewport_height() const { return viewport_height; }
int camera::get_sample_per_pixel() const { return sample_per_pixel; }

void camera::set_position(const point3 &_position) { position = _position; }
void camera::set_direction(const vec3 &_direction) { direction = _direction; }
void camera::set_focal_length(const double &_focal_length) { focal_length = _focal_length; }
void camera::set_aspect_ratio(const double &_aspect_ratio) {
    aspect_ratio = _aspect_ratio;
    image_height = static_cast<int>(image_width / aspect_ratio);
    viewport_height = viewport_width / (static_cast<double>(image_width) / image_height);
}
void camera::set_image_width(const int &_image_width) {
    image_width = _image_width;
    image_height = static_cast<int>(image_width / aspect_ratio);
}
void camera::set_image_height(const int &_image_height) {
    image_height = _image_height;
    image_width = static_cast<int>(image_height * aspect_ratio);
}
void camera::set_viewport_width(const double &_viewport_width) {
    viewport_width = _viewport_width;
    viewport_height = viewport_width / (static_cast<double>(image_width) / image_height);
}
void camera::set_viewport_height(const double &_viewpost_height) {
    viewport_height = _viewpost_height;
    viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
}
void camera::set_sample_per_pixel(const int &_sample_per_pixel) { sample_per_pixel = _sample_per_pixel; }