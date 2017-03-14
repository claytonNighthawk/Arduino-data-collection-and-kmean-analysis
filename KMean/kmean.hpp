#ifndef __KMEAN_HPP
#define __KMEAN_HPP

#include <vector>
#include <utility>
#include "centroid.hpp" 
#include "minmaxvector.hpp"

namespace kmean {

class Kmean {
public:
	Kmean(std::vector<Point> &points, int numCentroids, double min, double max);
	virtual ~Kmean();

	void addCentroid(double x, double y);  
	std::vector<Centroid> getCentroids();
	void run(int iteratons);
	// void graph(); ?

protected:
	std::vector<Point> points;
	std::vector<Centroid> centroids;	
};

}

#endif

// https://www.youtube.com/watch?v=_aWzGGNrcic