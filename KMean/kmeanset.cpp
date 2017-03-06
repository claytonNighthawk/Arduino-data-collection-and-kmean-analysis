#include "centroid.hpp" 
#include "point.hpp"

using namespace std:

Kmean::Kmean(int numCentroids, vector<Point> points) {
    this->points = points;

    for (int i = 0; i < numCentroids; i++) {
        double x = (double) i; // needs initialization with random double
        double y = (double) i; // needs initialization with random double
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
    for (int k = 0; k < iterations; ++k) {
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

        for (int c = 0; c < centroids.size(); c++) {
            centroids[c].recalculate();
        }
    }
    // Then graph the results
}