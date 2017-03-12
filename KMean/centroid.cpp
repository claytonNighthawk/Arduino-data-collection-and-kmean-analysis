#include <algorithm>    // std::find
#include <vector>       // std::vector
#include <utility>      // std::pair
#include <cmath>        
#include "centroid.hpp" 
// #include "point.hpp"

namespace kmean {

Centroid::Centroid() {}

Centroid::Centroid(double x, double y) {
    loc = std::make_pair(x, y);
}

Centroid::~Centroid() {} // probably causes memory leaks need to come back to this later

void Centroid::setLocation(double x, double y) {
    loc = std::make_pair(x, y);
}

std::pair<double, double> Centroid::getLocation() {
    return loc;
}

void Centroid::addPoint(Point* newP) {
    pointsPTR.push_back(newP);
}

void Centroid::clearPoints() {
    pointsPTR.clear();
}

// void Centroid::removePoint(Point oldP) {
//     auto temp = find(points.begin(), points.end(), oldP); 
//     if (temp != points.end()) {
//         points.erase(temp);
//     }
// }

double Centroid::computeDist(Point* point) {
    double d21 = ((*point).first - loc.first) * ((*point).first - loc.first);  // The first term in the dist formula 
    double d22 = ((*point).second - loc.second) * ((*point).second - loc.second);  // The second term in the dist formula 
    return sqrt(d21 + d22);                            // The final distance from the point to the provided centroid
}

void Centroid::recalculate() { 
    double x = 0;
    double y = 0;
    for (unsigned int i = 0; i < pointsPTR.size(); i++) {
        x += pointsPTR[i]->first;
        y += pointsPTR[i]->second;  
    }
    Point avg = std::make_pair(x / pointsPTR.size(), y / pointsPTR.size()); 
    loc = avg;
}

bool Centroid::operator==(const Centroid &other) { 
    return this->loc == other.loc;
}

bool Centroid::operator!=(const Centroid &other) {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Centroid& cent) {
    os << "(" << cent.loc.first << ", " << cent.loc.second << ")";
    return os;
}

};


