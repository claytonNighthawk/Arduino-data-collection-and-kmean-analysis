#include <vector>
#include <utility>
#include "centroid.hpp" 
#include "point.hpp"

using namespace std:

Centroid::Centroid() {}

void Centroid::setLocation(double x, double y) {
    loc = make_pair(x, y);
}

pair<double, double> Centroid::getLocataion() {
    return loc;
}

void Centroid::addPoint(Point newP) {
    points.push_back(newP);
}

void Centroid::removePoint(Point oldP) {
    Point temp = find(points.begin(), points.end(), oldP); 
    if (temp != points.end()) {
        points.erase(temp);
    }
}

void Centroid::recalculate() { 
    int x = 0;
    int y = 0
    for (int i = 0; i < points.size(); i++) {
        x += points.loc.first;
        y += points.loc.second;  
    }
    pair<double, double> avg = make_pair(x / points.size(), y / points.size()); 
    loc = avg;
}

bool Centroid::operator==(const Centroid &other) { 
    return this->loc == other.loc;
}

bool Centroid::operator!=(const Centroid &other) {
    return !(*this == other);
}




