/**
 * Minimum spanning tree.
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#ifndef _POPUP17SM_MST_
#define _POPUP17SM_MST_

#include <algorithm>
#include <vector>
#include <iostream> //cerr for debug
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include "graph.h"
#include "unionfind.h"




typedef long long llong;



/**
 * Returns the internal edge IDs of the edges in G that make up the minimal spanning tree.
 * 
 * Returns the minimal spanning forest if no such tree exists. (Check size of returned vector.)
 *
 * Be aware: Currently assumes nodes are 0-indexed integral types.
 */
template<typename IDType, typename WeightType>
std::vector<llong> mst_internal_ids(Graph<IDType, WeightType> & G){
	
	std::vector<llong> ids;
	
	const auto & edgemap = G.edge_list();
	
	std::vector< std::pair<llong, Edge<IDType, WeightType> > > edges(edgemap.begin(), edgemap.end());
	std::sort(edges.begin(), edges.end(),
	[](const std::pair<llong, Edge<IDType, WeightType> > & a, const std::pair<llong, Edge<IDType, WeightType> > & b) {
		return a.second < b.second;
	}
		);
	
	//ASSUMING vectors 0-initialized integrals:
	AlmostUnionFind unionfind(G.n_nodes());
	//TODO: add mapping IDType->unionfind index ->IDType
	
	WeightType tw(0);
	for(auto it = edges.begin(); it != edges.end(); ++it){
		const Edge<IDType, WeightType> & e = it->second;
		if(!(unionfind.query(e.from, e.to))){
			tw += e.w;
			unionfind.unite(e.from, e.to);
			ids.push_back(it->first);
		}
	}
	G.dbg_mst = tw;
	return ids;
}

template<typename IDType, typename WeightType>
std::vector<std::pair<IDType, IDType> > mst(const Graph<IDType, WeightType> & G){
	std::vector<llong> v = mst_internal_ids(G);
	std::vector<std::pair<IDType, IDType> > rv;
	for(auto it = v.begin(); it != v.end(); ++it){
		const Edge<IDType, WeightType>& e = G.edge_list()[*it];
		rv.push_back(std::pair<IDType, IDType>( e.from, e.to ));
	}
	
	return rv;
}
#endif