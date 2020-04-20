#include "../include/sphere.h"

double sphere::volume() {
	double vol = (4/3) * PI * _r * _r * _r;
	return vol;
}

double sphere::area() {
	double s = 4 * PI * _r * _r;
	return s;
}
