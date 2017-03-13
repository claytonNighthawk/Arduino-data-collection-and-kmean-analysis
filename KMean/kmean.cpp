#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include "kmean.hpp"
#include "centroid.hpp" 

namespace kmean {

double fRand(double fMin, double fMax) {
    // http://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Kmean::Kmean(int numCentroids, std::vector<Point> &points, double min, double max) {
    this->points = points;

    for (int i = 0; i < numCentroids; i++) {
        double x = fRand(min, max); // needs a way to determine min and max of data set
        double y = fRand(min, max); // needs a way to determine min and max of data set
        Centroid* cent = new Centroid(x, y);
        centroids.push_back(*cent);
    }
}

Kmean::~Kmean() {} //TODO: probably causes memory leaks need to come back to this later

// void Kmean::addPoint(double x, double y) {
//     Point p = new Point(x, y);
//     points.push_back(p);
// } 

void Kmean::addCentroid(double x, double y) {
    Centroid* c = new Centroid(x, y);
    centroids.push_back(*c);
}

std::vector<Centroid> Kmean::getCentroids() {
    return centroids;
}

void Kmean::run(int iterations) {
    Point p;
    Centroid c;
    int closestCentroid = 0;  
    double tempDist;
    for (int n = 0; n < iterations; ++n) {
        unsigned int k; // used when indexing into centroids 
        // clears the vector of points ready for the new iteration
        for (k = 0; k < centroids.size(); k++) {
            centroids[k].clearPoints();
        }
        
        // calculates closest centroid for each point
        for (unsigned int i = 0; i < points.size(); i++) {
            p = points[i];
            c = centroids[0];
            double minDist = c.computeDist(p);
            for (k = 0; k < centroids.size(); k++) {
                tempDist = c.computeDist(p);
                if (minDist > tempDist) {
                    minDist = tempDist;
                    closestCentroid = k;
                }
                c = centroids[k];
            }
            centroids[closestCentroid].addPoint(points[i]);
        }

        // recalculate the centroid locations
        for (k = 0; k < centroids.size(); k++) {
            centroids[k].recalculate();
        }

    }
}
// Then graph the results or more interesting graph them as the method runs

};