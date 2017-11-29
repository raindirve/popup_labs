#pragma once
/**
 * Implements the KMP algorithm for string matching. 
 * 
 * https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * 
 * @author Michal Horemuz
 * @author Sean Wenström
 */


#include <vector>
#include <string>
#include <iostream>

template<typename T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec) {
	for(size_t i = 0; i<vec.size(); ++i) {
		os << vec[i] << "\t";
	}
	return os;
}

/**
 * Internal function to build the partial match table.
 */
std::vector<int> longest_suffixes(const std::string &s) {
	std::vector<int> T(s.size()+1,0);
	
	int pos = 1;
	int match = 0;
	T[0] = -1;
	while (pos < s.size()) {
		if(s[pos] == s[match]) {
			
			T[pos] = T[match];
			++pos;
			++match;
		} else {
			T[pos] = match;
			match = T[match];
			while(match>=0 && s[pos] != s[match]) {
				match = T[match];
			}
			++pos;
			++match;
		}		
	}
	T[pos] = match;
	

	return T;

}

/** 
 * Returns the beginning indexes of all matches of the pattern p on the string s.
 */
std::vector<int> matcher(const std::string & p, const std::string & s) {
	std::vector<int> matches;
	
	std::vector<int> T = longest_suffixes(p);
	
	int pos = 0;
	int match = 0;
	
	while (pos + match < s.size()) {
		if(s[pos+match] == p[match]) {
			++match;			
			if(match == p.size()) {
				matches.push_back(pos);
				pos = pos + match - T[match];
				match = T[match];
			}
		} else {
			
			if(T[match] >= 0) {
				pos = pos + match - T[match];
				match = T[match];
			} else {
				
				pos = pos + match + 1;
				match = 0;
			}
		}
	}

	return matches;
	
}




















