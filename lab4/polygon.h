#pragma once

#include "point.h"
#include "line.h"
#include <vector>
#include <algorithm>
#include <utility>

template<typename T>
struct Polygon {
	Polygon(int id_ = 0) : id(id_) {};
	Polygon(const std::vector<Point<T>> & pts, int id_ = 0) : points(pts), id(id_) {};

	void add_point(const Point<T> & p) {
		points.push_back(p);
	}

	size_t n_points() const {
		return points.size();
	}

	bool is_simple() const {
		// TODO
		return true;
	}

	std::vector<Point<T>> points;
	int id;
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Polygon<T> & poly) {
	os << poly.id << ": {";
	for (int i = 0; i < poly.n_points(); ++i) {
		os << "\t" << poly.points[i] << "\n";
	}
	os << "}";
	return os;
}

template<typename T>
double area(const Polygon<T> & poly) {
	if(poly.points.size() < 3) return 0;

	double A = 0;
	for (int i = 0; i < poly.points.size()-1; ++i) {
		A += cross(poly.points[i], poly.points[i+1]);
	}
	A += cross(poly.points.back(), poly.points.front());
	return A/2;
}

template<typename T>
bool point_in_polygon(const Polygon<T> & poly, const Point<T> & p) {
	double sum = 0;
	for (int i = 0; i < poly.points.size() - 1; ++i) {
		if (dist(Line<T>(poly.points[i], poly.points[i + 1], true), p) == 0) { // check if point on line
			return true;
		}
		sum += angle(poly.points[i]-p, poly.points[i + 1]-p);		
	}
	if (dist(Line<T>(poly.points.back(), poly.points.front(), true), p) == 0) {
		return true;
	}
	sum += angle(poly.points.back()-p, poly.points.front()-p);
	//std::cout << sum << "\n";
	return sum > 3.14;
}

template<typename T>
Polygon<T> convex_hull(const Polygon<T> & poly) {
	if(poly.n_points() < 3) return poly;

	std::vector<std::pair<Point<T>, double > > angles;
	angles.reserve(poly.points.size());
	for (int i = 0; i < poly.points.size(); ++i) {
		angles.push_back(std::pair<Point<T>, double >(poly.points[i], 0));
	}
	std::sort(angles.begin(), angles.end()); // sort by x	

	Point<T> anchor = angles[0].first;


	for (int i = 1; i < angles.size(); ++i) {
		angles[i].second = angle(angles[i].first - anchor);
	}

	std::sort(angles.begin()+1,angles.end(),
		[&anchor](const std::pair<Point<T>, double > & p1, const std::pair<Point<T>, double > & p2) -> bool { // sort by angle, then by dist to anchor
			if (p1.second != p2.second) {
				return p1.second < p2.second;
			} else {
				return dist2(p1.first,anchor) < dist2(p2.first,anchor);
			}
		}
	);

	std::vector<Point<T>> good_pts;
	good_pts.reserve(angles.size());
	good_pts.push_back(anchor);
	for (int i = 1; i < angles.size(); ++i) {
		while ((i < angles.size() - 1) && (angles[i].second == angles[i + 1].second)) {
			++i;
		}
		good_pts.push_back(angles[i].first);
	}

	if(good_pts.size() < 3) return good_pts;

	std::vector<Point<T>> stack;
	stack.reserve(good_pts.size());

	stack.push_back(good_pts[0]);
	stack.push_back(good_pts[1]);
	stack.push_back(good_pts[2]);

	for (int i = 3; i < good_pts.size(); ++i) {
		while (dist(Line<T>(stack[stack.size() - 2], stack[stack.size() - 1]), good_pts[i]) >= 0) {
			stack.pop_back();
		}
		stack.push_back(good_pts[i]);
	}

	return Polygon<T>(stack);
}



















