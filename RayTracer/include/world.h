#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "volume.h"
#include "camera.h"

class world {
public:
    world();


private:
    std::vector<camera> cams;
    std::vector<surface> surs;
};

#endif