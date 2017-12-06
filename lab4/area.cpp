#include "point.h"
#include "line.h"
#include "polygon.h"
#include <iomanip>
#include <iostream>
#include <string>

typedef long long llong;

using std::cout;







int main() {



	int n;
	std::cin >> n;
	while (n != 0) {
		llong x,y;
		Polygon<llong> polly;
		while(n--){
			std::cin >> x >> y;
			polly.add_point(x, y);
		}
		
		
		double A = area(polly);
		bool cw = A < 0;
		if(cw) {
			A *= -1;
			cout << "CW ";
		} else{
			cout << "CCW ";
		}
		//~ cout << A << '\n';
		//std::cout << line1 << " " << line2 << "\n";
		std::cout << std::fixed << std::setprecision(1) << round(A*10)/10 << "\n";
		
		
		
		
		
		
		std::cin >> n;
	}


	return 0;
}