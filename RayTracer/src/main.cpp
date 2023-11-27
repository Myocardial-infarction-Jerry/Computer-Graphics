#include "utils.h"
#include "world.h"

extern std::ofstream fp;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./main [image_file.ppm]\n";
        return 0;
    }

    fp = std::ofstream(argv[1]);

    world flat;

    fp.close();

    return 0;
}