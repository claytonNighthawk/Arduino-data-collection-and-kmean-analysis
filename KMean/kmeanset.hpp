#ifndef __KMEAN_HPP
#define __KMEAN_HPP

#include <vector>

class Kmean {
public:
	Kmean();
	Kmean(int numCentroids, std::vector<Point> points);
	virtual ~Kmean();

	void addPoint(double x, double y);  // For eventual data streaming 
	void addCentroid(double x, double y);  
	void getPoints();
	void getCentroids();
	void run(int iteratons);

protected:
	std::vector<Point> points;
	std::vector<Centroid> centroids;	
};

#endif

// https://www.youtube.com/watch?v=_aWzGGNrcic