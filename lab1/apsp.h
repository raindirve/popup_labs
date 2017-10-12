#ifndef _POPUP17SM_APSP_
#define _POPUP17SM_APSP_

#include "graph.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

template<typename IDType, typename WeightType>
std::unordered_map<IDType,std::unordered_map<IDType, WeightType> > shortest_path_all_pairs(const Graph<IDType,WeightType> & G) {
	std::unordered_map<IDType,std::unordered_map<IDType, WeightType> > dists;
	//~ std::unordered_map<IDType,std::unordered_map<IDType, WeightType> > is_inf;
	const auto & nodes = G.node_list_ref();
	const auto & edges = G.edge_list_ref();
	
	for(auto it = nodes.cbegin(); it != nodes.cend(); ++it) {
		dists[*it][*it] = 0;
	}
	
	for(auto it = edges.cbegin(); it != edges.cend(); ++it) {
		dists[it->second.from][it->second.to] = it->second.w;
	}
	
	for(auto it1 = nodes.cbegin(); it1 != nodes.cend(); ++it1) {
		for(auto it2 = nodes.cbegin(); it2 != nodes.cend(); ++it2) {
			for(auto it3 = nodes.cbegin(); it3 != nodes.cend(); ++it3) {
				bool direct_path = dists[*it2].count(*it3) > 0;
				bool connected_path = (dists[*it2].count(*it1) > 0) && (dists[*it1].count(*it3) > 0);
				
				// if path already exists, compare to possible new path
				if(direct_path) {
					// if paths from it2 -> it1 and it1 -> it3 exist
					if(connected_path) {
						// compare, and set to lowest
						dists[*it2][*it3] = std::min(dists[*it2][*it3], dists[*it2][*it1] + dists[*it1][*it3]);
					}
				} else {
					// if path doesnt exist, and conneced path does, set to connected path
					if(connected_path) {
						dists[*it2][*it3] = dists[*it2][*it1] + dists[*it1][*it3];
					}
				}				
			}
		}
	}
	
	
	return dists;	
}



#endif

















