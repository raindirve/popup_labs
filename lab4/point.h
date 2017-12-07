#pragma once

#include <cmath>
#include <iostream>
// #include <cassert>
#define assert(x,i) if(!(x)) exit(i)
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>
#include <numeric>

using std::pair;
using std::vector;

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


//(-1, -1) fail state, i.e. only 1 points in set
//requires sequential IDs on points vector
// http://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
template<typename T>
std::pair<Point<T>, Point<T>> closest_pair(const std::vector<Point<T> > & points) {
	

	std::vector<Point<T>> xpoints = points;
	std::vector<int> ysorted(points.size());
	std::iota(ysorted.begin(), ysorted.end(), 0);

	std::sort(xpoints.begin(), xpoints.end());
	std::sort(ysorted.begin(), ysorted.end(),
		[&xpoints](const int & i, const int & j) -> bool {
			const Point<T> & lhs = xpoints[i], rhs = xpoints[j];
			return lhs.y < rhs.y || (!(rhs.y < lhs.y) && lhs.x < rhs.x);
		}
	);
	//std::sort(ypoints.begin(), ypoints.end(),
	//	[](const Point<T> & lhs, const Point<T> & rhs) -> bool {
	//		return lhs.y < rhs.y || (!(rhs.y < lhs.y) && lhs.x < rhs.x);
	//	}
	//);

	std::pair<Point<T>, Point<T>> rv = closest_pair(xpoints, ysorted);
	return rv;
}

template<typename T>
std::pair<Point<T>, Point<T>> closest_pair(const std::vector<Point<T> > & xpoints, const std::vector<int> & ysorted) {
	size_t n = xpoints.size();
	//std::cout << n << "\n";
	if(n < 4) { // brute force
		T best = dist2(xpoints[0], xpoints[1]); // know that n is at least 2.
		std::pair<int, int> best_idxs(0, 1);
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				T d = dist2(xpoints[i], xpoints[j]);
				if (d < best) {
					best_idxs.first = i;
					best_idxs.second = j;
					best = d;
				}
			}
		}
		//std::cout << "returning " << best << " " << best_idxs.first << " " << best_idxs.second << "\n";
		return std::pair<Point<T>, Point<T>>(xpoints[best_idxs.first], xpoints[best_idxs.second]);
	}

	int mid = n/2; // index of midpoint belongs to right
	//std::cout << n << " " << mid << "\n";

	std::vector<Point<T> > left_xpoints(xpoints.begin(), xpoints.begin() + mid);
	std::vector<Point<T> > right_xpoints(xpoints.begin() + mid, xpoints.end());

	std::vector<int> left_ypoints(mid);
	std::vector<int> right_ypoints(n-(mid));

	

	int lidx = 0;
	int ridx = 0;

	// sort ypoints to go left or right, based on x coordinate of mid point
	for (int i = 0; i < n; ++i) {
		if(ysorted[i] < mid) {
			left_ypoints[lidx] = ysorted[i];
			++lidx;
		} else {
			right_ypoints[ridx] = ysorted[i]-mid;
			++ridx;
		}
	}
	
	//std::cout << "n= " << n << "\n";
	//std::cout << "left split sizes " << left_xpoints.size() << " " << left_ypoints.size() << "\n";
	//std::cout << "right split sizes " << right_xpoints.size() << " " << right_ypoints.size() << "\n";

	assert(left_xpoints.size() == left_ypoints.size(),1);
	assert(right_xpoints.size() == right_ypoints.size(),2);

	int diff = std::abs(int(left_xpoints.size()) - int(right_xpoints.size()));
	assert(diff <= 1, 3);
	diff = std::abs(int(left_ypoints.size()) - int(right_ypoints.size()));
	assert(diff <= 1, 3);

	// get smallest dist on left side, and right side
	std::pair<Point<T>, Point<T>> left_result = closest_pair(left_xpoints,left_ypoints);
	std::pair<Point<T>, Point<T>> right_result = closest_pair(right_xpoints,right_ypoints);
	T lbest = dist2(left_result.first, left_result.second);
	T rbest = dist2(right_result.first, right_result.second);

	// record best pair
	std::pair<Point<T>, Point<T>> best_pair;
	T best;
	if(lbest < rbest) {
		best = lbest;
		best_pair = left_result;
	} else {
		best = rbest;
		best_pair = right_result;
	}

	// compare cross distances

	// get all points closer than best to middle line, sorted by y
	std::vector<Point<T>> overlap_strip;
	for (int i = 0; i < n; ++i) {
		if (sq(xpoints[ysorted[i]].x - xpoints[mid].x) < best) {
			overlap_strip.push_back(xpoints[ysorted[i]]);
		}
	}

	T best_overlap = best;
	int best_i;
	int best_j;
	for (int i = 0; i < overlap_strip.size(); ++i) {
		for (int j = i + 1; j < overlap_strip.size(); ++j) { // at most 6 times
			if(sq(overlap_strip[i].y - overlap_strip[j].y) >= best_overlap) {
				break; // y is sorted, so if this condition happens then we dont ahve to check rest of y
			} else {
				T d = dist2(overlap_strip[i], overlap_strip[j]);
				if (d < best_overlap) {
					best_overlap = d;
					best_i = i;
					best_j = j;
				}
			}
		}
	}

	if(best_overlap < best) {
		best_pair.first = overlap_strip[best_i];
		best_pair.second = overlap_strip[best_j];
	}

	//std::cout << "returning from " << n << " " << mid << "\n";
	return best_pair;

}