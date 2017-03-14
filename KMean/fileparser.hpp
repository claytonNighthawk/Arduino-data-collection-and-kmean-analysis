#ifndef __KMEAN_HPP
#define __KMEAN_HPP

#include <vector>
#include <string>
#include <utility>

typedef std::pair<double, double> Point;

int fileParser(string fileName, std::vector<Point> &TimeTemp, std::vector<Point> &TimeLight, std::vector<Point> &TimeSound, std::vector<Point> &TempLight, \
                std::vector<Point> &TempSound, std::vector<Point> &LightSound);

#endif