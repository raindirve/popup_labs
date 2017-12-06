#include "point.h"
#include "line.h"
#include "polygon.h"
#include <iomanip>
#include <iostream>
#include <string>

typedef long long llong;

using std::cout;
using std::cin;







int main() {
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);


	int n, m;
	std::cin >> n;
	while (n != 0) {
		Polygon<llong> polly;
		while(n-->0){
			llong x1,y1;//,x2,y2;
			std::cin >> x1 >> y1;// >> x2 >> y2;
			polly.add_point(x1, y1);
		}
		
		Polygon<llong> hull = convex_hull(polly);
		
		std::cout << hull.n_points() << "\n";
		for(int i = 0; i<hull.n_points(); ++i) {
			std::cout << hull.points[i].x << " " << hull.points[i].y << "\n";
		}
		
		
		//~ if(isct.id == -1) {
			//~ std::cout << "none\n";
		//~ } else if(isct.singular()) {
			//~ std::cout <<  std::fixed << std::setprecision(2) << round(isct.p1.x * 100)/100 << " " << round(isct.p1.y * 100)/100 << "\n";
		//~ } else {
			//~ std::cout <<  std::fixed << std::setprecision(2) << round(isct.p1.x * 100)/100 << " " << round(isct.p1.y * 100)/100 << " " << round(isct.p2.x * 100)/100 << " " << round(isct.p2.y * 100)/100 << "\n";
		//~ }
			
		//~ cout << A << '\n';
		//std::cout << line1 << " " << line2 << "\n";
		//~ std::cout << std::fixed << std::setprecision(1) << round(A*10)/10 << "\n";
		
		
		
		
		
		
		std::cin >> n;
	}
	
	
	//~ Point<int> a(8,-3);
	//~ Point<int> b1(9,-2);
	//~ Point<int> b2(8,-2);
	//~ Point<int> b3(-1,1);
	//~ Point<int> b4(-1,-1);
	//~ std::cout << "agle betewen " << b1-a << "," << b2-a << " : " << angle(b1-a, b2-a) << "\n";
	//~ std::cout << "agle betewen " << b2-a << "," << b1-a << " : " << angle(b2-a, b1-a) << "\n";


	return 0;
}