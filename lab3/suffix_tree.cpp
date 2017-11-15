#include <bits/stdc++.h>
#include "suffix_tree.h"

using namespace std;


int main(){
	std::string s;
	std::cin >> s;
	
	s = s+'$';
	SuffixTree st(s);
	
	auto root = st.nodes[0];
	
	//~ for(auto p : root.children) {
		//~ std::cout << p.first << " ";
	//~ }
	//~ std::cout << "\n";	
	
	

	std::queue<std::pair<int,int>> q;
	q.push(std::pair<int,int>(0,0));
	
	std::cout << s.substr(1,0) << "\n";
	
	dprint(st);

	//~ while(!q.empty()) {
		//~ std::pair<int,int> u = q.front();
		//~ int idx = u.first;
		//~ int depth = u.second;
		//~ q.pop();
		
		//~ Node & n = st.nodes[idx];
		
		//~ std::cout << "Node: " << s.substr(n.begin, n.end - n.begin) << " at depth " << depth << "\n";
		//~ std::cout << "  " << n.begin << " " <<  n.end << "\n";
		//~ for(auto p : n.children) {
			//~ std::cout << "  " << p.first << "\n";
			//~ q.push(std::pair<int,int>(p.second,depth+1));			
		//~ }
		
		
	//~ }
	
	
	
	return 0;
}