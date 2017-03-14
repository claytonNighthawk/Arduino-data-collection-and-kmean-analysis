#ifndef __CENTROID_HPP
#define __CENTROID_HPP

#include <vector>
#include <utility>
#include <iostream>
// #include "minmaxvector.hpp"

namespace kmean {
typedef std::pair<double, double> Point;

class Centroid {

public:
	Centroid(); 
	Centroid(double x, double y);
	virtual ~Centroid();

	void setLocation(double x, double y);
	std::pair<double, double> getLocation();
	const std::vector<Point> getPoints();
	void addPoint(Point newP);
	void clearPoints(); 
	double computeDist(Point &point);
	void recalculate(); 

	bool operator== (const Centroid &other);
	bool operator!= (const Centroid &other);
	friend std::ostream& operator<<(std::ostream& os, const Centroid& cent);

protected:
	std::pair<double, double> loc;	
	std::vector<Point> points;
};

};
#endif