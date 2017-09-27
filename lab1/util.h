#ifndef ___L1UTIL___
#define ___L1UTIL___

#include <iostream>
#include <vector>

template<class iterator_type>
void printiter(const iterator_type & begin, const iterator_type & end){
	iterator_type current = begin;
	while(current != end){
		std::cout << *current << ' ';
		++current;
	}
	std::cout << endl;
}

template<class iterator_type>
void printiterr(const iterator_type & begin, const iterator_type & end){
	iterator_type current = begin;
	while(current != end){
		std::cerr << *current << ' ';
		++current;
	}
	std::cerr << endl;
}


template<typename T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec) {
	for(size_t i = 0; i<vec.size()-1; ++i) {
		os << vec[i] << "\t";
	}
	if(vec.size() > 0) {
		os << vec.back();	
	}
	return os;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const std::vector<std::vector<T>> & mat) {
	for(size_t i = 0; i<vec.size(); ++i) {
		os << mat[i] << "\n";
	}
	return os;
}




#endif































