#include "mst.h"
#include <iostream>
#include <vector>
//~ #include "util.h" // debug
using namespace std;
typedef long long llong;


int main(){
	int n, m;
	cin >> n >> m;
	int from, to, weight;
	while(n != 0){
		
		Graph<int, long> G;
		for(int i = 0; i < n; ++i){
			G.add_node(i);
		}
		for(int i = 0; i < m; ++i){
			cin >> from >> to >> weight;
			if(from > to) std::swap(from, to);
			G.add_edge(from, to, weight);
		}
				
		
		vector<llong> mintree = mst_internal_ids<int, long>(G);
		
		if(mintree.size() != n - 1){
			cout << "Impossible" << endl;
		} else{
			long totlen(0);
			pair<int, int> pt;
			string s("");
			vector<string> vs;
			vector<pair<int, int>> vpt;
			const auto & edges = G.edge_list_ref();
			
			for(auto it = mintree.begin(); it != mintree.end(); ++it){
				const Edge<int, long> & e = edges.at(*it);
				//s = to_string(e.from) + ' ' + to_string(e.to);
				//vs.push_back(s);
				pt = pair<int, int>(e.from, e.to);
				vpt.push_back(pt);
				totlen += e.w;
			}
			std::sort(vpt.begin(), vpt.end());
			std::sort(vs.begin(), vs.end());
			cout << totlen << endl;
			
			//~ for(auto it = vs.begin(); it != vs.end(); ++it){
				//~ cout << *it << '\n';
			//~ }
			for(auto it = vpt.begin(); it != vpt.end(); ++it){
				cout << it->first << ' ' << it->second << endl;
			}
		}
		
		
		cin >> n >> m;
	}
	
	
	
}