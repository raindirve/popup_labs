
#include "point.h"
#include "line.h"
#include "polygon_isct.h"
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef Point<double> P;
typedef Line<double> L;
typedef Polygon<double> Poly;
typedef long double ld;




int main(){
	
	double x,y;
	std::string s;
	P last_point;
	vector<P> square = {P(0,0), P(10,0), P(10,10), P(0, 10)};
	Poly field(square);
	while(cin >> x >> y >> s){
		
		P current(x,y);
		P midpoint = last_point + (current - last_point) / 2.0;
		//~ cerr << "Midpoint: " << midpoint << endl;
		P perpvec = perp(current-last_point);
		
		L line(midpoint, midpoint+perpvec);
		double d = dist(line,current);
		if(last_point == current){
			//~ cerr << "hello" << endl;
			if(s[0] != 'S'){
				field = Poly();
			} else{
				//noop
			}
		} else if(s[0] == 'S'){
			//~ cerr << "is it" << endl;
			field = Poly();
		}else{
			//~ cerr << "me yo'ure looking for" << endl;
			bool hot = (s[0] == 'H');
			
			if(d == 0){
				
			}else{
				if((d<0) == (hot)) {
					line = L(midpoint+perpvec, midpoint);
				}
			
				
				
				field = cut(field,line);
			}
		}
		
		cout << std::fixed << std::setprecision(6) << round(area(field)*1e6) / 1e6 << '\n';
		
		
		
		//~ cerr << field << '\n';
		
		last_point = current;
	}
}