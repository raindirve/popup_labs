
#include "sssp.h"
#include <iostream>
#include <vector>
//#include "util.h" // debug
using namespace std;
typedef long long llong;


int main(){
	int T;
	cin >> T;
	//~ std::cout << T << "\n";
	
	int from, to, weight;
	for(int j = 0; j<T; ++j) {
		int N,M;
		cin >> N >> M;
		
		//~ std::cout << N << " " << M << "\n";
		
		Graph<int, long> G;
		for(int i = 1; i <= N; ++i){
			G.add_node(i);
		}
		for(int i = 0; i < M; ++i){
			cin >> from >> to >> weight;
			G.add_edge(from, to, weight);
			G.add_edge(to, from, weight);
			//cerr << G[from].size() << " and " << G[to].size() << endl;
			
		}
		
		int S;
		cin >> S;
				
		
		//~ std::cout << S << "\n";
		
		std::unordered_map< int, int > came_from = shortest_path_nnweights(G, S);
		
		//cerr << "i like building" << endl;
		
		
		for(int k = 1; k<=N; ++k) {
			int target = k;
			if(target == S) continue;
			long wsum(0);
			//~ cerr << "query " << i << endl;
			if(came_from.count(target) > 0){
				while(came_from[target] != target){
					wsum += G.smallest_at(came_from[target])[target];
					target = came_from[target];
				}
				cout << wsum;
			} else {
				cout << -1;
			}				
			//TODO	cout << path.first << '\n';
				

			cout << " ";
		}
		cout << "\n";
	}
	
	
	
}