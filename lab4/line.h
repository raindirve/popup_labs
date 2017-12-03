#pragma once

#include "point.h"


template<typename T>
struct Line {
	Line(const Point<T> & p1_ = Point<T>(), const Point<T> & p2_ = Point<T>(), bool segment_ = false) : p1(p1_), p2(p2_), segment(segment_) {}
	
	template<typename U>
	Line(const Line<U> & li) : p1(li.p1), p2(li.p2), segment(li.segment) {}

	template<typename U>
	operator Line<U>() {
		return Line<U>(p1, p2, segment);
	}

	template<typename U>
	Line & operator=(const Line<U> & li) {
		p1 = li.p1;
		p2 = li.p2;
		segment = li.segment;
		return *this;
	}

	Point<T> vec() const {
		return p2-p1;
	}

	Point<T> p1;
	Point<T> p2;
	bool segment;
};


template<typename T>
std::ostream & operator<<(std::ostream & os, const Line<T> & li) {
	os << "[" << li.p1 << ", " << li.p2 << "]";
	return os;
}

template<typename T>
double dist(const Line<T> & li, const Point<T> & p) {
	if (li.segment) {
		if (dot(p - li.p1, li.p2 - li.p1) < 0) {
			return dist(li.p1,p);
		} else if (dot(p - li.p2, li.p1 - li.p2) < 0) {
			return dist(li.p2, p);
		} else {
			return double(cross(p - li.p1, li.p2 - li.p1)) / dist(li.p1, li.p2);
		}
	} else {
		return double(cross(p - li.p1, li.p2 - li.p1)) / dist(li.p1, li.p2);
	}	
}


// -1 id means no intersect
template<typename T>
Point<double> intersect(const Line<T> & li1, const Line<T> & li2) {
	T denom = cross(li1.vec(),li2.vec());
	if (denom == 0) { // lines parallel, need to check if same
		if (cross(li1.vec(), li2.p1 - li1.p1) == 0) {
			// same line, need to check if overlap if segments
			if (!li1.segment && !li2.segment) {
				return li1.p1;
			} else if (li1.segment && !li2.segment) {
				return li1.p1;
			} else if (!li1.segment && li2.segment) {
				return li2.p1;
			} else { // both segments
				Point<T> v = li1.vec();
				T t1 = dot(li1.p1, v);
				T t2 = dot(li1.p2, v);
				T t3 = dot(li2.p1, v);
				T t4 = dot(li2.p2, v);

				//std::cout << v << " " << t1 << " " << t2 << " " << t3 << " " << t4 << "\n";

				if (!((t1 > t3 && t1 > t4) || (t1 < t3 && t1 < t4))) { // l1p1 inside l2
					return li1.p1;
				}

				if (!((t2 > t3 && t2 > t4) || (t2 < t3 && t2 < t4))) { // l1p2 inside l2
					return li1.p2;
				}

				if (!((t3 > t1 && t3 > t2) || (t3 < t1 && t3 < t2))) { // l2p1 inside l1
					return li2.p1;
				}

				if (!((t4 > t1 && t4 > t2) || (t4 < t1 && t4 < t2))) { // l2p2 inside l1
					return li2.p2;
				}

				// segments dont overlap
				return Point<double>(0, 0, -1);
			}
		} else { // parallel and dont overlap
			return Point<double>(0, 0, -1);
		}		
	}

	T numer = cross(li2.p1 - li1.p1, li2.vec());

	double t1 = double(numer) / denom;

	if (li1.segment) {
		if (t1 < 0 || t1 > 1) {
			return Point<double>(0, 0, -1);
		}
	}

	Point<double> p = li1.p1 + t1 * li1.vec();

	if (li2.segment) {
		T numer2 = cross(li1.p1 - li2.p1, li1.vec());
		double t2 = -double(numer2) / denom;
		if (t2 < 0 || t2 > 1) {
			return Point<double>(0, 0, -1);
		}
	}

	return p;
}
















