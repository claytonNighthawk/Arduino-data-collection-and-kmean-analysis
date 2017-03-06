#include "centroid.hpp" 
#include "point.hpp"
#include <utility>
#include <cmath>

using namespace std:

Point::Point() {}

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