#include <vector>
#include <utility>
#include <cstdlib>

#include "kmean.hpp"
#include "centroid.hpp" 

using namespace kmean;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void vectorMaker(std::vector<Point*> &points, int numPoints) {
    double x, y;
    Point p;
    for (int i = 0; i < numPoints; i++) {
        x = fRand(0, 5);
        y = fRand(0, 5);
        p = std::make_pair(x, y);
        points.push_back(&p);
    }
}

// void printVector(std::vector<Point*> &points) {
//     for (auto i = points.begin(); i != points.end(); ++i) {
//         std::cout << **i << ' ';
//     }
// }

// void printVector(std::vector<Centroid> &centroids) {
//     for (auto i = centroids.begin(); i != centroids.end(); ++i) {
//         std::cout << *i << ' ';
//     }
// }

int main() {
    srand(time(NULL));
    int numCentroids = 6; 
    int iteratons = 10; 
    std::vector<Point*> pointsPTR;

    vectorMaker(pointsPTR, 10); 
    // printVector(pointsPTR);

    Kmean* kmeanTest = new Kmean(numCentroids, pointsPTR);

    kmeanTest->run(iteratons);
    std::vector<Centroid> centroids = kmeanTest->getCentroids();

    // printVector(centroids);
    // printVector(pointsPTR);

    Point newPoint = std::make_pair(fRand(0, 5), fRand(0, 5));
    pointsPTR.push_back(&newPoint);
    kmeanTest->run(5); 

    // printVector(centroids);
    // printVector(pointsPTR);

    return 0;
}