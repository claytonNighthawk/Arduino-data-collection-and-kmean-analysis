// https://www.youtube.com/watch?v=_aWzGGNrcic

#ifndef __CENTROID_HPP
#define __CENTROID_HPP

#include <vector>
#include <utility>
#include "point.hpp"

class Centroid {

public:
	Centroid();
	virtual ~Centroid();
	void setLocation();

	void addPoint();
	void removePoint();
	std::vector<Point> getPoints();

protected:
	std::vector<Point> points;
	std::pair<double, double> loc;	
};

#endif