#include "sssp.h"
#include <iostream>
#include <vector>
//#include "util.h" // debug
using namespace std;
typedef long long llong;


int main(){
	int n, m, q, s; // s == origin
	cin >> n >> m >> q >> s;
	int from, to, weight, t0, P;
	while(n != 0){
		std::unordered_map<llong,std::pair<int,int>> available;
		Graph<int, long> G;
		for(int i = 0; i < n; ++i){
			G.add_node(i);
		}
		for(int i = 0; i < m; ++i){
			cin >> from >> to >> t0 >> P >> weight;
			int id = G.add_edge(from, to, weight);
			available[id] = std::pair<int, int>(t0, P);			
		}
		
		std::unordered_map< int, pair<long, int> > came_from = shortest_path_nnttweights(G, s, available);
		
		//cerr << "i like building" << endl;
		
		int target;
		for(int i = 0; i < q; ++i){
			long wsum(0);
			//~ cerr << "query " << i << endl;
			cin >> target;
			if(came_from.count(target) > 0){
				/*while(came_from[target] != target){
					wsum += G.smallest_at(came_from[target])[target];
					target = came_from[target];
				}*/
				wsum = came_from[target].first;
				cout << wsum << endl;
			} else {
				cout << "Impossible" << '\n';
			}				
			//TODO	cout << path.first << '\n';
			
		}
		cout << endl;
		cin >> n >> m >> q >> s;		
	}
	
	
	
}