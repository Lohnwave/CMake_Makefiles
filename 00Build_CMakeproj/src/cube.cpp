#include "../include/cube.h"

double cube::volume() {
	double vol = _length * _length * _length;
	return vol;
}

double cube::area() {
	double s = _length * _length * 6;
	return s;
}
