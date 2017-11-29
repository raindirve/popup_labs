#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <cctype>
#include <algorithm>

typedef long long llong;
using namespace std;

std::ostream & operator<<(std::ostream & os, const std::vector<std::string> & mat) {
    for (int i = 0; i < mat.size(); ++i) {
        os << mat[i] << "\n";
    }
    return os;
}


struct Node {
    Node(char c_ = 0, bool end_ = false) : c(c_), end(end_) {}

    bool end;
    char c;
    llong count = 0;
    std::map<char, llong> children;
};




struct Dict {

    Dict() {
        nodes.push_back(Node());
    }

    llong add_node(int parent, const Node & n) {
        if (nodes[parent].children.count(n.c) == 0) {
            nodes.push_back(n);
            nodes[parent].children[n.c] = nodes.size() - 1;
        }
        return nodes[parent].children[n.c];
    }

    bool solve(const std::string & s) {
        word = s;
        int n_digits = 0;
        for (int i = 0; i < s.size(); ++i) {
            if(isdigit(s[i])) ++n_digits;
        }
        return backtrack(3,n_digits);
    }

    bool find(const std::string & s) const {
        llong nidx = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (nodes[nidx].children.count(s[i])) {
                nidx = nodes[nidx].children.at(s[i]);
            } else {
                return false;
            }
        }
        return nodes[nidx].end;
    }
    
    llong find2(const std::string & s) const {
        llong nidx = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (nodes[nidx].children.count(s[i])) {
                nidx = nodes[nidx].children.at(s[i]);
            } else {
                return -1;
            }
        }
        return nidx;
    }
    

    bool backtrack(int changes_left, int digits_left) {
        if(changes_left < digits_left) return false;
        if(find(word)) return true;
        if(changes_left == 0) return false;

        // try replacing digits first
        if (digits_left > 0) {
            for (int i = 0; i < word.size(); ++i) {
                if (isdigit(word[i])) {
                    // try replacing with all possible letters
                    char temp;
                    temp = word[i];
                    for (char c = 'a'; c <= 'z'; ++c) {                     
                        word[i] = c;
                        if(backtrack(changes_left - 1, digits_left - 1)) return true;
                    }
                    for (char c = 'A'; c <= 'Z'; ++c) {
                        word[i] = c;
                        if (backtrack(changes_left - 1, digits_left - 1)) return true;
                    }
                    
                    word[i] = temp; // backtrack
                    return false; // if it cannot replace the first digit to make a word, it cant make a word
                }
            }
            std::cout << "son, I am dissapoint\n";
        } else { // try swapping
            for (int i = 1; i < word.size(); ++i) {
                std::swap(word[i - 1], word[i]);
                if (backtrack(changes_left - 1, digits_left)) return true;
                std::swap(word[i - 1], word[i]);
            }
        }
        return false;
    }

    bool valid(int i, int j) const {
        return (i >= 0) && (i < 4) && (j >= 0) && (j < 4);
    }
    
    void dfsprint(llong idx, std::string & name, const double & tot){
		Node& t = nodes[idx];
		if(t.end) {
			cout << name << " " << (double)t.count/tot << "\n";
		}

		for(auto a : t.children){
			name.push_back(a.first);
			dfsprint(a.second, name, tot);
			name.pop_back();
		}
		return;
	}

    std::string word;
    std::string longest_word;
    std::vector<std::vector<bool>> visited;
    std::unordered_set<std::string> found_words;
    //Node root;
    std::vector<std::string> board;
    std::vector<Node> nodes;
};




int main() {
 
    Dict solver;
	
	string temp;
	llong tot = 0;
	
	getline(cin, temp);
	while(cin){
		//~ std::cout << temp << "\n";
		llong parent = 0;
		for (int j = 0; j < temp.size(); ++j) {
		    Node n(temp[j]);
		    parent = solver.add_node(parent, n);
		}
		solver.nodes[parent].end = true;		
		solver.nodes[parent].count += 1;
		
		tot++;
		getline(cin, temp);
	}

	std::string name = "";
	solver.dfsprint(0,name,double(tot)/100.0);

  



    return 0;
}

