#include <vector>
#include <utility>
#include "kmean.hpp"
#include "centroid.hpp" 

namespace kmean {

double fRand(double fMin, double fMax) {
    // http://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Kmean::Kmean() {}

Kmean::Kmean(int numCentroids, std::vector<Point> &points) {
    this->points = points;

    for (int i = 0; i < numCentroids; i++) {
        double x = fRand(15.0, 25.0); // needs a way to determine min and max of data set
        double y = fRand(15.0, 25.0); // needs a way to determine min and max of data set
        Centroid* cent = new Centroid(x, y);
        centroids.push_back(*cent);
    }
}

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
    Point p = points[0];
    Centroid c = centroids[0];
    double minDist = c.computeDist(p);
    int closestCentroid = 0; // 
    double tempDist;
    Centroid oldCentroid;
    for (int n = 0; n < iterations; ++n) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < centroids.size(); j++) {
                tempDist = c.computeDist(p);
                if (minDist > tempDist) {
                    minDist = tempDist;
                    closestCentroid = j;
                }
                p = points[i];
                c = centroids[j];
            }

            oldCentroid = p.getCentroid(); // Point not a class anymore this needs to be changed
            if (oldCentroid != centroids[closestCentroid]) {
                oldCentroid.removePoint(p);
                p.setCentroid(centroids[closestCentroid]);
                centroids[closestCentroid].addPoint(p);
            }
        }

        for (int k = 0; k < centroids.size(); k++) {
            centroids[k].recalculate();
        }
    }
    // Then graph the results or more interesting graph them as the method runs
}

};