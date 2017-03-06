#ifndef __POINT_HPP
#define __POINT_HPP

#include "centroid.hpp"
#include <utility>

class Point {
public:
	Point(double x, double y);
	virtual ~Point();
	friend class Centroid;


	double computeDist(Centroid cent);

protected:

	const std::pair<double, double> loc;  
	Centroid parent;

};

#endif