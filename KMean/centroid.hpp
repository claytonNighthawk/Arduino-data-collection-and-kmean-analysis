#ifndef __CENTROID_HPP
#define __CENTROID_HPP

#include <vector>
#include <utility>
#include <iostream>

namespace kmean {
typedef std::pair<double, double> Point; // Const?
// What happens if I have std::pair<double, double> that isnt a "Point"? 
// Since they are functionally the same it shouldn't matter, anything I declare as 
// std::pair<double, double> is just a plain location where as Point has more meaning attached to it

class Centroid {

public:
	Centroid(); 
	Centroid(double x, double y);
	virtual ~Centroid();

	void setLocation(double x, double y);
	std::pair<double, double> getLocation();
	void addPoint(Point newP);
	void removePoint(Point oldP); 
	double computeDist(Point point);
	void recalculate(); 

	bool operator==(const Centroid &other);
	bool operator!=(const Centroid &other);
	friend std::ostream& operator<< (std::ostream&, const Centroid&);

protected:
	std::pair<double, double> loc;	
	std::vector<Point> points;
};

}
#endif