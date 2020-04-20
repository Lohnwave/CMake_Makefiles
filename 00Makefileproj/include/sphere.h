#ifndef __SPHERE__H_
#define __SPHERE__H_
#define PI 3.1415926
#include "geometry.h"

class sphere : public geometry{
public:
	sphere(double val):_length(val) {
		_r = _length/2;
	}
	double volume();
	double area();
private:
	double _r;
	double _length;
};
#endif
