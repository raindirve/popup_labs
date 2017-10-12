/**
 * Contains functions for finding all pairs of shortest paths in a graph
 *
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#ifndef _POPUP17SM_APSP_
#define _POPUP17SM_APSP_

#include "graph.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <utility>


/*
*	Uses Floyd-Warshall algorithm to calculate all minimum pairwise distance in a graph. O(|V|^3)
*	Returns a pair of map<ID,map<ID,weight>> (sparse matrix) and map<ID,map<ID,bool>>.
*	The first element in the pair is the distance matrix. 
* 	The second elemnt is a bool matrix which is true for the paths which go through infinite loops
*	Sorry about the return type
*/
template<typename IDType, typename WeightType>
std::pair<std::unordered_map<IDType,std::unordered_map<IDType, WeightType> >, std::unordered_map<IDType,std::unordered_map<IDType, bool> > > shortest_path_all_pairs(const Graph<IDType,WeightType> & G) {
	std::unordered_map<IDType,std::unordered_map<IDType, WeightType> > dists;
	std::unordered_map<IDType,std::unordered_map<IDType, bool> > neg_cycles;

	const auto & nodes = G.node_list_ref();
	const auto & edges = G.edge_list_ref();
	
	// self distances = 0
	for(auto it = nodes.cbegin(); it != nodes.cend(); ++it) {
		dists[*it][*it] = 0;
	}
	
	// add all edges to dists
	for(auto it = edges.cbegin(); it != edges.cend(); ++it) {	
		if(dists[it->second.from].count(it->second.to)) { // if exists
			dists[it->second.from][it->second.to] = std::min(it->second.w, dists[it->second.from][it->second.to]);
		} else {
			dists[it->second.from][it->second.to] = it->second.w;
		}			
	}
	
	llong counter = 0;
	for(auto it1 = nodes.cbegin(); it1 != nodes.cend(); ++it1) {
		for(auto it2 = nodes.cbegin(); it2 != nodes.cend(); ++it2) {
			for(auto it3 = nodes.cbegin(); it3 != nodes.cend(); ++it3) {
				++counter;
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
	//~ std::cerr << counter << "iterations" << std::endl;
	
	for(auto it_k = nodes.cbegin(); it_k != nodes.cend(); ++it_k) {
		if(dists[*it_k][*it_k] < 0) { // if the connector is part of a neg loop
			for(auto it1 = nodes.cbegin(); it1 != nodes.cend(); ++it1) {
				for(auto it2 = nodes.cbegin(); it2 != nodes.cend(); ++it2) {
					if(dists[*it1].count(*it2) == 0){} else{ // if no path exists -> no risk of negative loop
						bool connected_path = (dists[*it1].count(*it_k) > 0) && (dists[*it_k].count(*it2) > 0);
						if(connected_path) { // if connected path exists
							neg_cycles[*it1][*it2] = true;
						}									
					}
				}
			}
		}
	}
	
	
	return std::pair<std::unordered_map<IDType,std::unordered_map<IDType, WeightType> >, std::unordered_map<IDType,std::unordered_map<IDType, bool> > > (dists,neg_cycles);
}



#endif

















