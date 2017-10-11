#ifndef _POPUP17SM_SSSP_
#define _POPUP17SM_SSSP_

#include <algorithm>
#include <vector>
#include <iostream> //cerr for debug
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>




typedef long long llong;
//typedef long long wtype;

template<typename IDType, typename WeightType>
struct Graph{	
	
	std::unordered_map<IDType,WeightType> & operator[](const IDType & id) {
		return(G[id]);
	}
	
	const std::unordered_map<IDType,WeightType> & operator[](const IDType & id)  const {
		return(G[id]);
	}
	
	bool exists(const IDType & id) const {
		return G.count(id) > 0;
	}
	
	bool edgeBetween(const IDType & i1, const IDType & i2) const {
		return (exists(i1) && operator[](i1).count(i2) > 0);
	}
	
	size_t n_nodes() const {
		return G.size();
	}
	
	/**
	* returns number of outgoing edges
	*/
	size_t n_neighbors(const IDType & id) const {
		if(exists(id)) {
			return G[id].size();
		} else {
			return 0;
		}
	}
	
	
	/**
	* updates the edge from from to to to have weight w
	* returns true if the edge did not previously exist
	*/
	bool addEdge(const IDType & from_id, const IDType & to_id, const WeightType & w) {
		bool ret;
		if(exists(from_id)) {			
			ret = G[from_id].count(to_id) == 0;			
			if(!exists(to_id)) {
				G[to_id] = std::unordered_map<IDType,WeightType>();
			}			
		} else {
			ret = true;			
			G[from_id] = std::unordered_map<IDType,WeightType>();					
		}
		G[from_id][to_id] = w;	
		return ret;		
	}
	
	
	
	Graph(){}
	
	
	
	
	std::unordered_map<IDType,std::unordered_map<IDType,WeightType>> G;
};




template<typename IDType, typename WeightType>
std::vector<IDType> shortest_path_nnweights(const Graph & G, const IDType & from, const IDType & to) {
	
	
}






















































#endif