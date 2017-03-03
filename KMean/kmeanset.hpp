#ifndef __KMEANSET_HPP
#define __KMEANSET_HPP

#include <vector>

class KmeanSet {
public:
	KmeanSet();
	~KmeanSet();
	run();

	std::vector<Point> points;
	std::vector<Centroid> centroids;


	
};

#endif