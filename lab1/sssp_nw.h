#ifndef _POPUP17SM_BELLFORD_
#define _POPUP17SM_BELLFORD_

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
 * Backtracking map contains data on the format
 * [NodeID -> (ParentID, (WeightIfNotNegCycle, hasNegCycle))]
 * 
 * If hasNegCycle, backtracking will only reach the most recent infinite loop.
 * 
 * (The function can be modified to construct any path by adding a backtracking map that keeps track of the first seen parent.
 *  These can be taken back to origin from such an infloop.)
 * 
 * Note than unreachable nodes will not be in the backtracking map.
 */
template<typename IDType, typename WeightType>
std::unordered_map<IDType,std::pair<IDType, std::pair<WeightType, bool> > > shortest_path_negweights(const Graph<IDType,WeightType> & G, const IDType & from) {
	
	std::unordered_set<IDType> visited;
	std::unordered_set<IDType> new_visited;
	
	std::unordered_map<IDType,IDType> came_from;
	
	std::unordered_map<IDType, WeightType> node_weight;
	std::unordered_map<IDType, bool> node_cycle;
	
	
	size_t size = G.n_nodes();
	came_from[from] = from;
	node_weight[from] = 0;
	visited.insert(from);
	new_visited.insert(from);
	
	for(size_t i = 1; i < size; ++i){ //run |V| - 1 
		for(auto it = visited.cbegin(); it != visited.cend(); ++it){
			const IDType & curr = *it;
			const WeightType & cw = node_weight[curr];
			
			for(auto neighit = G.smallest_at(*it).cbegin(); neighit != G.smallest_at(*it).cend(); ++neighit){
				const std::pair<IDType, WeightType> & targ = *neighit;
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
	std::queue<IDType> q;
	
	for(auto it = visited.cbegin(); it != visited.cend(); ++it){
		const IDType & curr = *it;
		const WeightType & cw = node_weight[curr];
		
		for(auto neighit = G.smallest_at(*it).cbegin(); neighit != G.smallest_at(*it).cend(); ++neighit){
			const std::pair<IDType, WeightType> & targ = *neighit;
			if(cw + targ.second < node_weight[targ.first]){
				node_weight[targ.first]  = cw+targ.second;
				came_from[targ.first] = curr;
				if(!node_cycle[targ.first]){
					node_cycle[targ.first] = true;
					q.push(targ.first);
				}
			}
		}
	}
	
	while(!q.empty()){
		IDType n = q.front();
		q.pop();
		for(auto neighit = G.smallest_at(n).cbegin(); neighit != G.smallest_at(n).cend(); ++neighit){
			if(!node_cycle[neighit->first]){
				node_cycle[neighit->first] = true;
				q.push(neighit->first);
			}
		}
	}
	
	
	//construct output
	std::unordered_map<IDType,std::pair<IDType, std::pair<WeightType, bool> > > rv;
	for(auto it = visited.cbegin(); it != visited.cend(); ++it){
		//~ std::cerr << "inserting" << *it << "in return value" << '\n';
		rv[*it] = std::pair<IDType, std::pair<WeightType, bool> >(came_from[*it], std::pair<WeightType, bool>(node_weight[*it], node_cycle[*it]));
	}
	return rv;
}



























#endif