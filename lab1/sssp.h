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
/* 
template <class T>
inline void hash_combine(std::size_t & seed, const T & v) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct EdgeHasher {
	std::size_t operator()(Edge<_, _> const & e) const {
		std::size_t seed = 0;
		hash_combine(seed, e.edgeID);
		return seed;
	}
};
 */



template<typename IDType, typename WeightType>
struct Graph{	
	typedef std::pair<WeightType,IDType> WNode;
	typedef std::pair<IDType, WeightType> NWode;
	typedef Edge<IDType, WeightType> E;
	
	
	std::vector<Edge<IDType, WeightType> > & operator[](const IDType & id) {
		return(G[id]);
	}
	
	const std::vector<Edge<IDType, WeightType> > & operator[](const IDType & id)  const {
		return(G.at(id));
	}
	
	// return a map (neighbor list) of this node's neighbor nodes and the lowest weight of any paths there
	std::unordered_map<IDType,WeightType> & smallest_at(const IDType & id) {
		return(G_small.at(id));
	}
	
	const std::unordered_map<IDType,WeightType> & smallest_at(const IDType & id)  const {
		return(G_small.at(id));
	}
	
	bool exists(const IDType & id) const {
		return G.count(id) > 0;
	}
	
	bool edge_between(const IDType & i1, const IDType & i2) const {
		return (exists(i1) && operator[](i1).count(i2) > 0);
	}
	
	size_t n_nodes() const {
		return G.size();
	}
	
	/**
	* returns number of distinct outgoing edges
	*/
	size_t n_neighbors(const IDType & id) const {
		if(exists(id)) {
			return G_small[id].size();
		} else {
			return 0;
		}
	}
	
	
	/**
	* returns the id of the new edge
	*/
	llong add_edge(const IDType & from_id, const IDType & to_id, const WeightType & w) {
		//~ std::cerr << "Hey! Adding edge " << from_id << "->" << to_id << std::endl;
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




template<typename IDType, typename WeightType>
std::unordered_map<IDType,IDType> shortest_path_nnweights(const Graph<IDType,WeightType> & G, const IDType & from) {
	
	typedef Edge<IDType, WeightType> PQ_Node;
	
	std::unordered_map<IDType,IDType> came_from;
	std::priority_queue<PQ_Node,std::vector<PQ_Node>,std::greater<PQ_Node>> q;
	std::unordered_set<IDType> visited;
	
	q.push(PQ_Node(from,from,0));
	
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


template<typename IDType, typename WeightType>
std::unordered_map<IDType,std::pair<WeightType, IDType> > shortest_path_nnttweights(const Graph<IDType,WeightType> & G, const IDType & from, const std::unordered_map<llong,std::pair<int,int>> & available) {
	
	typedef Edge<IDType, WeightType> PQ_Node;
	
	std::unordered_map<IDType,std::pair<WeightType, IDType> > came_from;
	std::priority_queue<PQ_Node,std::vector<PQ_Node>,std::greater<PQ_Node>> q;
	std::unordered_set<IDType> visited;
	
	q.push(PQ_Node(from,from,0));
	
	while(!q.empty()) {
		PQ_Node curr = q.top();
		q.pop();
		//~ std::cerr << "Just removed " << curr.from << "->" << curr.to  << std::endl;
		
		WeightType & cw = curr.w;
		IDType & cid = curr.to;
		
		if(visited.count(cid)>0) continue;
		visited.insert(cid);
		
		came_from[curr.to] = std::pair<WeightType, IDType>(cw, curr.from);
			
		const auto neighbs = G[cid];
		//~ std::cerr << "Neighbs: " << neighbs.size() << std::endl;
		for(auto it = neighbs.cbegin(); it != neighbs.cend(); ++it) {
			const auto & n = *it;
			int wait_weight;
			if(visited.count(n.to) > 0) continue;
			
			if(available.count(n.edgeID)) {
				auto times = available.at(n.edgeID);
				
				if(times.first >= cw){
					wait_weight = times.first;
				}else{
					if(times.second == 0){
						continue;
					}else{
						wait_weight = cw + (times.second - ((cw - times.first) % times.second));
					}
				}
				
				
				
			} else {
				std::cerr << "LETHAL ALERT." << std::endl;
				exit(76);
			}

			
			q.push(PQ_Node(n.from, n.to, wait_weight+n.w));			
		}
		
		
	}	
	
	return came_from;	
}



















































#endif