#include "suffix_tree.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	//~ cin.sync_with_stdio(false);
	//~ cin.tie(0);
	std::string p;
	std::string t;
	
	std::getline(cin, p);
	//~ cerr << p;
	while(std::cin) {
		std::getline(cin, t);
	
		//~ cerr << t;
		//~ p = p.substr(0, p.size()-1);
		//~ t = p.substr(0, t.size()-1);
		//~ cerr << p << '\n';
		//~ cerr << t << '\n';
		SuffixTree st(t);
		//~ return 0;
		auto vi = st.match(p);
		return 0;
		std::sort(vi.begin(), vi.end());
		for(auto i : vi){
			cout << i << " ";
		} 	
		cout << "\n";
		return 0;
		
		std::getline(cin, p);
	}
	
	
	//~ for(char c = 1; c!=0; ++c) {
		//~ std::cout << uc(c) << "\n";
	//~ }
	
	
	
	
	
	return 0;
}