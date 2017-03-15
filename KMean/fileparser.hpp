#ifndef __FILEPARSER_HPP
#define __FILEPARSER_HPP

#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <utility>

// using std::map;
// using std::string;
// using std::tuple;
// using std::vector; 

typedef std::pair<double, double> Point;

int fileParser(std::map<std::string, std::tuple<std::vector<Point>, double, double>>&, std::vector<std::string>& mapKeys, std::string fileName);

#endif