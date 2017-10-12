#include "sssp_nw.h"
#include <iostream>
#include <vector>
//~ #include "util.h" // debug
using namespace std;
typedef long long llong;


int main(){
	int n, m, q, s; // s == origin
	cin >> n >> m >> q >> s;
	int from, to, weight;
	while(n != 0){
		
		Graph<int, long> G;
		for(int i = 0; i < n; ++i){
			G.add_node(i);
		}
		for(int i = 0; i < m; ++i){
			cin >> from >> to >> weight;
			G.add_edge(from, to, weight);
			//cerr << G[from].size() << " and " << G[to].size() << endl;
			
		}
				
		std::unordered_map<int,std::pair<int, std::pair<long, bool> > > data = shortest_path_negweights(G, s);
		
		//~ printiterr(data.begin(), data.end());
		
		
		//cerr << "i like building" << endl;
		
		int target;
		for(int i = 0; i < q; ++i){
			//~ cerr << "query " << i << endl;
			cin >> target;
			if(data.count(target) > 0){
				if(data[target].second.second){
					cout << "-Infinity" << '\n';
				}else {
					cout << data[target].second.first << '\n';
				}
			} else {
				cout << "Impossible" << '\n';
			}				
			
			
		}
		cout << endl;
		cin >> n >> m >> q >> s;
	}
	
	
	
}