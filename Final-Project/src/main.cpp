#include <bits/stdc++.h>
#include "vec3.h"
#include "color.h"
using namespace std;

int main(int argc, char const *argv[]) {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // aRender
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.5);
            cout << pixel;
        }
    }
    cerr << "\nDone.\n";
    return 0;
}
