

#include <iostream>
#include "apsp.h"
#include <vector>

//#include "util.h" // debug
using namespace std;
typedef long long llong;


int main(){
	int n, m, q;
	cin >> n >> m >> q;
	int from, to, weight;
	while(n != 0){		
		Graph<int, long> G;
		for(int i = 0; i < n; ++i){
			G.add_node(i);
		}
		for(int i = 0; i < m; ++i){
			cin >> from >> to >> weight;
			G.add_edge(from, to, weight);			
		}
		//~ cerr << "Num nodes: " << G.nodes.size() << " " << G.node_list_ref().size() << endl;
		//~ if(G.n_nodes() > 150) exit(3);
		auto apsp = shortest_path_all_pairs(G);
		
		//~ for(int i = 0; i<n; ++i) {
			//~ for(int j = 0; j<n; ++j) {
				//~ cout << apsp.second[i][j] << "\t";
			//~ }
			//~ cout << "\n";
		//~ }
		//~ cout << "\n";

		for(int i = 0; i < q; ++i){
			int from,to;
			cin >> from >> to;
			
			if(apsp.first[from].count(to) > 0) { // if possible
				if(apsp.second[from][to]) { // neg cycle
					cout << "-Infinity\n";
				} else {
					cout << apsp.first[from][to] << "\n";
				}				
			} else {
				cout << "Impossible\n";
			}
			
		}
		cout << "\n";
		cin >> n >> m >> q;		
	}
	
	
	
}










