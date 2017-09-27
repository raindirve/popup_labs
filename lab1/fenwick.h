#ifndef ___FENWICK___
#define ___FENWICK___

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




#endif






































