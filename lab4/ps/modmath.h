/**
 * Header for handling modular arithmetic in sizes up to max long long int/2.
 * Implements GCD, addition, subtraction, multiplication and division in modular space,
 * where the latter returns -1 iff the division is invalid (e.g. divisor is 0 or non-coprime with M.
 */
#pragma once

#include <cassert>
#include <cmath>

typedef long long llong;

template<typename T>
T mod(const T & a, const T & m) {
	return ((a % m) + m) % m;
}

struct GCD_result {
	GCD_result(llong gcd_ = 0, llong x_ = 0, llong y_ = 0) : gcd(gcd_), x(x_), y(y_) {}
	llong gcd;
	llong x;
	llong y;
};

// http://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
// x is a^-1 (mod b), y is b^-1 (mod a)
llong gcd_recursive(const llong & a, const llong & b, llong & x, llong & y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}

	llong x1, y1;
	llong g = gcd_recursive(b%a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return g;
}

GCD_result gcd(llong a, llong b) {
	GCD_result r;
	r.gcd = gcd_recursive(a, b, r.x, r.y);
	r.x = mod(r.x, b);
	r.y = mod(r.y, a);
	return r;
}

template<typename T> 
T sub_mod(const T & a, const T & b, const T & m) {
	return mod(a-b,m);
}


template<typename T> 
T add_mod(const T & a, const T & b, const T & m) {
	return mod(a+b,m);
}


// https://en.wikipedia.org/wiki/Ancient_Egyptian_multiplication#Russian_peasant_multiplication
template<typename T> 
T mult_mod(T a, T b, const T & m) {
	assert(a >= 0 && b >= 0);
	T ret=0;
	while(b) {
		if(b % 2 == 1) {
			ret = (ret + a) % m;
		}
		a = (a * 2) % m;
		b /= 2;
	}
	return mod(ret,m);	
}

template<typename T>
T div_mod(const T & a, const T & b, const T & m) {
	if (b == 0) return -1;
	GCD_result g = gcd(b,m);
	if (g.gcd != 1) {
		return -1;
	} else {
		assert(mult_mod(g.x, b, m) == 1);
		//std::cout << b << " inverse " << m << " : " << g.x << "\n";
		return mult_mod(a, g.x, m);
	}
}














