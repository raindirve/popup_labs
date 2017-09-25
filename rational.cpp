
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>


typedef long long llong;

std::random_device rd;     
std::mt19937 rng(rd());    

template<typename T>
T gcdr(T a, T b) {
	if (a == 0) return b;
	return gcdr(b%a, a);
}

template<typename T>
T gcd(T a, T b) {
	return gcdr(abs(a),abs(b));
}

template<typename T>
struct Rational {
	Rational(T n_ = 0, T d_ = 1) {
		if (d_ < 0) {
			numer = -n_;
			denom = -d_;
		} else {
			numer = n_;
			denom = d_;
		}
		reduce();
	}

	Rational(T num) {
		numer = num;
		denom = 1;
	}


	Rational & reduce() {
		T my_gcd = gcd(numer,denom);

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



int main() {
	llong N;
	std::cin >> N;

	std::uniform_int_distribution<int> ur_op(0, 3);
	std::uniform_int_distribution<llong> ur(-1e+9, 1e+9);
	for (int i = 0; i < N; ++i) {
		llong n1,n2,d1,d2;
		char op;

		std::cin >> n1 >> d1 >> op >> n2 >> d2;

		Rational<llong> left(n1, d1);
		Rational<llong> right(n2, d2);

		switch (op) {
			case '+':
				std::cout << (left + right).reduce() << "\n";
				break;
			case '-':
				std::cout << (left - right).reduce() << "\n";
				break;
			case '*':
				std::cout << (left * right).reduce() << "\n";
				break;
			case '/':
				std::cout << (left / right).reduce() << "\n";
				break;
		}
	}


	return 0;
}






















