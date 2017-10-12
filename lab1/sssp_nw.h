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
 * 
 * 
 * 
 */
template<typename IDType, typename WeightType>
std::unordered_map<IDType,std::pair<IDType, std::pair<WeightType, bool> > shortest_path_negweights(const Graph<IDType,WeightType> & G, const IDType & from) {
	
	std::unordered_set<IDType> visited;
	std::unordered_set<IDType> new_visited;
	
	std::unordered_map<IDType,IDType> came_from;
	
	//~ typedef std::pair<WeightType, bool> WPair;
	std::unordered_map<IDType,WPair> node_weight;
	std::unordered_map<IDType, WeightType> node_weight;
	
	
	size_t size = G.n_nodes();
	came_from[from] = from;
	node_weight[from] = WPair(0, false);
	
	for(int i = 0; i < size; ++i){
		for(auto it = visited.cbegin(); it != visited.cend(); ++it){
			const IDType & curr = *it;
			const WPair & cwc = node_weight[curr];
			
			for(auto neighit = G.smallest_at(*it).cbegin(); neighit != G.smallest_at(*it).cend(); ++neighit){
				
				
				if(node_weight.count(neighit->first) == 0){
					WPair(cwc.first + 
				}
				
				
				
			}
		}
	}
	
	while(!q.empty()) {
		PQ_Node curr = q.top();
		q.pop();
		//~ std::cerr << "Just removed " << curr.from << "->" << curr.to  << std::endl;
		
		WeightType & cw = curr.w;
		IDType & cid = curr.to;
		
		if(visited.count(cid)>0) continue;
		visited.insert(cid);
		
		came_from[curr.to] = curr.from; 		
		
		// get neighbs
		//~ std::cerr << cid << " is being naughty. \n";
/* 		const auto neighbs = G.smallest_at(cid);
		//~ std::cerr << "Neighbs: " << neighbs.size() << std::endl;
		for(auto it = neighbs.cbegin(); it != neighbs.cend(); ++it) {
			const auto & n = *it;
			if(visited.count(n.first) > 0) continue;
			//~ std::cerr << "Added " << cid << "->" << n.first << std::endl;
			q.push(PQ_Node(cid, n.first, cw+n.second));			
		} */
		
		const auto neighbs = G[cid];
		//~ std::cerr << "Neighbs: " << neighbs.size() << std::endl;
		for(auto it = neighbs.cbegin(); it != neighbs.cend(); ++it) {
			const auto & n = *it;
			if(visited.count(n.to) > 0) continue;
			//~ std::cerr << "Added " << cid << "->" << n.first << std::endl;
			q.push(PQ_Node(n.from, n.to, cw+n.w));			
		}
		
		
	}	
	
	return came_from;
	
}



























#endif