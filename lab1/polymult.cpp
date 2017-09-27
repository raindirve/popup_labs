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


void FFT(std::vector<std::complex<double> > & A, bool invert = false) { // this is fucked
	int n = A.size(); // should be power of 2
	if(A.size() == 1) return;
	
	std::vector<std::complex<double> > A_even(n/2);
	std::vector<std::complex<double> > A_odd(n/2);
	
	for(int i = 0; i<n/2; ++i) {
		A_even[i] = A[2*i];
		A_odd[i] = A[2*i+1];		
	}
	
	FFT(A_even, invert);
	FFT(A_odd, invert);
	
	double angle = 2 * M_PI / n;
	if(invert) angle *= -1;
	
	
	std::complex<double> w(cos(angle),sin(angle));
	std::complex<double> x(1,0);
	
	for (int j=0; j < n/2; ++j) {
		A[j] = A_even[j] + x * A_odd[j];
		A[j+n/2] = A_even[j] - x * A_odd[j];
		if(invert) {
			A[j] /= 2;
			A[j+n/2] /= 2;
		}		
		x = x * w;
	}	
}


void betterFFT(std::valarray<std::complex<double> > & a) { // better use this one
	int n = a.size(); // should be power of 2
	if(n <= 1) return;
	
	std::valarray<std::complex<double> > a_even = a[std::slice(0, n/2, 2)]; // split in half, odd and even powers
	std::valarray<std::complex<double> > a_odd = a[std::slice(1, n/2, 2)];
	
	betterFFT(a_even);
	betterFFT(a_odd);
	
	std::complex<double> k;	
	double angle = 0;
	for (int j=0; j < n/2; ++j, angle += -2 * M_PI / n) {		
		k = std::complex<double>(cos(angle),sin(angle)) * a_odd[j]; 
		a[j] = a_even[j] + k;
		a[j+n/2] = a_even[j] - k;
	}	
}

void betteriFFT(std::valarray<std::complex<double> > & a) {	
	a = a.apply(std::conj); 
    betterFFT(a);
	a = a.apply(std::conj);
    a /= a.size();
}



template<typename T>
void print_vec(const std::vector<T> & arr, int n = -1) {
	if(n == -1) n = arr.size();
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

template<typename T>
void print_vec(const std::valarray<T> & arr) {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}


int main() {	
	
	int T;
	
	std::cin >> T;
	
	for(int i = 0; i<T; ++i) {
		int na;
		std::cin >> na;
		++na;
		std::vector<std::complex<double>> va(na);		
		int k;
		for(int j = 0; j<na; ++j) {
			std::cin >> k;
			va[j] = k;
		}		
		
		int nb;
		std::cin >> nb;	
		++nb;
		std::vector<std::complex<double>> vb(nb);		
		for(int j = 0; j<nb; ++j) {
			std::cin >> k;
			vb[j] = k;
		}
		
		int max_power = na + nb;
	
		int s = 1;
		while(s < max_power) {
			s <<= 1;
		}
				
		std::valarray<std::complex<double>> a(s);		
		std::valarray<std::complex<double>> b(s);
		
		// print_vec(va);
		// print_vec(a);
		
		std::copy(va.begin(), va.end(), std::begin(a));   
		std::copy(vb.begin(), vb.end(), std::begin(b));   		
			
		
		// print_vec(a);
		
		betterFFT(a);
		betterFFT(b);
		
		// print_vec(a);
		
		for(int j = 0; j<s; ++j) {
			a[j] *= b[j];
		}
		
		// print_vec(a);
		betteriFFT(a);
		// print_vec(a);
		
		std::vector<long long> ans(s);
		
		max_power = 0;
		long long temp;
		for(int j = 0; j<s; ++j) {
			temp = round(a[j].real());
			ans[j] = temp;
			if(temp != 0) {
				max_power = j;
			}
		}
		
		std::cout << max_power << "\n";
		print_vec(ans,max_power+1);
		
	}
	
	
	
	
	
	
	return 0;
}



























