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
    cout << endl;
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

// void clearVectorMap(map<string, tuple<vector<Point>, double, double>>& minMaxVectorMap) {
//     for (auto it = minMaxVectorMap.begin(), it != minMaxVectorMap.end(); it++) {
//         delete it->first;
//         delete[] get<0>(it->second);
        
//     }

// }

int main() {
    int numCentroids = 10; 
    int iteratons = 2; 
    map<string, tuple<vector<Point>, double, double>> minMaxVectorMap;
    vector<string> mapKeys = {"TimeTemp", "TimeLight", "TimeSound", "TempLight", "TempSound", "LightSound"};
    map<string, Kmean*> kmeanMap;

    // calls fileparser and populates the map and everything inside of it 
    fileParser(minMaxVectorMap, mapKeys, "data/smallsample400");

    for (string key : mapKeys) {
        kmeanMap[key] = new Kmean(get<0>(minMaxVectorMap[key]), numCentroids, get<1>(minMaxVectorMap[key]), get<2>(minMaxVectorMap[key]));
    }

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



    return 0;
}