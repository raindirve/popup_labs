/**
* @author seanw
* @author michalh
**/


#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>


template<typename IteratorType>
std::vector<int> lis(IteratorType begin, IteratorType end) {	
	std::vector<int> lis_array(end-begin,1); // longest increasing subseq ending at i
	std::vector<int> last_index(end-begin,-1); // previous index of subseq ending at i
	
	int max_idx = 0;
	int i = 0;
	for(IteratorType it = begin;it!=end;++it,++i) {
		int j = 0;
		for(IteratorType it2 = begin; it2 != it; ++it2,++j) {
			if(*it > *it2 && lis_array[i] < lis_array[j] + 1) {
				lis_array[i] = lis_array[j] + 1;
				last_index[i] = j;
				if(lis_array[i] > lis_array[max_idx]) {
					max_idx = i;
				}
			}		
		}
	}
	
	
	int max_val = lis_array[max_idx];
	std::vector<int> ret(max_val);
	int idx = max_idx;
	i = 0;
	while(idx != -1) {
		ret[i] = idx;		
		idx = last_index[idx];		
		++i;		
	}
	
	std::reverse(ret.begin(),ret.end());
	return ret;
}

using namespace std;

template<typename IteratorType>
std::vector<int> lis2(const IteratorType & begin, const IteratorType & end) {	
	std::vector<int> lis_array(end-begin+1,-1); // index of last element of subseq of length i
	std::vector<int> last_index(end-begin,-1); // previous index of index in the longest subseq
	//~ cerr << "hello" << endl;
	lis_array[1] = 0;
	
	
	int max_len = 1;
	int i = 1;
	for(IteratorType it = begin+1;it!=end;++it,++i) {
		int lo = 1;
		int hi = max_len;
		int mid;
		while(lo <= hi) { // find largest subseq size where the last element is less than current element
			mid = ceil((lo+hi)/2);
			//~ cerr << lis_array[mid] << " lis_array[mid]" << endl;
			if(*(begin + lis_array[mid]) < *(begin+i)) {
				lo = mid+1;
			} else {
				hi = mid-1;
			}
		}
		//~ cerr << i << "is I" << endl;
		//~ cerr << lo << " is lo" << endl;
		int current_length = lo; // lo is 1 past the largest subseq size with last element less than current element
		
		//~ if(i >= last_index.size()) std::cerr << "HELP124" << i << " len, size " << last_index.size() << '\n';
		//~ if(current_length >= lis_array.size()) std::cerr << "HELP34" << current_length << " len, size " << lis_array.size() << '\n';
		
		//~ cerr << "i: " << i << ", current_length: " << current_length << " ,lis_array[current_length-1]: " << lis_array[current_length-1] << "\n"; 
		
		last_index[i] = lis_array[current_length-1]; // update with new element
		lis_array[current_length] = i;
		
		if(current_length > max_len) {
			max_len = current_length;
		}
	}
	
	//~ cerr << i << " last I" << endl;

	//~ exit(1);
	std::vector<int> ret(max_len);
	int idx = lis_array[max_len];
	i = 0;
	while(idx != -1) {
		//~ cerr << idx << "is IDX, " << i << " is I" << endl;
		ret[i] = idx;		
		idx = last_index[idx];		
		++i;		
	}
	
	std::reverse(ret.begin(),ret.end());
	return ret;
}




template<typename T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec) {
	if(vec.size() == 0) return os;
	for(int i = 0; i<vec.size()-1; ++i) {
		os << vec[i] << " ";
	}		
	os << vec.back();
	return os;
}






int main() {
	
	
	int n;
	while(std::cin >> n) {
		std::vector<int> arr(n);
		for(int i = 0; i<n; ++i) {
			std::cin >> arr[i];
		}
		
		std::vector<int> ans = lis2(arr.begin(),arr.end());
		std::cout << ans.size() << "\n" << ans << "\n";
		
	}
	
	
	
	
	
	return 0;
}








