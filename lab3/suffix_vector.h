#pragma once

#define rep(i, f, t) for(int i = f; i < (t); ++i)
#define trav(a, x) for(auto& a : x)
typedef long long llong;





#include <vector>
#include <string>
#include <algorithm>


struct SuffixVector {

	SuffixVector(const std::string & s_) : s(s_) {
		// fun here
	}
	
	const int at(size_t i) const {
		return v[i];
	}
	
	std::string suffix(size_t i) const{
		return s.substr(i, s.size());
	}
	
	int count_pattern(const std::string & pattern) const{
		//initial binsrch
		int lo = 0, hi = v.size()-1;
		
		int mid = lo + (hi - lo)/2;
	}

	
	
	std::vector<int> v;
	std::string s;
};






// http://brenden.github.io/ukkonen-animation/



















