#include "world.h"
#include "utils.h"

world::world() {}

void world::render(std::ostream &out, const camera &cam) {
    auto dir = cam.get_direction(), pos = cam.get_position();

    auto viewport_u = vec3(-dir.z(), 0, dir.x()).unit() * cam.get_viewport_width();
    if (viewport_u.x() < 0) viewport_u = -viewport_u;
    auto viewport_v = cross(dir, viewport_u).unit() * cam.get_viewport_height();
    if (viewport_v.y() > 0) viewport_v = -viewport_v;

    auto pixel_delta_u = viewport_u / cam.get_image_width();
    auto pixel_delta_v = viewport_v / cam.get_image_height();

    auto viewport_base = cam.get_position() + dir * cam.get_focal_length() - viewport_u / 2 - viewport_v / 2;

    std::clog << "Rendering cam " << &cam << " at " << '(' << pos.x() << ", " << pos.y() << ", " << pos.z() << ')' << "\n";
    out << "P3\n" << cam.get_image_width() << ' ' << cam.get_image_height() << "\n255\n";

    std::vector<std::vector<std::vector<ray>>> ray_list(cam.get_image_width(), std::vector<std::vector<ray>>(cam.get_image_height()));

    for (int j = 0; j < cam.get_image_height(); ++j) {
        for (int i = 0; i < cam.get_image_width(); ++i)
            for (int t = 0; t < cam.get_sample_per_pixel(); ++t) {
                auto pixel = viewport_base + (randf() + i) * pixel_delta_u + (randf() + j) * pixel_delta_v;
                ray_list[i][j].push_back(ray(pos, pixel - pos));
            }
    }


}