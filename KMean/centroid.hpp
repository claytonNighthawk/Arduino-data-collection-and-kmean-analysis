#ifndef __CENTROID_HPP
#define __CENTROID_HPP

#include <vector>
#include <utility>
#include <iostream>

namespace kmean {
typedef std::pair<double, double> Point;
// Since pair<double, double> and Point are functionally the same anything I declare as 
// pair<double, double> is just a plain location where as Point has more meaning attached

class Centroid {

public:
	Centroid(); 
	Centroid(double x, double y);
	virtual ~Centroid();

	void setLocation(double x, double y);
	std::pair<double, double> getLocation();
	void addPoint(Point* newP);
	void clearPoints(); 
	double computeDist(Point* point);
	void recalculate(); 

	bool operator== (const Centroid &other);
	bool operator!= (const Centroid &other);
	friend std::ostream& operator<<(std::ostream& os, const Centroid& cent);

protected:
	std::pair<double, double> loc;	
	std::vector<Point*> pointsPTR;
};

};
#endif