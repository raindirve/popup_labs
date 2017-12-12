
#include "point.h"
#include "line.h"
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef Point<double> P;
typedef Line<double> L;
typedef long double ld;

bool in_circle(P & p,double & r) {
	return length2(p) <= sq(r);
}

double dist2_to_x(P & from, P & to, P & mid) {
	return dist2(from,mid) + dist2(mid,to);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	double r, x,y,X,Y;
	cin >> r >> x >> y >> X >> Y;
	while(r >= 0){
		P start = P(x,y), target = P(X,Y);
		
		//~ P diff = target - start;
		//~ L h, d;
		//~ L sh, sd;
		//~ if(std::abs(dist.x) > std::abs(dist.y)){
			//~ //right-left sector - horizontal line
			
		//~ } else {
			
		//~ }
		L start_h(start, start+P(1,0));
		L start_v(start, start+P(0,1));
		
		L start_r(start, start+P(1,1));
		L start_l(start, start+P(-1,1));
		
		L target_h(target, target+P(1,0));
		L target_v(target, target+P(0,1));
		
		L target_r(target, target+P(1,1));
		L target_l(target, target+P(-1,1));
		
		L ict = L(0,0,0,0,-1);
		
		double mindist2 = 999999999999999;
		P midpoint;
		
		ict = intersect(start_h,target_r);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_h,target_l);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_v,target_r);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_v,target_l);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_r,target_h);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_r,target_v);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_l,target_h);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		
		ict = intersect(start_l,target_v);
		
		if(in_circle(ict.p1,r)) {
			double d = dist2_to_x(start,target,ict.p1);
			if(d < mindist2) {
				//~ cerr << "New midpoint!" << endl;
				mindist2 = d;
				midpoint = ict.p1;
			}
		}
		//~ cerr << midpoint << endl;
		P diff = midpoint - start;
		double d = length(diff);
		if(d > 1e-10){
			// check if horizontal or diag
			if(std::abs(std::abs(diff.x) - std::abs(diff.y)) < 1e-10) {
				if(diff.x > 0 && diff.y > 0) {
					std::cout << std::fixed << std::setprecision(10) << "northeast " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x < 0 && diff.y > 0) {
					std::cout << std::fixed << std::setprecision(10) << "northwest " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x < 0 && diff.y < 0) {
					std::cout << std::fixed << std::setprecision(10) << "southwest " << round(d*1e10)/1e10 << "\n";
				} else {
					std::cout << std::fixed << std::setprecision(10) << "southeast " << round(d*1e10)/1e10 << "\n";
				}		
				
			} else { // str
				
				if(diff.x > 1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "east " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x <-1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "west " << round(d*1e10)/1e10 << "\n";
				} else if (diff.y < 1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "south " << round(d*1e10)/1e10 << "\n";
				} else {
					std::cout << std::fixed << std::setprecision(10) << "north " << round(d*1e10)/1e10 << "\n";
				}					
			}
			
			
		}
		
		diff = target-midpoint;
		d = length(diff);
		if(d > 1e-10){
			// check if horizontal or diag
			if(std::abs(std::abs(diff.x) - std::abs(diff.y)) < 1e-10) {
				if(diff.x > 0 && diff.y > 0) {
					std::cout << std::fixed << std::setprecision(10) << "northeast " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x < 0 && diff.y > 0) {
					std::cout << std::fixed << std::setprecision(10) << "northwest " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x < 0 && diff.y < 0) {
					std::cout << std::fixed << std::setprecision(10) << "southwest " << round(d*1e10)/1e10 << "\n";
				} else {
					std::cout << std::fixed << std::setprecision(10) << "southeast " << round(d*1e10)/1e10 << "\n";
				}		
				
			} else { // str
				
				if(diff.x > 1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "east " << round(d*1e10)/1e10 << "\n";
				} else if (diff.x < -1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "west " << round(d*1e10)/1e10 << "\n";
				} else if (diff.y < -1e-10) {
					std::cout << std::fixed << std::setprecision(10) << "south " << round(d*1e10)/1e10 << "\n";
				} else {
					std::cout << std::fixed << std::setprecision(10) << "north " << round(d*1e10)/1e10 << "\n";
				}					
			}
		}
		std::cout<<"\n";

		cin >> r >> x >> y >> X >> Y;
	}
	
}