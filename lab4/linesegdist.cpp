#include "point.h"
#include "line.h"
#include "polygon.h"
#include <iomanip>










int main() {

	/*std::cout << Point<double>(1.1, 2.2) * 2 << "\n";
	std::cout << 2 * Point<double>(1.1, 2.2) << "\n";
	std::cout << 2 * Point<int>(1, 2) << "\n";
	std::cout << Point<int>(1, 2) * 2 << "\n";
	std::cout << Point<int>(1, 2) * 1.1 << "\n";
	std::cout << 1.1 * Point<int>(1, 2) << "\n";
	std::cout << Point<int>(1.1, 2) + Point<int>(1, 2) << "\n";
	std::cout << Point<double>(1.1, 2) + Point<int>(1, 2) << "\n";
	std::cout << Point<int>(1.1, 2) - Point<int>(1, 2) << "\n";
	std::cout << Point<double>(1.1, 2) - Point<int>(1, 2) << "\n";*/

	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2)), Line<int>(Point<int>(2, 1), Point<int>(1, 2))) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2)), Line<int>(Point<int>(4, 3), Point<int>(3, 4))) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(4, 3), Point<int>(3, 4), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(4, 3), Point<int>(3, 4), false)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(4, 3), Point<int>(3, 4), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(4, 3), Point<int>(3, 4), false)) << "\n";

	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(3, 1), Point<int>(2, 2), false)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(3, 1), Point<int>(2, 2), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(3, 1), Point<int>(2, 2), false)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(3, 1), Point<int>(2, 2), true)) << "\n";


	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(3, 3), Point<int>(4, 4), false)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Line<int>(Point<int>(3, 3), Point<int>(4, 4), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(3, 3), Point<int>(4, 4), false)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Line<int>(Point<int>(3, 3), Point<int>(4, 4), true)) << "\n";

	//std::cout << intersect(Line<int>(Point<int>(1, 1), Point<int>(4, 4), true), Line<int>(Point<int>(3, 3), Point<int>(2, 2), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(4, 4), Point<int>(2, 2), true), Line<int>(Point<int>(1, 1), Point<int>(3, 3), true)) << "\n";
	//std::cout << intersect(Line<int>(Point<int>(4, 4), Point<int>(2, 2), true), Line<int>(Point<int>(3, 3), Point<int>(1, 1), true)) << "\n";
	
	
	//std::cout << dist(Line<int>(Point<int>(1, 1), Point<int>(2, 2), true), Point<int>(0, 1)) << "\n";
	//std::cout << dist(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Point<int>(0, 1)) << "\n";
	//std::cout << dist(Line<int>(Point<int>(1, 1), Point<int>(2, 2), false), Point<int>(1, 0)) << "\n";
	//
	//Polygon<double> poly;
	//poly.add_point(Point<double>(1, 1));
	//poly.add_point(Point<double>(2, 1));
	//poly.add_point(Point<double>(2, 2));
	//poly.add_point(Point<double>(1, 2));

	//std::cout << area(poly) << "\n";

	//Point<double> p;

	//p = Point<double>(1.5, 1.5);
	//std::cout << point_in_polygon(poly, p) << "\n";
	//p = Point<double>(2.5, 2.5);
	//std::cout << point_in_polygon(poly, p) << "\n";

	//Polygon<double> poly;
	//poly.add_point(Point<double>(1, 1));
	//poly.add_point(Point<double>(2, 1));
	//poly.add_point(Point<double>(3, 1));
	//poly.add_point(Point<double>(4, 1));
	//poly.add_point(Point<double>(2, 2));
	//poly.add_point(Point<double>(4, 2));
	//poly.add_point(Point<double>(4, 3));
	//poly.add_point(Point<double>(4, 4));
	//poly.add_point(Point<double>(3, 3));
	//poly.add_point(Point<double>(2, 4));

	//std::cout << poly << "\n";

	//std::cout << convex_hull(poly) << "\n";



	int n;
	std::cin >> n;
	while (n--) {
		llong x1,y1,x2,y2,x3,y3,x4,y4;
		std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		Line<llong> line1(Point<llong>(x1, y1), Point<llong>(x2, y2), true);
		Line<llong> line2(Point<llong>(x3, y3), Point<llong>(x4, y4), true);
		//std::cout << line1 << " " << line2 << "\n";
		std::cout << std::fixed << std::setprecision(2) << round(dist(line1,line2)*100)/100 << "\n";
	}


	return 0;
}