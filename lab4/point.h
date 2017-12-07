#pragma once

#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>

typedef long long llong;


template<typename T>
T sq(const T & x){ return x*x; }

template<typename T>
struct Point {
	Point(const T & x_ = T(), const T & y_ = T(), int id_ = 0) : x(x_), y(y_), id(id_) {}

	template<typename U>
	Point(const Point<U> & p) : x(p.x), y(p.y), id(p.id) {}

	template<typename U>
	operator Point<U>() {
		return Point<U>(x,y,id);
	}

	template<typename U>
	Point & operator=(const Point<U> & p) {
		x = p.x;
		y = p.y;
		id = p.id;
		return *this;
	}

	Point<T> & operator+=(const Point<T> & other) {
		x += other.x;
		y += other.y;
		return *this;
	} 

	Point<T> & operator-=(const Point<T> & other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Point<T> & operator*=(const T & val) {
		x *= val;
		y *= val;
		return *this;
	}

	bool valid() const {
		return id >= 0;
	}

	operator bool() const {
		return valid();
	}

	T x;
	T y;
	int id;
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Point<T> & p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

template<typename T>
bool operator==(const Point<T> & lhs, const Point<T> & rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

template<typename T>
bool operator!=(const Point<T> & lhs, const Point<T> & rhs) {
	return !(lhs==rhs);
}

template<typename T>
bool operator<(const Point<T> & lhs, const Point<T> & rhs) {
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

template<typename T>
bool operator>(const Point<T> & lhs, const Point<T> & rhs) {
	return rhs < lhs;
}

template<typename T>
bool operator>=(const Point<T> & lhs, const Point<T> & rhs) {
	return !(lhs < rhs);
}

template<typename T>
bool operator<=(const Point<T> & lhs, const Point<T> & rhs) {
	return !(rhs < lhs);
}

template<typename T, typename U>
Point<double> operator+(Point<T> lhs, const Point<U> & rhs) {
	return Point<double>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
Point<T> operator+(Point<T> lhs, const Point<T> & rhs) {
	lhs += rhs;
	lhs.id = 0;
	return lhs;
}

template<typename T, typename U>
Point<double> operator-(Point<T> lhs, const Point<U> & rhs) {
	return Point<double>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template<typename T>
Point<T> operator-(Point<T> lhs, const Point<T> & rhs) {
	lhs -= rhs;
	lhs.id = 0;
	return lhs;
}

template<typename T>
T operator*(const Point<T> & lhs, const Point<T> & rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T, typename U>
Point<double> operator*(const Point<T> & lhs, const U & val) {
	return Point<double>(double(lhs.x) * val, double(lhs.y) * val, 0);
}

template<typename T>
Point<T> operator*(Point<T> lhs, const T & val) {
	lhs *= val;
	lhs.id = 0;
	return lhs;
}

template<typename T, typename U>
Point<double> operator*(const U & val, const Point<T> & rhs) {
	return rhs * val;
}

template<typename T>
Point<double> operator*(const T & val, const Point<T> & rhs) {
	return rhs * val;
}

template<typename T, typename U>
Point<double> operator/(const Point<T> & lhs, const U & val) {
	return Point<double>(double(lhs.x) / double(val), double(lhs.y) / double(val), 0);
}

template<typename T>
T dot(const Point<T> & lhs, const Point<T> & rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T>
T cross(const Point<T> & lhs, const Point<T> & rhs) {
	return lhs.x * rhs.y - rhs.x * lhs.y;
}

template<typename T>
double area(const Point<T> & p1, const Point<T> & p2, const Point<T> & p3) {
	return double(cross(p2-p1,p3-p1)) / 2;
}

template<typename T>
double angle(const Point<T> & p) {
	//~ assert(p.x != 0 || p.y != 0);
	return atan2(p.y,p.x);
}

template<typename T>
double angle(const Point<T> & p1, const Point<T> & p2) {
	return atan2(cross(p1,p2),dot(p1,p2));
}

template<typename T>
T length2(const Point<T> & p) {
	return p.x * p.x + p.y * p.y;
}

template<typename T>
double length(const Point<T> & p) {
	return sqrt(double(length2(p)));
}

template<typename T>
T dist2(const Point<T> & p1, const Point<T> & p2) {
	return length2(p1-p2);
}

template<typename T>
double dist(const Point<T> & p1, const Point<T> & p2) {
	return sqrt(double(dist2(p1,p2)));
}

template<typename T>
double norm(const Point<T> & p) {
	return length(p);
}

template<typename T>
Point<double> normalize(const Point<T> & p) {
	return p / norm(p);
}

template<typename T>
Point<T> perp(const Point<T> & p) {
	return Point<T>(-p.y, p.x);
}

//(-1, -1) fail state, i.e. only 1 points in set
//requires sequential IDs on points vector
// http://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
template<typename T>
std::pair<int, int> closest_pair(const std::vector<Point<T> > & points, const std::vector<int> & ysorted, size_t from, size_t to) {
	if(from+1 == to) return std::pair<int, int>(-1, -1);
	
	if(points[from].x == points[to-1].x){
		//linear stepping
		T best_d = dist2(points[from], points[from+1]);
		T d;
		int best_idx = from;
		for(int i = from+1; i < to-1; ++i){
			d = dist2(points[i], points[i+1]);
			if(d < best_d) {
				best_d = d;
				best_idx = i;
			}
			
		}
		return std::pair<int,int>(best_idx,best_idx+1); 
	}
	else{
		int one_past_mid = to - (to-from)/2;
		
		std::pair<int, int> left = closest_pair(points, from, one_past_mid);
		std::pair<int, int> right = closest_pair(points, one_past_mid, to);
		T lbest = dist2(points[left.first], points[left.second]);
		T rbest = dist2(points[right.first], points[right.second]);
		T best = std::min(lbest, rbest);
		
		//~ //binsrch all x f.w. x+best on right side
		//~ int hi = one_past_mid;
		//~ int lo = from;
		
		
		
		
		//~ T target = points[one_past_mid].x;
		//~ while(lo < hi) {
			//~ int mid = lo + (hi-lo)/2;
			//~ if(sq(target - points[mid].x) < best) hi = mid;
			//~ else lo = mid + 1;
		//~ }
		//~ int lstart = lo;
		
		//~ lo = from + (to-from)/2;
		//~ hi = to;
		
		//~ target = points[one_past_mid-1].x;
		//~ while(lo < hi) {
			//~ int mid = lo + (hi-lo)/2;
			//~ if(sq(target - points[mid].x) >= best) hi = mid;
			//~ else lo = mid + 1;
		//~ }
		//~ int rend = lo;
		
		//~ std::vector<int> rstrip(rend-(one_past_mid));
		//~ std::iota(rstrip.begin(), rstrip.end(), one_past_mid);
		
		//~ std::sort(rstrip.begin(), rstrip.end(), 
			//~ [&points] (const int & i, const int & j) -> bool {
				//~ const Point & lhs = points[i], rhs = points[j];
				//~ return lhs.y < rhs.y || (!(rhs.y < lhs.y) && lhs.x < rhs.x);
			//~ }
		//~ );
		
		std::vector<int> lstrip();//(one_past_mid)-lstart);
		lstrip.reserve(to-from);
		std::vector<int> rstrip();//(one_past_mid)-lstart);
		rstrip.reserve(to-from);
		//~ std::iota(lstrip.begin(), lstrip.end(), lstart);
		
		T target = points[one_past_mid].x;
		for(auto a & : ysorted){
			if(sq(points[a].x - target) < best){
				if(a < one_past_mid)lstrip.push_back(a);
				else rstrip.push_back(a);
			}
		}
		
		int rstart = 0, rend = 0;
		
		for(auto a & : lstrip){
			
		}
		
		
		//~ std::sort(lstrip.begin(), lstrip.end(), 
			//~ [&points] (const int & i, const int & j) -> bool {
				//~ const Point & lhs = points[i], rhs = points[j];
				//~ return lhs.y < rhs.y || (!(rhs.y < lhs.y) && lhs.x < rhs.x);
			//~ }
		//~ );		
		
		
		
	}
	
}

template<typename T>
std::pair<int, int> closest_pair(std::vector<Point<T> > points) {
	std::sort(points.begin(), points.end());
	std::vector<int> ysorted(points.size());
	std::iota(ysorted.begin(),ysorted.end(),0);
	std::sort(ysorted.begin(),ysorted.end(), 
		[&points] (const int & i, const int & j) -> bool {
			const Point & lhs = points[i], rhs = points[j];
			return lhs.y < rhs.y || (!(rhs.y < lhs.y) && lhs.x < rhs.x);
		}
	);
	
	
	closest_pair(points,ysorted, 0, points.size());
}



template<typename T>
int colinear(const std::vector<Point<T>> & points) {
	if (points.size() < 3) {
		return int(points.size());
	}
	
	int nmax = 0;
	for (int i = 0; i < points.size(); ++i) {
		std::unordered_map<double, int> angles;
		angles.reserve(points.size()-i);
		for (int j = i + 1; j < points.size(); ++j) {
			double theta = angle(points[j] - points[i]);
			if (theta < 0) {
				theta = angle(points[i] - points[j]);
			}

			//std::cout << "angle " << points[i] << " " << points[j] << " " << theta << "\n";

			if (angles.count(theta) > 0) {
				angles[theta] += 1;
			} else {
				angles[theta] = 2;
			}
		}

		
		for (auto & kv : angles) {
			nmax = std::max(nmax, kv.second);
		}
	}

	return nmax;
}


