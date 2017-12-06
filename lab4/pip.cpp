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



	int n, m;
	std::cin >> n;
	while (n != 0) {
		llong x,y;
		Polygon<llong> polly;
		while(n--){
			std::cin >> x >> y;
			polly.add_point(x, y);
		}
		//~ std::cout << polly << "\n"; // cerr
		cin >> m;
		while(m--){
			std::cin >> x >> y;
			Point<llong> p(x, y);
			//~ std::cout << p; //cerr
			switch(point_in_polygon(polly, p)){
				case 2:
					cout << "in\n";
					break;
				case 1:
					cout << "on\n";
					break;
				case 0:
					cout << "out\n";
					break;
			}
			//~ polly.add_point(x, y);
		}
		
			
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