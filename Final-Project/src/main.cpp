#include <iostream>
#include <chrono>
#include <cmath>

#include "color.h"
#include "ray.h"
#include "vec3.h" 

double hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return -1.0;
    else
        return (-half_b - std::sqrt(discriminant)) / a;
}

color ray_color(const ray &r) {
    double t = hit_sphere(point3(0, 0, 1), 0.5, r);
    if (t > 0) {
        vec3 N = (r.at(t) - vec3(0, 0, 1)).unit();
        return 0.5 * color(1 - N.x(), 1 - N.y(), 1 - N.z());
    }

    auto a = 0.5 * (r.direction().y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[]) {
    // Image
    double aspect_ratio = 16.0 / 9.0; // Ideal ratio
    int image_height = 1080;
    int image_width = static_cast<int>(aspect_ratio * image_height);

    // Camera
    point3 camera(0, 0, 0);
    double focal_length = 1.0;
    vec3 camera_angle = vec3(0, 0, 1).unit();

    // Viewport
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height); // Actual ratio
    vec3 viewport_u = vec3(camera_angle.z(), 0, -camera_angle.x()).unit() * viewport_width;
    vec3 viewport_v = vec3(
        camera_angle.x() * camera_angle.y(),
        -(camera_angle.x() * camera_angle.x()) - (camera_angle.z() * camera_angle.z()),
        camera_angle.z() * camera_angle.y()
    ).unit() * viewport_height;
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    auto viewport_base = camera + focal_length * camera_angle - viewport_u / 2 - viewport_v / 2;
    auto pixel_base = viewport_base + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    fprintf(stdout, "P3\n%d %d\n255\n", image_width, image_height);
    for (int j = 0; j < image_height; ++j) {
        fprintf(stderr, "\rScanlines remain: %d ", image_height - j);
        // fflush(stderr);
        for (int i = 0; i < image_width; ++i) {
            auto pixel = pixel_base + i * pixel_delta_u + j * pixel_delta_v;
            ray r(camera, pixel - camera);

            color pixel_color = ray_color(r);
            std::cout << pixel_color;
        }
    }
    fprintf(stderr, "\rDone.                   \n");

    return 0;
}