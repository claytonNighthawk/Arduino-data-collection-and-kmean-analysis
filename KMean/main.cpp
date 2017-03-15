#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include "kmean.hpp"
#include "centroid.hpp" 
#include "fileparser.hpp" // fileparser from chris

using namespace kmean;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::map;
using std::tuple;
using std::string;
using std::get;

void printVector(vector<Point> &points) {
    cout << "Points " << points.size();
    for (unsigned int i = 0; i < points.size(); ++i) {
        if (i % 6 == 0) {
            cout << endl;
        }
        cout << "(" << points[i].first << ", " << points[i].second << ") ";
    }
    cout << endl << endl;
}

void printVector(vector<Centroid> &centroids) {
    cout << "Centroids " << centroids.size() << endl;
    for (unsigned int i = 0; i < centroids.size(); ++i) {
        if (i % 6 == 0) {
            cout << endl;
        }
        cout << centroids[i] << " ";
    }
    cout << endl << endl;
}

void printCentroidPoints(vector<Centroid> &centroids) {
    cout << "Print points attached to centroids " << endl;
    vector<Point> points;
    for (unsigned int i = 0; i < centroids.size(); ++i) {
        points = centroids[i].getPoints();
        cout << "Centroid " << i << " @ " << centroids[i] << " : ";
        printVector(points);
    }
    // cout << endl;   
}

int main() {
    int numCentroids = 10; 
    int iteratons = 1; 
    map<string, tuple<vector<Point>, double, double>> minMaxVectorMap;
    vector<string> mapKeys = {"TimeTemp", "TimeLight", "TimeSound", "TempLight", "TempSound", "LightSound"};
    map<string, Kmean*> kmeanMap;


    // T = time, Temp = temperature, L = light, S = sound
    // vector<Point> points_TTemp;
    // vector<Point> points_TL;
    // vector<Point> points_TS;
    // vector<Point> points_TempL;
    // vector<Point> points_TempS;
    // vector<Point> points_LS;
    // a vector of vectors would make more sense
    

    // calls fileparser and populates the map and everything inside of it 
    fileParser(minMaxVectorMap, mapKeys, "data/smallsample400");

    for (string key : mapKeys) {
        kmeanMap[key] = new Kmean(get<0>(minMaxVectorMap[key]), numCentroids, get<1>(minMaxVectorMap[key]), get<2>(minMaxVectorMap[key]));
    }
    
    // Kmean* kmean_TTemp = new Kmean(get<0>(minMaxVectorMap["TimeTemp"]), numCentroids, get<1>(minMaxVectorMap["TimeTemp"]), get<2>(minMaxVectorMap["TimeTemp"]));
    // Kmean* kmean_TL = new Kmean(get<0>(minMaxVectorMap["TimeLight"]), numCentroids, get<1>(minMaxVectorMap["TimeLight"]), get<2>(minMaxVectorMap["TimeLight"]));
    // Kmean* kmean_TS = new Kmean(get<0>(minMaxVectorMap["TimeSound"]), numCentroids, get<1>(minMaxVectorMap["TimeSound"]), get<2>(minMaxVectorMap["TimeSound"]));
    // Kmean* kmean_TempL = new Kmean(get<0>(minMaxVectorMap["TempLight"]), numCentroids, get<1>(minMaxVectorMap["TempLight"]), get<2>(minMaxVectorMap["TempLight"]));
    // Kmean* kmean_TempS = new Kmean(get<0>(minMaxVectorMap["TempSound"]), numCentroids, get<1>(minMaxVectorMap["TempSound"]), get<2>(minMaxVectorMap["TempSound"]));
    // Kmean* kmean_LS = new Kmean(get<0>(minMaxVectorMap["LightSound"]), numCentroids, get<1>(minMaxVectorMap["LightSound"]), get<2>(minMaxVectorMap["LightSound"]));

    printVector(get<0>(minMaxVectorMap["TimeTemp"]));
    vector<Centroid> centroids = kmeanMap["TimeTemp"]->getCentroids();
    printVector(centroids);

    kmeanMap["TimeTemp"]->run(iteratons);
    centroids = kmeanMap["TimeTemp"]->getCentroids();
    printCentroidPoints(centroids);
    
    // for (string key : mapKeys) {
    //     kmeanMap[key]->run(iteratons);
    //     centroids = kmeanMap[key]->getCentroids();
    //     // printVector(points_TempS);
    //     // printVector(centroids_TimeTemp);
    //     printCentroidPoints(centroids);
    // }


    // kmean_TTemp.run(iteratons);
    // centroids_TTemp = kmean_TTemp.getCentroids();
    // graph results or maybe have kmean class do graphing internally, would probably make more sense

    // // data streaming 
    // dataStreamer();
    // points_TTemp.push_back(newPoint);
    // kmean_TTemp.run(5); 

    return 0;
}