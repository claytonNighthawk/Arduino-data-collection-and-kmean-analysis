#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "kmean.hpp"
#include "centroid.hpp" 
// #include "minmaxvector.hpp"
#include "fileparser.hpp" // fileparser from chris

using namespace kmean;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::map;
using std::touple;
using std::string;

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
    int numCentroids = 15; 
    int iteratons = 1; 
    double min = 15.0; // for temp
    double max = 250;
    map<string, touple<vector<Point>, double, double>> pointsMap;
    std::vector<string> mapKeys = {"TimeTemp", "TimeLight", "TimeSound", "TempLight", "TempSound", "LightSound"};


    // T = time, Temp = temperature, L = light, S = sound
    // vector<Point> points_TTemp;
    // vector<Point> points_TL;
    // vector<Point> points_TS;
    // vector<Point> points_TempL;
    // vector<Point> points_TempS;
    // vector<Point> points_LS;
    // a vector of vectors would make more sense
    

    // calls fileparser and populates the map and everything inside of it 
    fileParser(pointsMap, mapKeys, "data/singlesensor");
    
    // Kmean* kmean_TTemp = new Kmean(points_TTemp, numCentroids, min, max);
    // Kmean* kmean_TL = new Kmean(numCentroids, points_TL);
    // Kmean* kmean_TS = new Kmean(points_TS, numCentroids, min, max);
    // Kmean* kmean_TempL = new Kmean(numCentroids, points_TempL);
    Kmean* kmean_TempS = new Kmean(pointsMap, numCentroids, min, max);
    // Kmean* kmean_LS = new Kmean(numCentroids, points_LS);

    printVector(points_TempS);
    std::vector<Centroid> centroids_TempS = kmean_TempS->getCentroids();
    printVector(centroids_TempS);
    
    for (int i = 0; i < iteratons; i++) {
        kmean_TempS->run(1);
        centroids_TempS = kmean_TempS->getCentroids();
        // printVector(points_TempS);
        // printVector(centroids_TempS);
        printCentroidPoints(centroids_TempS);
    }


    // kmean_TTemp.run(iteratons);
    // centroids_TTemp = kmean_TTemp.getCentroids();
    // graph results or maybe have kmean class do graphing internally, would probably make more sense

    // // data streaming 
    // dataStreamer();
    // points_TTemp.push_back(newPoint);
    // kmean_TTemp.run(5); 

    return 0;
}