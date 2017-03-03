#ifndef __POINT_HPP
#define __POINT_HPP

#include "centroid.hpp"

class Point {
public:
	Point(int, int);
	virtual ~Point();
	const std::pair<int, int> loc;  // Making these public data memebers since it is simple  
	Centroid parent;  				// and 4 getter/setters would be too much 
};

#endif