#ifndef ___POLYMULT___
#define ___POLYMULT___

/**
 * Provides functions 
 * 
 * @author seanw
 * @author michalh
 **/



#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <valarray>



//#define PI 3.14159265


void fft(std::valarray<std::complex<double> > & a) { // better use this one
	int n = a.size(); // should be power of 2
	if(n <= 1) return;
	
	std::valarray<std::complex<double> > a_even = a[std::slice(0, n/2, 2)]; // split in half, odd and even powers
	std::valarray<std::complex<double> > a_odd = a[std::slice(1, n/2, 2)];
	
	fft(a_even);
	fft(a_odd);
	
	std::complex<double> k;	
	double angle = 0;
	for (int j=0; j < n/2; ++j, angle += -2 * M_PI / n) {		
		k = std::complex<double>(cos(angle),sin(angle)) * a_odd[j]; 
		a[j] = a_even[j] + k;
		a[j+n/2] = a_even[j] - k;
	}	
}

void ifft(std::valarray<std::complex<double> > & a) {	
	a = a.apply(std::conj); 
    fft(a);
	a = a.apply(std::conj);
    a /= a.size();
}


typedef long long llong;

std::vector<double> polymult(const std::vector<double> & a_, const std::vector<double> & b_ ) {
	int na = a_.size();
	int nb = b_.size();
	
	int max_power = na + nb; // maximum possible power from the result of the mult
	
	int s = 1;
	while(s < max_power) { // smallest power of 2 larger than max power
		s <<= 1;
	}
	
	std::valarray<std::complex<double>> a(s);		// need complex numbers for the fft
	std::valarray<std::complex<double>> b(s);
	
	for(int i = 0; i<na; ++i) {
		a[i] = std::complex<double>(a_[i],0);
	}
	
	for(int i = 0; i<nb; ++i) {
		b[i] = std::complex<double>(b_[i],0);
	}
	
	fft(a); // fft both polynomials
	fft(b);
	
	for(int j = 0; j<s; ++j) {  // convolution becomes pointwise multiplication
		a[j] *= b[j];
	}
	
	ifft(a); // inverse fft
	
	std::vector<double> ans(s); // output vector
	for(int j = 0; j<s; ++j) {
		ans[j] = a[j].real();
	}
	return ans;
}





#endif




















