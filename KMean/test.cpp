#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include "kmean.hpp"
#include "centroid.hpp" 

using namespace kmean;
using std::cout;
using std::endl;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void vectorMaker(std::vector<Point> &points, int numPoints) {
    double x, y;
    Point p;
    for (int i = 0; i < numPoints; i++) {
        x = fRand(0.0, 5.0);
        y = fRand(0.0, 5.0);
        p = std::make_pair(x, y);
        points.push_back(p);
    }
}

void printVector(std::vector<Point> &points) {
    cout << "Points " << points.size() << endl;
    for (unsigned int i = 0; i < points.size(); ++i) {
        cout << "(" << points[i].first << ", " << points[i].second << ") ";
    }
    cout << endl << endl;
}

void printVector(std::vector<Centroid> &centroids) {
    cout << "Centroids " << endl;
    for (unsigned int i = 0; i < centroids.size(); ++i) {
        cout << centroids[i] << " ";
    }
    cout << endl << endl;
}

void printCentroidPoints(std::vector<Centroid> &centroids) {
    cout << "Print points attached to centroids " << endl;
    std::vector<Point> points;
    for (unsigned int i = 0; i < centroids.size(); ++i) {
        points = centroids[i].getPoints();
        cout << "Centroid " << i << ": ";
        printVector(points);
    }
    // cout << endl;   
}

int main() {
    // srand(time(NULL));
    int numCentroids = 2; 
    int iteratons = 10; 
    std::vector<Point> points;
    double min = 0.0;
    double max = 5.0;

    vectorMaker(points, 5); 
    
    printVector(points);

    Kmean* kmeanTest = new Kmean(numCentroids, points, min, max);
    std::vector<Centroid> centroids = kmeanTest->getCentroids();
    printVector(centroids);
    printCentroidPoints(centroids);
    
    kmeanTest->run(iteratons);
    centroids = kmeanTest->getCentroids();

    printVector(centroids);
    printCentroidPoints(centroids);
    
    printVector(points);

    Point newPoint = std::make_pair(fRand(min, max), fRand(min, max));
    points.push_back(newPoint);
    kmeanTest->run(5); 

    printVector(centroids);
    printCentroidPoints(centroids);
    
    printVector(points);

    return 0;
}