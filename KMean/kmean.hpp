#ifndef __KMEAN_HPP
#define __KMEAN_HPP

#include <vector>
#include <utility>
#include "centroid.hpp" 
#include "point.hpp"


class Kmean {
public:
	// Kmean();
	Kmean(int numCentroids, std::vector<Point> &points);
	virtual ~Kmean();

	// void addPoint(double x, double y);  // For eventual data streaming, done externally? 
	void addCentroid(double x, double y);  
	void getCentroids();
	void run(int iteratons);
	// void graph(); ?

protected:
	std::vector<Point> points;
	std::vector<Centroid> centroids;	
};

#endif

// https://www.youtube.com/watch?v=_aWzGGNrcic