#include <bits/stdc++.h>
#include "suffix_tree.h"

using namespace std;


int main(){
	std::string s;
	std::getline(cin, s);
	
	SuffixTree st(s);
	
	auto root = st.nodes[0];
	
	//~ for(auto p : root.children) {
		//~ std::cout << p.first << " ";
	//~ }
	//~ std::cout << "\n";	
	
	

	//~ std::queue<std::pair<int,int>> q;
	//~ q.push(std::pair<int,int>(0,0));
	
	//~ std::cout << s.substr(1,0) << "\n";
	
	
	//~ dprint(st);
	
	
	//~ string s;
	//~ string p;
	
	//~ s.push_back((char)(-1));
	//~ s.push_back((char)(-9));
	//~ s.push_back((char)(-1));
	//~ s.push_back((char)(-7));
	//~ s.push_back((char)(-1));
	//~ s.push_back((char)(-7));
	//~ s.push_back((char)(-5));
	
	//~ SuffixTree st(s);
	
	//~ p.push_back((char)(-1));
	//~ p.push_back((char)(-7));
	
	//~ auto vi = st.match(p);
	//~ return 0;
	//~ std::sort(vi.begin(), vi.end());
	//~ for(auto i : vi){
		//~ cout << i << " ";
	//~ } 	
	//~ cout << "\n";


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