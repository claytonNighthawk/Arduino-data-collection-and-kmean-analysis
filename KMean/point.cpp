#include <utility>
#include <cmath>
#include "centroid.hpp" 
#include "point.hpp"

using namespace std:

Point::Point(double x, double y) {
	loc = std::make_pair(x, y);
}

Point::Point(const std::pair<double, double> loc) {
	this->loc = loc;
}

double Point::computeDist(Centroid cent) {
	double d21 = ((cent.loc.first - loc.first) * (cent.loc.first - loc.first));  // The first term in the dist formula 
	double d22 = ((cent.loc.second - loc.second) * (cent.loc.second - loc.second));  // The second term in the dist formula 
	return sqrt(abs(d21 + d22)); 							// The final distance from the point to the provided centroid
}

void Point::setCentroid(Centroid c) {
	cent = c;
}

Centroid Point::getCentroid() {
	return cent;
}

bool Point::operator==(const Point &other) { 
    return this->loc == other.loc;
}

bool Point::operator!=(const Point &other) {
    return !(*this == other);
}