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

void pointVectorAdder(std::vector<Point> &points, double min, double max, int numPoints) {
    double x, y;
    Point p;
    for (int i = 0; i < numPoints; i++) {
        x = fRand(min, max);
        y = fRand(min, max);
        p = std::make_pair(x, y);
        points.push_back(p);
    }
}

void printVector(std::vector<Point> &points) {
    cout << "Points " << points.size();
    for (unsigned int i = 0; i < points.size(); ++i) {
        if (i % 6 == 0) {
            cout << endl;
        }
        cout << "(" << points[i].first << ", " << points[i].second << ") ";
    }
    cout << endl << endl;
}

void printVector(std::vector<Centroid> &centroids) {
    cout << "Centroids " << centroids.size() << endl;
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
        cout << "Centroid " << i << " @ " << centroids[i] << " : ";
        printVector(points);
    }
    // cout << endl;   
}

int main() {
    // srand(time(NULL));
    // int numCentroids = 2; 
    int iteratons = 3; 
    std::vector<Point> points;
    double min = 0.0;
    double max = 5.0;

    pointVectorAdder(points, min, max, 24);
    // pointVectorAdder(points, min, 3, 12); 
    // pointVectorAdder(points, 3, max, 12); 

    
    printVector(points);

    Kmean* kmeanTest = new Kmean(points, 4, min, max);
    // kmeanTest->addCentroid(fRand(3, 4), fRand(3, 4));
    // kmeanTest->addCentroid(fRand(4, max), fRand(4, max));
    std::vector<Centroid> centroids = kmeanTest->getCentroids();
    printVector(centroids);
    
    for (int i = 0; i < iteratons; i++) {
        kmeanTest->run(1);
        centroids = kmeanTest->getCentroids();
        printVector(points);
        // printVector(centroids);
        printCentroidPoints(centroids);
    }

    // kmeanTest->addCentroid(fRand(4, 5), fRand(4,max));
    // pointVectorAdder(points, min, max, 1); 
    // kmeanTest->run(iteratons); 
    // centroids = kmeanTest->getCentroids();

    // printVector(centroids);
    // printCentroidPoints(centroids);
    
    // printVector(points);

    return 0;
}