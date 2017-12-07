
#include "polygon.h"
#include <iostream>
#include <vector>









int main() {
	int n;
	std::cin >> n;
	while (n != 0) {
		std::vector<Point<llong>> pts;
		pts.reserve(n);
		while (n --> 0) {
			Point<llong> p;
			std::cin >> p.x >> p.y;
			pts.push_back(p);
		}

		std::cout << colinear(pts) << "\n";

		std::cin >> n;
	}





	return 0;
}





