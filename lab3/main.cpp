
#include <iostream>
#include <vector>
#include "modmath.h"




int main() {
	
	llong n;
	int t;

	std::cin >> n >> t;
	while (n != 0) {
		assert(std::cin);
		for (int i = 0; i < t; ++i) {
			llong x,y;
			char op;
			std::cin >> x >> op >> y;
			assert(x >= 0 && y >= 0);
			assert(x < n && y < n);
			switch (op) {
				case '/':
					std::cout <<  div_mod(x, y, n) << "\n";
					break;
				case '*':
					std::cout << mult_mod(x, y, n) << "\n";
					break;
				case '+':
					std::cout <<  add_mod(x, y, n) << "\n";
					break;
				case '-':
					std::cout <<  sub_mod(x, y, n) << "\n";
					break;
			}
		}

		std::cin >> n >> t;
	}
	std::cin >> n;
	assert(!std::cin);
	
	

	return 0;
}




















