ifndef __POINT_HPP
#define __POINT_HPP

#include <utility>
#include <iostream>
// #include "centroid.hpp"

namespace kmean {

class Centroid;

class Point {
public:
	Point(double x, double y);
	Point(const std::pair<double, double> loc);
	virtual ~Point();
	friend class Centroid;

	double computeDist(Centroid cent);

	bool operator==(const Point &other);
	bool operator!=(const Point &other);
	friend std::ostream& operator<< (std::ostream&, const Point&);


protected:
	const std::pair<double, double> loc;  
	Centroid cent;

};

}

#endif
