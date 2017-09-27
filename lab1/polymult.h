#ifndef ___POLYMULT___
#define ___POLYMULT___

/**
* @author seanw
* @author michalh
**/



#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <valarray>



#define PI 3.14159265


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







#endif




















