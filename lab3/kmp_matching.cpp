#include "kmp.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.sync_with_stdio(false);
	cin.tie(0);
	std::string p;
	std::string t;
	
	std::getline(cin, p);
	//~ cerr << p;
	while(std::cin) {
		std::getline(cin, t);
	
		
		//~ std::cerr << p << "\n";
		//~ std::cerr << t << "\n";
		auto vi = matcher(p,t);
		//~ std::cerr << "sup" << "\n";
		//~ std::sort(vi.begin(), vi.end());
		for(auto i : vi){
			cout << i << " ";
		} 	
		cout << "\n";
		
		std::getline(cin, p);
	}
	
	
	
	
	
	
	return 0;
}