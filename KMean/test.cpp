#include <vector>
#include <utility>
#include "kmean.hpp"
#include "centroid.hpp" 
#include "point.hpp"

using namespace kmean;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void vectorMaker(std::vector<Point> &points, int numPoints) {
    double x, y;
    Point p;
    for (int i = 0; i < numPoints; i++) {
        x = fRand(0, 5);
        y = fRand(0, 5);
        p = new Point(x, y);
        points.push_back(p);
    }
}

void printVector(std::vector<Point> &points) {
    for (auto i = points.begin(); i != points.end(); ++i) {
        cout << *i << ' ';
    }
}

void printVector(std::vector<Centroid> &centroids) {
    for (auto i = centroids.begin(); i != centroids.end(); ++i) {
        cout << *i << ' ';
    }
}

int main() {
    int numCentroids = 6; 
    int iteratons = 20; 
    std::vector<Point> points;

    vectorMaker(points, 10); 
    printVector(points);

    Kmean kmeanTest = new Kmean(numCentroids, points);

    kmeanTest.run(iteratons);
    std::vector<Centroid> centroids = kmeanTest.getCentroids();

    printVector(centroids);
    printVector(points);

    points.push_back(newPoint);
    kmeanTest.run(5); 

    printVector(centroids);
    printVector(points);

    return 0;
}