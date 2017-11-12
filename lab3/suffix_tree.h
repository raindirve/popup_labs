#pragma once

#include <string>
#include <vector>
#include <unordered_map>


struct Node {
	Node(int id_, int begin_, int end_, int parent_ = -1, int suffix_link_ = 0) : id(id_), begin(begin_), end(end_), parent(parent_), suffix_link(suffix_link_) {}

	int id;
	int begin;
	int end;

	int parent;
	int suffix_link;

	std::unordered_map<char,int> children;
};


struct SuffixTree {

	SuffixTree(const std::string & s_) : s(s_) {
		nodes = std::vector<Node>();

		int next_id = 0;
		//int current_position = 0;

		int active_node = 0;
		char active_edge = 0;		
		int active_length = 0;
		int remainder = 0;		

		nodes.push_back(Node(next_id++,0,0)); // root from 0 to 0 (empty)
		for (int i = 0; i < s.size(); ++i) {
			int suffix_link_from = 0;
			char c = s[i];
			++remainder;
			while (remainder > 0) {
				if (active_length == 0) {
					active_edge = c;
				}

				if (nodes[active_node].children.count(active_edge) == 0) { // if node does not have a child beginning with letter
					// add node
					Node n(next_id,i,-1,active_node);
					nodes.push_back(n);
					nodes[active_node].children[active_edge] = next_id;
					++next_id;
					// --

					if (suffix_link_from != 0) { // set suffix link from
						nodes[suffix_link_from].suffix_link = active_node;						
					}
					suffix_link_from = active_node;
					
				} else { // edge exists already
					int node_idx = nodes[active_node].children[active_edge];
					// length of suffix
					Node & node = nodes[active_node];
					int node_length;
					if (node.end == -1) {
						node_length = (i+1) - node.begin;
					} else {
						node_length = node.end - node.begin;
					}

					if (active_length == node_length) { // the needed node is past this one and we know it is not a leaf node because leaf nodes size always grows.
						// set next node to active node
						active_edge = 0;
						active_length = 0;
						active_node = node_idx;
						continue; // start again from next node
					}

					if (s[node.begin + active_length] == c) { // next position matches new char -> advance i
						++active_length;
						if (suffix_link_from != 0) { // set suffix link from
							nodes[suffix_link_from].suffix_link = active_node;							
						}
						suffix_link_from = active_node;
						break; // advance i without decrementing remaining
					}

					// if we have come this far, we need to split the node...
					Node split_node(next_id,node.begin,node.begin+active_length,node.parent); //  from current node start to i
					int split_idx = next_id;					
					nodes[active_node].children[active_edge] = split_idx;
					nodes.push_back(split_node);
					++next_id;

					Node branch_node(next_id,i,-1,split_idx); // the new branch
					int branch_idx = next_id;
					nodes[split_idx].children[c] = branch_idx;
					nodes.push_back(branch_node);
					++next_id;

					// the node we are splitting now starts after the split node
					node.begin += active_length;
					char node_c = s[node.begin]; // first letter of node
					nodes[split_idx].children[node_c] = node_idx;

					if (suffix_link_from != 0) { // set suffix link from
						nodes[suffix_link_from].suffix_link = split_idx;
						suffix_link_from = split_idx;
					}
				}
				--remainder; // if we got here, we have added something
				if (active_node == 0 && active_length > 0) {
					--active_length;
					active_edge = s[i-remainder+1]; // previous letter that hasnt been added
				} else {
					active_node = nodes[active_node].suffix_link; // active node set to suffix link. suffix link == 0 means it goes back to root
				}


			}
		}

	}


	std::vector<Node> nodes;
	std::string s;
};






















