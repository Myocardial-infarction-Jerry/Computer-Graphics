#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "surface.h"

class world {
public:
    world();

    vector<vector<color>> *render()

private:
    vector<camera> cams;
    vector<surface> surs;
};

#endif