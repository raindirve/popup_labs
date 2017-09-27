#include "graph.h"
#include <iostream>
#include <vector>

using namespace std;
typedef long long llong;


int main(){
	int n, m, q, s; // s == origin
	cin >> n >> m >> q >> s;
	while(n != 0){
	    vector<int> a(m),b(m),c(m);
		for(int i = 0; i < m; ++i){
			cin >> a[i] >> b[i] >> c[i];
		}
		Graph<int> g(a,b,c);
		int target;
		for(int i = 0; i < q; ++i){
			cin >> target;
			auto path = g.get_path(s, target);
			if(path.second.empty()){
				cout << "Impossible" << '\n';
			}else{
				cout << path.first << '\n';
			}
		}
		
		cin >> n >> m >> q >> s;
		cout << endl;
	}
	
	
	
}