#include <vector>
#include <utility>
#include "kmean.hpp"
#include "centroid.hpp" 
#include "point.hpp"
// http://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c

using namespace std:

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Kmean::Kmean() {}

Kmean::Kmean(int numCentroids, vector<Point> &points) {
    this->points = points;

    for (int i = 0; i < numCentroids; i++) {
        double x = fRand(15.0, 25.0); // needs a way to determine min and max of data set
        double y = fRand(15.0, 25.0); // needs a way to determine min and max of data set
        cent = new Centroid(double x, double y);
        centroids.push_back(cent);
    }
}

void Kmean::addPoint(double x, double y) {
    Point p = new Point(x, y);
    points.push_back(p);
} 

void Kmean::addCentroid(double x, double y) {
    Centroid c = new Centroid(x, y);
    centroids.push_back(c);
}

void Kmean::run(int iterations) {
    Point p = points[0];
    Centroid c = centroids[0];
    double minDist = p.computeDist(c);
    int closestCentroid = 0; 
    double tempDist;
    Centroid oldCentroid;
    for (int n = 0; n < iterations; ++n) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < centroids.size(); j++) {
                tempDist = p.computeDist(c);
                if (minDist > tempDist) {
                    minDist = tempDist;
                    closestCentroid = j;
                }
                p = points[i];
                c = centroids[j];
            }

            oldCentroid = p.getCentroid();
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