#pragma once

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

//~ std::vector<int> longest_suffixes(const std::string &s) {
	//~ std::vector<int> T(s.size()+1,0);
	
	//~ int pos = 1;
	//~ int match = 0;

	//~ T[0] = -1;
	
	//~ while (pos + match < s.size()) {
		//~ if(s[pos+match] == s[match]) {
			//~ T[pos+match] = ++match;			
		//~ } else if(match == 0) {
			//~ ++pos			;
		//~ } else {
			//~ pos += match - T[match];
			//~ match = T[match];
		//~ }
		
	//~ }
	
	//~ std::cout << T << "\n";

	//~ return T;

//~ }

std::vector<int> longest_suffixes(const std::string &s) {
	std::vector<int> T(s.size()+1,0);
	
	//~ std::cout << s.size() << "\n";
	
	int pos = 1;
	int match = 0;
	//~ std::cerr << " hey" << '\n';
	T[0] = -1;
	//~ std::cerr << " you" << '\n';
	while (pos < s.size()) {
		//~ std::cerr << pos << ", " << match << std::endl;
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
	
	//~ std::cout << T << "\n";
	

	return T;

}


//~ std::vector<int> matcher(const std::string & p, const std::string & s) {
	//~ std::vector<int> matches;
	//~ std::vector<int> T = longest_suffixes(p);
	//~ int pos = 0;
	//~ int match = 0;
	
	
	//~ while (pos + match < s.size()) {
		//~ if(match < p.size() && s[pos+match] == p[match]) {
			//~ ++match;			
		//~ } else if(match == 0) {
			//~ ++pos			;
		//~ } else {
			//~ pos += match - T[match];
			//~ match = T[match];
		//~ }
		
		//~ if(match == p.size()) {
			//~ matches.push_back(match);
		//~ }	
	//~ }

	//~ return matches;
	
//~ }




struct MyVec{
	std::vector<int> a;
	//~ std::string n;
	MyVec(){}
	~MyVec(){
		std::cerr << "Removing my vector." << std::endl;
		//~ delete a;
	}
};


std::vector<int> matcher(const std::string & p, const std::string & s) {
	std::vector<int> matches;
	//~ MyVec matchesmv;
	//~ std::vector<int>& matches =  matchesmv.a;
	
	
	std::vector<int> T = longest_suffixes(p);
	//~ MyVec Tmv;
	//~ Tmv.a = longest_suffixes(p);
	//~ std::vector<int>& T = Tmv.a;
	
	
	int pos = 0;
	int match = 0;
	
	//~ std::cerr << "hi\n";
	while (pos + match < s.size()) {
	//~ std::cerr << "ha\n";
		//~ std::cerr << "match: " << match  << " pos: " << pos << " ... " << s.size() << "\n";
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

	//~ std::cerr << matches.size() << "\n";
	//~ std::cerr << matches << "\n";
	return matches;
	
}




















