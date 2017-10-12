/**
 * Contains functions for finding all pairs of shortest paths in a graph
 *
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#ifndef _POPUP17SM_MAXFLOW_
#define _POPUP17SM_MAXFLOW_


#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

typedef long long llong;

struct Edge {
	llong from;
	llong to;
	llong flow;
	llong capacity;
	llong id;
	llong reverse_id;	
}


/*
*	Uses Floyd-Warshall algorithm to calculate all minimum pairwise distance in a graph. O(|V|^3)
*	Returns a pair of map<ID,map<ID,weight>> (sparse matrix) and map<ID,map<ID,bool>>.
*	The first element in the pair is the distance matrix. 
* 	The second elemnt is a bool matrix which is true for the paths which go through infinite loops
*	Sorry about the return type
*/
template<typename IDType, typename WeightType>
Graph<IDType, WeightType> maxflow(Graph<IDType, WeightType> G, IDType s, IDType t) {
	const auto & nodes = G.node_list_ref();
	
	while(true) { // until bfs cant find anything		
		std::unordered_map<IDType,llong> came_from;
		
		std::queue<IDType> q;
		q.push(s);
		
		while(!q.empty()) {
			IDType cur = q.front();
			q.pop();
			
			auto neighbs = G[cur];
			for(auto it = neighbs.begin(); it != neighbs.end(); ++it) {
				if(came_from.count(it->to) == 0 && (it->to) != s && (it->capacity) > (it->flow)) {
					came_from[it->to] = it->edgeID;
					q.push(it->to);
				}
			}			
		}
		
		if(came_from.count(t) == 0) break; // no path found

		bool update = true;
		WeightType min_flow;
		llong edgeID;
		IDType id = t;
		while(came_from.count(id)) {
			if(update) {
				min_flow = G. came_from[id]
			}
			
			
		}
		

		
	}
	
	
}

#endif

















