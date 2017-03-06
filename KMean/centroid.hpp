#ifndef __CENTROID_HPP
#define __CENTROID_HPP

#include <vector>
#include <utility>
#include "point.hpp"

class Centroid {

public:
	Centroid();
	Centroid(double x, double y);
	virtual ~Centroid();
	friend class Point;

	void setLocation(double x, double y);
	std::pair<double, double> getLocation();
	void addPoint(Point newP);
	void removePoint(Point oldP); 
	void recalculate(); 

	bool operator==(const MyClass &other);
	bool operator!=(const MyClass &other);

protected:
	std::pair<double, double> loc;	
	std::vector<Point> points;
};

#endif