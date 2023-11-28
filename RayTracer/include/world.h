#ifndef WORLD_H
#define WORLD_H

#include <fstream>
#include <iostream>

#include "color.h"
#include "ray.h"
#include "volume.h"
#include "camera.h"

class world {
public:
    std::vector<camera> cams;
    std::vector<volume> surs;

    world();

    void render(std::ostream &out, const camera &cam);
};

#endif