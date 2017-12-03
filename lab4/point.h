#pragma once

#include <cmath>
#include <iostream>

typedef long long llong;


template<typename T>
struct Point {
	Point(const T & x_ = T(0), const T & y_ = T(0), int id_ = 0) : x(x_), y(y_), id(id_) {}

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










