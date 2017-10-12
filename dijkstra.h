#ifndef ___DIJKSTRA___
#define ___DIJKSTRA___


#include <queue>
#include <vector>
#include <utility>
#include <unordered_set>
#include "util.h"


typedef double Valtype;
typedef std::vector<std::vector<Valtype>> Mattype;
typedef std::pair<Valtype,int> Pairtype;


template<typename GraphType>
std::vector<int> dijkstra(const GraphType & g, int from, int to) {
	
	std::priority_queue<std::pair<Valtype, int>> q;
	
	std::vector<bool> visited(g.nodes());
	visited[from] = true;
	
	q.insert(Pairtype(0,from));
	
	while(!q.empty()) {
		Pairtype current = q.top();
		q.pop();
		
		
		
		
		
		
		
		
	}
	
	
	

	
	
	
	
	return std::vector<int>();	
	
}





































#endif







