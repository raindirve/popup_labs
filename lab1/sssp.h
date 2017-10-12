#ifndef _POPUP17SM_SSSP_
#define _POPUP17SM_SSSP_

#include <algorithm>
#include <vector>
#include <iostream> //cerr for debug
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <functional>
#include "graph.h"



typedef long long llong;




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
		WeightType time_from_last_available;
		//~ std::cerr << "Neighbs: " << neighbs.size() << std::endl;
		for(auto it = neighbs.cbegin(); it != neighbs.cend(); ++it) {
			const auto & n = *it;
			int wait_weight;
			if(visited.count(n.to) > 0) continue;
			
			if(available.count(n.edgeID)) {
				auto times = available.at(n.edgeID);
				//std::cerr << times.first << " " << times.second << "\n";
				if(cw <= times.first){
					wait_weight = times.first;
				}else{
					if(times.second == 0){
						continue;
					} else {
						time_from_last_available = (cw - times.first) % times.second;
						if (time_from_last_available == 0) {
							wait_weight = cw + 0;
						} else {
							wait_weight = cw + times.second - time_from_last_available;
						}						
					}
				}			
			} else {
				std::cerr << "LETHAL ALERT." << std::endl;
				exit(76);
			}

			
			//std::cerr << n << " " << n.w << " : " << cw << " " << wait_weight << "\n\n";
			q.push(PQ_Node(n.from, n.to, wait_weight+n.w));			
		}
		
		
	}	
	
	return came_from;	
}



















































#endif