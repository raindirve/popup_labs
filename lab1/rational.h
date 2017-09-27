#ifndef ___RATIONAL___
#define ___RATIONAL___

#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>


typedef long long llong;

/**
 * Returns the GCD of parametrized type.
 * Implemented here because stdlib version
 * inconsistent between platforms.
 */
template<typename T>
T gcd(T a, T b) {
	if (a == 0) return b;
	return gcd(b % a , a);
}

/**
 * Absolute value.
 */
template<typename T>
T absval(const T & val) {
	return val<0 ? -val : val;
}


template<typename T>
struct Rational {
        /**
         * default initializer 0 = 0/1
	 */
        Rational() {
		numer = 0;
		denom = 1;
	}
        /**
         * Constructs as (n/d)
         */
	Rational(T n_, T d_) {
		if (d_ < 0) {
			numer = -n_;
			denom = -d_;
		} else {
			numer = n_;
			denom = d_;
		}
		reduce();
	}
  
        /**
	 * Sets to the whole number, i.e. num = (num/1).
	 */
	Rational(T num) {
		numer = num;
		denom = 1;
	}

        /**
         * Reduces the fraction to the simplest possible fraction.
         */
	Rational & reduce() {
		if (numer == 0) {
			denom = 1;
			return *this;
		}

		T my_gcd = gcd<T>(absval(numer), absval(denom));

		if (my_gcd != 0) {
			numer /= my_gcd;
			denom /= my_gcd;
		}

		if (denom < 0) {
			denom = -denom;
			numer = -numer;
		}

		return *this;
	}

	Rational & operator+=(const Rational & b) {
		numer = numer * b.denom + b.numer * denom;
		denom = denom * b.denom;
		if (denom != 0) reduce();
		return *this;
	}

	Rational & operator+=(T a) {
		numer += denom * a;
		if (denom != 0) reduce();
		return *this;
	}

	Rational & operator-=(const Rational & b) {
		numer = numer * b.denom - b.numer * denom;
		denom = denom * b.denom;
		if (denom != 0) reduce();
		return *this;
	}

	Rational & operator-=(T a) {
		numer -= denom * a;
		if (denom != 0) reduce();
		return *this;
	}

	Rational & operator*=(const Rational & b) {
		numer *= b.numer;
		denom *= b.denom;
		if (denom != 0) reduce();
		return *this;
	}

	Rational & operator/=(const Rational & b) {
		numer *= b.denom;
		denom *= b.numer;
		if (denom != 0) reduce();
		return *this;
	}



	Rational operator-() const {
		return Rational(-numer, denom);
	}

	friend bool operator==(const Rational & a, const Rational & b) { return (a - b).numer == 0; }
	friend bool operator!=(const Rational & a, const Rational & b) { return !(a == b); }
	friend bool operator< (const Rational & a, const Rational & b) { return (a - b).numer < 0; }
	friend bool operator> (const Rational & a, const Rational & b) { return b<a; }
	friend bool operator<=(const Rational & a, const Rational & b) { return !(a>b); }
	friend bool operator>=(const Rational & a, const Rational & b) { return !(a<b); }

	template<typename G>
	friend Rational<G> operator+(Rational<G> a, const Rational<G> & b) { return a += b; }
	template<typename G>
	friend Rational<G> operator+(G a, Rational<G> b) { return b += a; }
	template<typename G>
	friend Rational<G> operator+(Rational<G> a, G b) { return a += b; }
	template<typename G>
	friend Rational<G> operator-(Rational<G> a, const Rational<G> & b) { return a -= b; }
	template<typename G>
	friend Rational<G> operator-(G a, Rational<G> b) { return b -= a; }
	template<typename G>
	friend Rational<G> operator-(Rational<G> a, G b) { return a -= b; }
	template<typename G>
	friend Rational<G> operator*(Rational<G> a, const Rational<G> & b) { return a *= b; }
	template<typename G>
	friend Rational<G> operator*(G a, Rational<G> b) { return b *= a; }
	template<typename G>
	friend Rational<G> operator*(Rational<G> a, G b) { return a *= b; }
	template<typename G>
	friend Rational<G> operator/(Rational<G> a, const Rational<G> & b) { return a /= b; }
	template<typename G>
	friend Rational<G> operator/(G a, Rational<G> b) { return b /= a; }
	template<typename G>
	friend Rational<G> operator/(Rational<G> a, G b) { return a /= b; }
	template<typename G>
	friend std::ostream & operator<<(std::ostream & os, const Rational<G> & rat);
	template<typename G>
	friend Rational<G> abs(const Rational<G> & r) {
		return Rational<G>(absval(r.numer), absval(r.denom));
	}


	double to_double() const {
		return double(numer) / double(denom);
	}

	bool valid() const {
		return denom != 0;
	}

	T numer;
	T denom;
};


template<typename T>
std::ostream & operator<<(std::ostream & os, const Rational<T> & rat) {
	os << rat.numer << " / " << rat.denom;
	return os;
}



#endif






