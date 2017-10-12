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
	Edge(const IDType & from_ = 0, const IDType & to_ = 0, const WeightType & w_ = 0, const llong edgeID_ = -1) : from(from_), to(to_), w(w_), edgeID(edgeID_) {}
	
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


template <class T>
inline void hash_combine(std::size_t & seed, const T & v) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename IDType, typename WeightType>
struct EdgeHasher {
	std::size_t operator()(Edge<IDType, WeightType> const & e) const {
		std::size_t seed = 0;
		hash_combine(seed, e.edgeID);
		return seed;
	}
};



template<typename IDType, typename WeightType>
std::ostream & operator<<(std::ostream & os, const Edge<IDType,WeightType> & e) {
	os << "(" << e.from << "," << e.to << ")";
	return os;
}

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
		E e(from_id, to_id, w, next_id++);
		G[from_id].push_back(e);
		edges[e.edgeID] = e;
		if(!ret){// if it exists
			G_small[from_id][to_id] = std::min(G_small[from_id][to_id], w);
		} else {
			G_small[from_id][to_id] = w;
		}
		return next_id - 1;		
	}
	
	bool add_node(const IDType & id){
		nodes.insert(id);
		if(exists(id)){
			return false;
		} else {
			G[id] = std::vector<E>();
			G_small[id] = std::unordered_map<IDType,WeightType>();
			return true;
		}		
	}
	
	std::unordered_set<IDType> node_list() const {
		return nodes;
	}
	
	std::unordered_map<llong,Edge<IDType,WeightType>> edge_list() const {
		return edges;
	}
	
	const std::unordered_set<IDType> & node_list_ref() const {
		return nodes;
	}
	
	const std::unordered_map<llong,Edge<IDType,WeightType>> & edge_list_ref() const {
		return edges;
	}
	
	
	
	Graph(){}
	
	llong next_id = 0;
	
	std::unordered_map<IDType,std::unordered_map<IDType,WeightType> > G_small; //keeps track of smallest weight edge for each
	std::unordered_map<IDType,std::vector<Edge<IDType,WeightType> > > G;
	std::unordered_set<IDType> nodes;
	std::unordered_map<llong,Edge<IDType,WeightType>> edges;
};








































#endif