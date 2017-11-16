



#include "suffix_tree.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	//~ cin.sync_with_stdio(false);
	//~ cin.tie(0);
	
	
	std::string s;	
	std::getline(cin, s);
	while(std::cin) {
		SuffixTree st(s);
		auto an = st._suffix_dfs(0);
		
		
		int n;
		std::cin >> n;
		int k;
		for(int i = 0; i<n; ++i) {
			std::cin >> k; 
			std::cout << an[s.size()-k-1] << " ";
		}
		std::cout << "\n";
		
		std::getline(cin, s);
		std::getline(cin, s);		
	}
	
	
	return 0;
}