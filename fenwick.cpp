/**
* @author seanw
* @author michalh
**/


#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <limits>
//~ const int max_l = std::numeric_limits<int>::max();
//~ const int max_ll = std::numeric_limits<long>::max();


template<typename T>
void print_vec(const std::vector<T> & arr) {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}


template<typename T>
class FenwickTree {
public:

    FenwickTree(std::vector<T> vec) {
        arr = std::vector<T>(vec.size() + 1, 0);
        val = std::vector<T>(vec.size() + 1, 0);
        for (int i = 0; i < vec.size(); ++i) {
            update(i, vec[i]);
			val[i+1] = vec[i];
        }
    }

    T prefix_sum(int idx) {
        ++idx;
        T ans = 0;
        while (idx > 0) {
            ans += arr[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    void update(int idx, T x) {
        ++idx;
        int dx = x - val[idx];
        val[idx] = x;
        while (idx < arr.size()) {
            //std::cout << idx <<  " " << dx << "\n";
            arr[idx] += dx;
            idx += idx & -idx;
        }
    }
	
	void add(int idx, T dx) {
        ++idx;
        val[idx] += dx;
        while (idx < arr.size()) {
            //std::cout << idx <<  " " << dx << "\n";
            arr[idx] += dx;
            idx += idx & -idx;
        }
    }	

    void print() {
        print_vec(val);
        print_vec(arr);
    }


private:
    std::vector<T> val;
    std::vector<T> arr;
};




int main() {
	
	
	int N;
	int Q;
	
	std::cin >> N;
	std::cin >> Q;
	
	std::vector<long long> arr(N,0);
	FenwickTree<long long> fwt(arr);
	
	//~ std::cout << max_l << " " << max_ll << "\n";000000
	
	
	//~ fwt.print();
	//~ std::cout << "\n";
	char op;
	int idx;
	long long val;
	for(int n = 0; n < Q; ++n) {
		std::cin >> op;
		switch(op) {
			case '+':
				std::cin >> idx >> val;
				fwt.add(idx,val);			
				break;
			case '?':
				std::cin >> idx;
				std::cout << fwt.prefix_sum(idx-1) << "\n";
				break;			
		}
		//~ fwt.print();
		//~ std::cout << "\n";
	}
	

	
	
	
	
	return 0;
}










































