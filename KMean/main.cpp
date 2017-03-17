#include <vector>
#include <utility>        // std::pair
#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include "kmean.hpp"
#include "centroid.hpp" 
#include "fileparser.hpp" // fileparser from chris
#include "gnuplot-iostream.h"

using namespace kmean;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::tuple;
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
    vector<Point> points;
    for (unsigned int i = 0; i < centroids.size(); ++i) {
        points = centroids[i].getPoints();
        cout << "Centroid " << i << " @ " << centroids[i] << " : ";
        printVector(points);
    }
}


void graphIt(vector<Centroid> &centroids) {
  vector<Point> points;
  vector<Point> centroid;
  int pt = 12;
  //Gnuplot gp("tee plot.gnu");
  Gnuplot gp;    
  
  //gp << "set zrange [-1:1]\n";      
  gp << "plot ";
  
  //build the command
  for (unsigned int i = 0; i < centroids.size(); ++i) {
    // graph data in smaller points	
    gp <<  "'-' with points ps 1 pt "<<pt <<" title 'points " << i <<"'";
   
    // graph centriod in large point
    gp << ", ";
    gp <<  "'-' with points ps 3 pt "<<pt <<" title 'centriod " << i << "',";
    pt++;  //iterate to next point style
  }	
  gp << "\n";
  // send the data	
  for (unsigned int x = 0; x < centroids.size(); ++x) {
    points = centroids[x].getPoints();
    centroid.push_back(centroids[x].getLocation());
    
    gp.send1d(points);
    gp.send1d(centroid);
    
    //remove last centroid
    centroid.pop_back();
    
  }
  
}


// for data streaming, adding points on the fly. 
// void addPoint(map<string, tuple<vector<Point>, double, double>> minMaxVectorMap, Point p, string dataSet) { 

// }

int main() {
    int numCentroids = 3; 
    int iteratons = 5; 
    vector<string> mapKeys = {"TimeTemp", "TimeLight", "TimeSound", "TempLight", "TempSound", "LightSound"};
    map<string, tuple<vector<Point>, double, double>> minMaxVectorMap;
    map<string, Kmean*> kmeanMap;

    // calls fileparser and populates the map and everything inside of it 
    fileParser(minMaxVectorMap, mapKeys, "data/singlesensor");
    vector<Centroid> centroids;

    // Create and run Kmeans
    for (string key : mapKeys) {
        kmeanMap[key] = new Kmean(get<0>(minMaxVectorMap[key]), numCentroids, get<1>(minMaxVectorMap[key]), get<2>(minMaxVectorMap[key]));
        cout << key << endl;
        kmeanMap[key]->run(iteratons);
        centroids = kmeanMap[key]->getCentroids();
        // printVector(get<0>(minMaxVectorMap[key]));
        // printVector(centroids_TimeTemp);
        printCentroidPoints(centroids);
	graphIt(centroids);

	// Then graph the results or more interesting graph them as the method runs



	// Don't forget to put "\n" at the end of each line!
	//gp << "set xrange [0:2000]\nset yrange [0:2000]\n";
	// '-' means read from stdin.  The send1d() function sends data to
	// gnuplot's stdin.
	//gp << "plot '-' with vectors title 'points' "
	// << "'-' with vectors title 'centriods'\n";
	//gp.send1d(kmeanMap[key]);
	//gp.send1d(centroids);
  
  
    }




    
    // Deallocate kmeanMap
    for (string key : mapKeys) {
        delete kmeanMap[key];
    }

    return 0;
}
