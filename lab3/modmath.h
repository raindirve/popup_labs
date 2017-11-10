#pragma once


#include <cmath>

typedef long long llong;


template<typename T>
T mod(const T & a, const T & m) {
	return ((a%m)+m)%m);
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
T mult_mod(const T & a, const T & b, const T & m) {
	T ret=0;
	while(b) {
		if(b % 2 == 1) {
			ret = (ret + a) % m;
		}
		a = (a * 2) % m;
		b /= 2;
	}
	return ret;	
}






















