#ifndef __CUBE__H__
#define __CUBE__H__
#include "geometry.h"

class cube : public geometry{
public:
	cube(double val):_length(val) {}
	double volume();
	double area();
private:
	double _length;
};

#endif
