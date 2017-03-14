#ifndef __FILEPARSER_HPP
#define __FILEPARSER_HPP

#include <vector>
#include <string>
#include <utility>
// #include "minmaxvector.hpp"

namespace kmean {
typedef std::pair<double, double> Point;

int fileParser(std::map<string, touple<vector<Point> pointsMap, double, double>>&, std::vector<std::string>& mapKeys, std::string fileName);

}
#endif