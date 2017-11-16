



#include "suffix_tree.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	//~ cin.sync_with_stdio(false);
	//~ cin.tie(0);
	
	
	int n;
	
	std::cin >> n;
	while(std::cin) {
	
		std::vector<std::string> patterns(n);
		std::string(p);
		std::getline(cin, p);
		for(int i = 0; i<n; ++i) {
			std::getline(cin, p);
			
			patterns[i] = p;		
		}
		
		std::getline(cin, p);
		SuffixTree st(p);
		
		for(int i = 0; i<n; ++i) {
			auto vi = st.match(patterns[i]);
			std::sort(vi.begin(), vi.end());
			for(auto i : vi){
				cout << i << " ";
			} 	
			cout << "\n";
		}
		std::cin >> n;
		
	}
	
	
	return 0;
}