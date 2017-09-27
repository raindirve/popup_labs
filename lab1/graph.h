#ifndef ___L1UTIL___
#define ___L1UTIL___

#include <iostream>
#include <vector>
#include <valarray>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>


template<typename T>
struct Node {
	Node(int id_) : id(id_) {}
	
	int id;
	std::vector<std::pair<T,Node*>> neighbors;	
};


template<typename T>
class Graph {
public:
	
	Graph(const std::vector<int> & froms, const std::vector<int> & tos, const std::vector<T> & weights) {
		for(int i = 0; i<froms.size(); ++i) {
			std::pair<int,std::pair<T,int>> pa = std::pair<int,std::pair<T,int>>(froms[i], std::pair<T,int>(weights[i],tos[i]));
			nodes.insert(pa);			
		}
	}
	
	/**
	 * Includes the start element in the path.
	 * 
	 * Returns <0, emptyvector> on fail.
	 */
	std::pair<T,std::vector<int>> get_path(int from, int to) const {
		static int last_from = from;
		static std::priority_queue<std::pair<T, int>> q;
		static std::unordered_set<int> visited;
		static std::unordered_map<int,std::pair<T,int>> came_from;  // maps from id to previous_id and path weight until id
		if(last_from != from){
			last_from = from;
			q.clear();
			visited.clear();
			
			q.push(std::pair<T, int>(0,from));
			came_from[from] = std::pair<T, int>(0, from);
		}else{
			if(visited.count(to)){
				return backtrack(to, came_from);			
			}
		}
		
		
		while(!q.empty()) {
			std::pair<T, int> current = q.top();
			q.pop();
			if(visited.count(current.second)) continue;
			
			visited.insert(current.second);
			
			if(current.second == to){ //win: backtrack
				return backtrack(to, came_from);
			}
			
			auto neighpair = nodes.equal_range(current.second);
			for(auto it = neighpair.first; it != neighpair.second; ++it){
				q.push(std::pair<T, int>(current.first + it->first, it->second)); 
			}
		}
		//we know we've found all nodes reachable from 'from', and not reached 'to'
		
		

		
		
		
		
		return std::pair<T, std::vector<int>>();	
		
		
	}
	
	
	std::vector<std::pair<T,int>> get_neighbors(int id) const {
		auto pi = nodes.equal_range(id);
		
		std::vector<std::pair<T, int>> out(pi.second-pi.first);
		int i = 0;
		for(auto it = pi.first; it != pi.second; ++it, ++i) {
			out[i] = *it;
		}
	
		return out;
	}
	
	
	
	
private:
	inline std::pair<T,std::vector<int>> backtrack(int to, const std::unordered_map<int,std::pair<T,int>> & came_from) const {
		std::vector<int> path;
		int id = to;
		T dist = came_from[id].first;				
		while(came_from[id] != id) {
			path.push_back(came_from[id].second);
			id = came_from[id];
		}
		path.push_back(came_from[id].second);		
		std::reverse(path.begin(),path.end());				
		return std::pair<T,std::vector<int>>(dist, path);
	}






	std::unordered_multimap<int,std::pair<T,int>> nodes;
	
	
};

























#endif
