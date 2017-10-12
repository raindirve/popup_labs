#ifndef _POPUP17SM_GRAPH_
#define _POPUP17SM_GRAPH_

#include <algorithm>
#include <vector>
#include <iostream> //cerr for debug
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include "graph.h"




typedef long long llong;


/**
 * Returns the backtracking map for all reachable nodes from 'from'.
 * 
 * ////Backtracking map contains data on the format
 * ////[NodeID -> (ParentID, (WeightIfNotNegCycle, hasNegCycle))]
 *nope
 * 
 * Note than unreachable nodes will not be in the backtracking map.
 * 
 * 
 */
template<typename IDType, typename WeightType>
std::unordered_map<IDType,std::pair<IDType, std::pair<WeightType, bool> > shortest_path_negweights(const Graph<IDType,WeightType> & G, const IDType & from) {
	
	std::unordered_set<IDType> visited;
	std::unordered_set<IDType> new_visited;
	
	std::unordered_map<IDType,IDType> came_from;
	
	std::unordered_map<IDType, WeightType> node_weight;
	std::unordered_map<IDType, bool> node_cycle;
	
	
	size_t size = G.n_nodes();
	came_from[from] = from;
	node_weight[from] = 0;
	
	for(int i = 0; i < size; ++i){
		for(auto it = visited.cbegin(); it != visited.cend(); ++it){
			const IDType & curr = *it;
			const WeightType & cw = node_weight[curr];
			
			for(auto neighit = G.smallest_at(*it).cbegin(); neighit != G.smallest_at(*it).cend(); ++neighit){
				const pair<IDType, WeightType> & targ = *neighit;
				if(node_weight.count(targ.first) == 0){
					node_weight[targ.first] = cw + targ.second;
					new_visited.insert(targ.first);
					came_from[targ.first] = curr;
				} else {
					if(cw + targ.second < node_weight[targ.first]){
						node_weight[targ.first]  = cw+targ.second;
						came_from[targ.first] = curr;
					}	
				}
			}
		}
		visited = new_visited;
	}
	
	//check for negative cycles
	for(auto it = visited.cbegin(); it != visited.cend(); ++it){
		node_cycle[*it] = false;
	}
	for(int i = 0; i < visited.size(); ++i){
		for(auto it = visited.cbegin(); it != visited.cend(); ++it){
			const IDType & curr = *it;
			const WeightType & cw = node_weight[curr];
			
			for(auto neighit = G.smallest_at(*it).cbegin(); neighit != G.smallest_at(*it).cend(); ++neighit){
				const pair<IDType, WeightType> & targ = *neighit;
				if(cw + targ.second < node_weight[targ.first]){
					node_weight[targ.first]  = cw+targ.second;
					came_from[targ.first] = curr;
					node_cycle[targ.first] = true;
				}
			}
		}
	}
	
	
	for(auto it = visited.cbegin(); it != visited.cend(); ++it){
		
	}
	return came_from;
}



























#endif