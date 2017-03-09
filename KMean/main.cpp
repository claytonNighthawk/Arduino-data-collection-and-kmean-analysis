#include <vector>
#include <utility>
#include "kmean.hpp"
#include "centroid.hpp" 
#include "point.hpp"
//#include file parser / vector maker from chris

using namespace std:

int main() {
	int numCentroids = 6; 
	int iteratons = 20; // just a guess
	// T = time, Temp = temperature, L = light, S = sound
	vector<Point> points_TTemp;
	vector<Point> points_TL;
	vector<Point> points_TS;
	vector<Point> points_TempL;
	vector<Point> points_TempS;
	vector<Point> points_LS;
	// or maybe a vector of vectors or map of vectors

	// calls file parser on fileName and populates the vectors
	fileParser(fileName, &points_TTemp, &points_TL, &points_TS, &points_TempL, &points_TempS, &points_LS); 

	Kmean kmean_TTemp = new Kmean(numCentroids, points_TTemp);
	// And so on...

	kmean_TTemp.run(iteratons);
	centroids_TTemp = kmean_TTemp.getCentroids();
	// graph results or maybe have kmean class do graphing internally, would probably make more sense

	// data streaming 
	dataStreamer();
	points_TTemp.push_back(newPoint);
	kmean_TTemp.run(5); 

	return 0;
}