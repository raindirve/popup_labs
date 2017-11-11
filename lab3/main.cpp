
#include <iostream>
#include <vector>
#include "modmath.h"




int main() {
	
	llong n;
	int t;

	std::cin >> n >> t;
	while (n != 0) {
		for (int i = 0; i < t; ++i) {
			llong x,y;
			char op;
			std::cin >> x >> op >> y;

			switch (op) {
				case '/':
					std::cout << div_mod(x,y,n) << "\n";
					break;
				case '*':
					std::cout << mult_mod(x, y, n) << "\n";
					break;
				case '+':
					std::cout << add_mod(x, y, n) << "\n";
					break;
				case '-':
					std::cout << sub_mod(x, y, n) << "\n";
					break;
			}
		}

		std::cin >> n >> t;
	}

	

	return 0;
}




















