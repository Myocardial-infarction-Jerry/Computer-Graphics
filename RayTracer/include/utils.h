#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::cerr;

std::ofstream fp;

double randf() { return double(rand()) / RAND_MAX; }

#endif