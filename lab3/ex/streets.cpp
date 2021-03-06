/**
 * Suffix tree for arbitrary strings of arbitrary size.
 * 
 * Should be linear time in all instances, but is kinda slow.
 * 
 * Specified for 8-bit chars, handles signed or unsigned.
 * 
 * Implements methods for searching and traversing the tree as well as finding all matches of a given string pattern.
 * 
 * @author Michal Horemuz
 * @author Sean Wenstr�m
 */


#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef unsigned long long ull;


#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <iostream>

struct Node {
    Node(int id_, int begin_, int end_, int parent_ = -1, int suffix_link_ = 0) : id(id_), begin(begin_), end(end_), parent(parent_), suffix_link(suffix_link_) {}

    int id;
    int begin;
    int end;

    int suffix = -1;

    int parent;
    int suffix_link;

    std::vector<int> children = std::vector<int>(257);
};

inline int uc(char c){
    return ((unsigned char)(c));
}


struct SuffixTree;
void dprint(SuffixTree &st);

struct SuffixTree {

    SuffixTree(const std::string &s_, const int & end_token = 256) : s(s_) {
        //~ s.push_back(end_token);
        nodes = std::vector<Node>();
        nodes.reserve(2*(s.size()+2));
        
        int next_id = 0;
        //int current_position = 0;

        int active_node = 0;
        int active_edge = 0;
        int active_pos = 0;
        int active_length = 0;
        int remainder = 0;

        nodes.push_back(Node(next_id++,0,0)); // root from 0 to 0 (empty)
        for (int i = 0; i < s.size()+1; ++i) {
            
            int c;
            if(i == s.size()) {
                c = end_token;
            } else {
                c = uc(s[i]);
            }

#ifdef DEBUG            
            //~ std::cerr << "===================" << "Printing tree on iteration " << i << " letter: " << char(c) << " edge: " << uc(c) << " ===================" << "\n";
            //~ std::cerr << "Active node: " << active_node << ", Active edge:" << active_edge << ", Remainder: " << remainder << "\n";
#endif            

            int suffix_link_from = 0;
            ++remainder;
            while (remainder > 0) {
                if (active_length == 0) {
                    active_edge = uc(c);
                    active_pos = i;
                }

                if (nodes[active_node].children[active_edge] == 0) { // if node does not have a child beginning with letter

                    // new leaf
                    nodes.emplace(nodes.begin()+next_id,next_id,i,-1,active_node);
                    nodes[next_id].suffix = i - remainder + 1;
                    nodes[active_node].children[active_edge] = next_id;
                    ++next_id;

                    if (suffix_link_from != 0) { // set suffix link from
                        nodes[suffix_link_from].suffix_link = active_node;
                    }
                    suffix_link_from = active_node;
                    
                } else { // edge exists already
                    int node_idx = nodes[active_node].children[active_edge];
                    // length of suffix
                    //~ Node & node = nodes[node_idx];
                    int node_length;
                    if (nodes[node_idx].end == -1) {
                        node_length = (i+1) - nodes[node_idx].begin;
                    } else {
                        node_length = nodes[node_idx].end - nodes[node_idx].begin;
                    }

                    if (active_length >= node_length) { // the needed node is past this one and we know it is not a leaf node because leaf nodes size always grows.
                        // set next node to active node
                        active_pos += node_length;
                        active_edge = uc(s[active_pos]);
                        active_length -= node_length;
                        active_node = node_idx;
                        continue; // start again from next node
                    }

                    int sc = uc(s[nodes[node_idx].begin + active_length]);
                    if ( uc(sc) == uc(c)) { // next position matches new char -> advance i
                        ++active_length;
                        if (suffix_link_from != 0) { // set suffix link from
                            nodes[suffix_link_from].suffix_link = active_node;
                        }
                        suffix_link_from = active_node;
                        break; // advance i without decrementing remaining
                    }
                    int split_idx;
                    // if we have come this far, we need to split the node...
                     //  from current node start to i
                    nodes.emplace(nodes.begin()+next_id,next_id,nodes[node_idx].begin,nodes[node_idx].begin+active_length,nodes[node_idx].parent);
                    split_idx = next_id;
                    nodes[active_node].children[active_edge] = split_idx;
                    //~ nodes.push_back(split_node);
                    ++next_id;

                    
                    // the new branch // new leaf
                    nodes.emplace(nodes.begin()+next_id,next_id,i,-1,split_idx);
                    nodes[next_id].suffix = i - remainder + 1;
                    nodes[split_idx].children[uc(c)] = next_id;
                    ++next_id;

                    // the node we are splitting now starts after the split node
                    nodes[node_idx].begin += active_length;
                    int node_c = uc(s[nodes[node_idx].begin]); // first letter of node
                    nodes[split_idx].children[node_c] = node_idx;
                    nodes[node_idx].parent = split_idx; 

                    if (suffix_link_from != 0) { // set suffix link from
                        nodes[suffix_link_from].suffix_link = split_idx;
                    }
                    suffix_link_from = split_idx;
                }
                --remainder; // if we got here, we have added something
                if (active_node == 0 && active_length > 0) {
                    --active_length;
                    active_edge = s[i-remainder+1]; // previous letter that hasnt been added
                    active_pos = i - remainder+1;
                } else {
                    active_node = nodes[active_node].suffix_link; // active node set to suffix link. suffix link == 0 means it goes back to root

                }
            }
#ifdef DEBUG
            //~ std::cerr << "anode " << active_node << ", " << "aedge " << active_edge << ", " << "alen " << active_length<< ", " << "remainder " << remainder << "\n";
            //~ dprint(*this);
#endif
        }

    }

    /**
     * Returns a vector of all starting positions of the given node.
     * 
     * The size of this vector will be equal to the number of matches to the string the node represents.
     */
    std::vector<int> _suffix_dfs(int nodeidx) const{
        std::vector<int> vi;
        vi.reserve(1000000);
        std::stack<int> idxs;
        idxs.push(nodeidx);
        while (!idxs.empty()) {
            int idx = idxs.top();
            idxs.pop();
            bool found = false;
            for (auto a : nodes[idx].children) {
                if(a!=0){
                    found = true;
                    idxs.push(a);
                }
            }
            if(!found) vi.push_back(nodes[idx].suffix);
        }
        return vi;
    }

    /**
     * Returns the internal node index of the arrival node after matching 
     * the pattern, or -1 if the word does not exist.
     *
     * O(|pattern|) since each character matches at most once.
     */
    int find(const std::string &pattern) {
        int nidx = 0;
        int sidx = 0;
        //~ dprint(*this);
        while (sidx < pattern.size()) {
            
            if (nodes[nidx].children[uc(pattern[sidx])]) {
                
                nidx = nodes[nidx].children[uc(pattern[sidx])];
#ifdef DEBUG
                //~ std::string q = s.substr(nodes[nidx].begin, nodes[nidx].end - nodes[nidx].begin);
                //~ std::cerr << "nidx is " << nidx << " on substr "  << q << "\n";
                //~ std::cerr << "begin " << nodes[nidx].begin << " end: " << nodes[nidx].end << " len: " << nodes[nidx].end - nodes[nidx].begin << '\n';
#endif                
                
                int end;
                if(nodes[nidx].end<0) {
                    end = s.size();
                } else {
                    end = nodes[nidx].end;
                }
#ifdef DEBUG                
                //~ std::cerr << (end - nodes[nidx].begin) << " " << pattern.size() << "\n";
                //~ std::cerr << "current substr " << q << '\n';
#endif                
		for (int i = 0; (i < (end - nodes[nidx].begin)) && (sidx+i < pattern.size()); ++i) {
                    //~ std::cerr << s[i +nodes[nidx].begin] << " " << pattern[i+sidx]<< "\n";
                    if (s[i+nodes[nidx].begin] != pattern[sidx+i]) return -1;
                }

                sidx += (end - nodes[nidx].begin);

            } else {
                return -1;
            }
        }
        return nidx;
    }

    
    /**
     * Returns a vector of all starting indexes of the 
     *
     * Linear time over O(|pattern|+k) where k is the number of matches. 
     * 
     * Could implement memoization to improve performance under multimatching / repeated polls.
     */
    std::vector<int> match(const std::string &pattern) {
        int idx = find(pattern);
        //~ std::cerr << "idx " << idx << "\n";
        if (idx == -1) return std::vector<int>(); //no match :(
        //~ std::cerr<< idx << " " << _suffix_dfs(idx).size() << "\n";
        auto a = _suffix_dfs(idx);
#ifdef DEBUG
        //~ std::string q = s.substr(nodes[idx].begin, nodes[idx].end - nodes[idx].begin);
        //~ std::cerr << q << "\n";
        //~ std::cerr<<" " << a.size() << "\n";
#endif
      return a;//_suffix_dfs(idx);
    }
    
    
    std::vector<Node> nodes;
    std::vector<int> leaves;

    std::string s;
};

//debug print tree to std::cerr
#include <queue>
void dprint(SuffixTree &st){
    std::string s = st.s;

    std::queue<std::pair<int,int>> q;
    q.push(std::pair<int,int>(0,0));

    while (!q.empty()) {
        std::pair<int,int> u = q.front();
        int idx = u.first;
        int depth = u.second;
        if(depth > 8) break;
        q.pop();

        const Node &n = st.nodes[idx];

        std::cerr << "Node: " << n.id << ", parent: " << n.parent << " string: " << s.substr(n.begin, n.end - n.begin) << " suffix: " << n.suffix << " link: " << n.suffix_link << "\n";
        std::cerr << "  " << n.begin << " " <<  n.end << "\n";
        for (int i = 0; i < n.children.size(); ++i) {
            if(!n.children[i]) continue;
            std::cerr << "  edge: " << char(i) << " id: " << n.children[i] << "\n";
            q.push(std::pair<int,int>(n.children[i],depth+1));
        }


    }
}


template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end) {
	size_t size = end - begin;

	vector<pair<pair<double, double>, int>> candidates(size);

	
	iterator_type current = begin;
	for (int i = 0; i < size; ++i) {
		candidates[i] = pair<pair<double, double>, int>(*current, i);
		++current;
	}

	sort(candidates.begin(), candidates.end());


	double current_point = interval.first;
	double target = interval.second;
	double maxend = -std::numeric_limits<double>::max(); // notice the "-"
	int maxindex = -1;
	vector<int> chosens;
	for (int i = 0; i < size; ++i) {
		double ivl_start = candidates[i].first.first;
		double ivl_end = candidates[i].first.second;
		//irrelevant element
		if (ivl_end < current_point) { continue; }

		if (ivl_start > current_point) { // current interval starts after current point
			if (maxend < current_point) { // no ivl could cover the current point
				return vector<int>(0);
			} else { // we have a winner
				chosens.push_back(maxindex);
				current_point = maxend;
				maxindex = -1;
			}
		}

		
		if (ivl_start <= current_point) { // starts before or at current point => consider this interval
			if (ivl_end > maxend) {
				maxend = ivl_end;
				maxindex = candidates[i].second;
				
				if (ivl_end >= target) { // win
					chosens.push_back(maxindex);
					return chosens;
				}
			}
		} else { // fail
			return vector<int>(0); // fial
		}

	}
	
	// Reaching the end means we haven't completely covered the interval - fail.
	return vector<int>(0);

}

#include "kmp.h"
 


int main(){
	
		//~ cin.sync_with_stdio(false);
	//~ cin.tie(0);
	
	
	int n, m;
	
	string scrap;
	getline(cin, scrap);
	
	n = stoi(scrap);
	
	string street;
	getline(cin, street);
	
	getline(cin, scrap);
	m = stoi(scrap);
	
	
	//~ return 0;
	std::vector<std::string> patterns(m);
	std::string p;
	for(int i = 0; i<m; ++i) {
		std::getline(cin, p);
		patterns[i] = p;		
	}
	//~ return 0;
	//~ std::getline(cin, p);
	//~ SuffixTree st(street);
	vector<bool> tiled(n, false);
	for(int i = 0; i<m; ++i) {
		auto vi = matcher(patterns[i], street);
		//~ return 0;
		//~ std::sort(vi.begin(), vi.end());
		
		for(auto start : vi){
			//~ cerr << start << "is cerr" << endl;
			 fill(tiled.begin()+start, tiled.begin()+start+patterns[i].size(), true);
		} 	
		//~ return 0;
		//~ cout << "\n";
	}
	//~ return 0;
	llong ctr = 0;
	for(bool b : tiled){
		if(!b)++ctr;
	}
	cout << ctr << endl;
	
	//~ std::cin >> n;
	
	
	return 0;
}



