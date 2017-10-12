/**
 * Describes a weighted, directional graph
 * 
 * Maps from IDType to weighted neighbour lists. 
 *
 * ID-agnostic - any hashable type should be useable as unique vertex IDs.
 * 
 * WeightType needs to be a number (at minimum, supports addition and initialization to 0).
 *
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#ifndef _POPUP17SM_GRAPH_
#define _POPUP17SM_GRAPH_

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
struct Edge {
	Edge(const IDType & from_, const IDType & to_, const WeightType & w_, const llong edgeID_ = 0) : from(from_), to(to_), w(w_), edgeID(edgeID_) {}
	
	IDType from;
	IDType to;
	WeightType w;
	llong edgeID;
	
	bool operator==(const Edge & other) const {
		return edgeID == other.edgeID;
	}
		
	bool operator<(const Edge & other) const {
		return w < other.w;
	}	

	bool operator>(const Edge & other) const {
		return w > other.w;
	}
};

template<typename IDType, typename WeightType>
struct Graph{	
	typedef std::pair<WeightType,IDType> WNode;
	typedef std::pair<IDType, WeightType> NWode;
	typedef Edge<IDType, WeightType> E;
	
	// Returns the weighted neighbour list of every outgoing edge from id. (vector of pair < neighborID, edgeWeight >)
	std::vector<Edge<IDType, WeightType> > & operator[](const IDType & id) {
		return(G[id]);
	}
	
	// Returns the weighted neighbour list of every outgoing edge from id. (vector of pair < neighborID, edgeWeight >)
	const std::vector<Edge<IDType, WeightType> > & operator[](const IDType & id)  const {
		return(G.at(id));
	}
	
	// Returns the weighted neighbour list of the smallest edge to each neighbour. (map neighborID->edgeWeight)
	std::unordered_map<IDType,WeightType> & smallest_at(const IDType & id) {
		return(G_small[id]);
	}
	
	// Returns the weighted neighbour list of the smallest edge to each neighbour.  (map neighborID->edgeWeight)
	const std::unordered_map<IDType,WeightType> & smallest_at(const IDType & id)  const {
		return(G_small.at(id));
	}
	
	bool exists(const IDType & id) const {
		return G.count(id) > 0;
	}
	
	bool edge_between(const IDType & i1, const IDType & i2) const {
		return (exists(i1) && operator[](i1).count(i2) > 0);
	}
	
	/**
	 * Returns the number of nodes (vertices) in the graph.
	 * 
	 * The graph is aware of any node that has been added with 'add_node' or 
	 * is/has been part of any edge in the graph.
	 */
	size_t n_nodes() const {
		return G.size();
	}
	
	/**
	 * Returns the number of outgoing neighbours for a given node.
	 */
	size_t n_neighbors(const IDType & id) const {
		if(exists(id)) {
			return G_small[id].size();
		} else {
			return 0;
		}
	}
	
	
	/**
	 * Adds an edge to the graph.
	 * 
	 * Returns the internal id of the new edge, for hacking purposes.
	 */
	llong add_edge(const IDType & from_id, const IDType & to_id, const WeightType & w) {
		bool ret(false);
		
		add_node(to_id);
		add_node(from_id);
		
		ret = G_small[from_id].count(to_id) == 0;
		G[from_id].push_back(E(from_id, to_id, w, next_id++));
		if(!ret){// if it exists
			G_small[from_id][to_id] = std::min(G_small[from_id][to_id], w);
		} else {
			G_small[from_id][to_id] = w;
		}
		return next_id - 1;		
	}
	
	bool add_node(const IDType & id){
		if(exists(id)){
			return false;
		} else {
			G[id] = std::vector<E>();
			G_small[id] = std::unordered_map<IDType,WeightType>();
			return true;
		}
	}
	
	Graph(){}
	
	llong next_id = 0;
	
	std::unordered_map<IDType,std::unordered_map<IDType,WeightType> > G_small; //keeps track of smallest weight edge for each
	std::unordered_map<IDType,std::vector<Edge<IDType,WeightType> > > G;
};








































#endif