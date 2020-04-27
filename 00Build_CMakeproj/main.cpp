#include <iostream>
#include "include/cube.h"
#include "include/sphere.h"

using namespace std;

int main() {
	cout << "please input D:" << endl;
	double D = 0.0;
	cin >> D;
	cube c1(D);
	sphere s1(D);

	cout << "cube V: \t" << c1.volume() << endl;
	cout << "sphere V:\t" << s1.volume() << endl;

	return 0;
}
