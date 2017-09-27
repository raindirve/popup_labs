#ifndef ___FENWICK___
#define ___FENWICK___

/**
 * Bit-indexed Fenwick tree implementation for
 * quick prefix sums.
 * 
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
  
    /**
     * Constructs the Fenwick tree from a given vector,
     * maintaining its internal order.
     */
    FenwickTree(std::vector<T> vec) {
        arr = std::vector<T>(vec.size() + 1, 0);
        val = std::vector<T>(vec.size() + 1, 0);
        for (int i = 0; i < vec.size(); ++i) {
            update(i, vec[i]);
            val[i+1] = vec[i];
        }
    }

    /**
     * Outputs the prefix sum of the given index, inclusive.
     */
    T prefix_sum(int idx) {
        ++idx;
        T ans = 0;
        while (idx > 0) {
            ans += arr[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    /**
     * Sets the new value of the element at
     * index idx to x, updating the sums.
     */
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

    /**
     * Adds the provided difference to the element
     * at index idx, updating sums.
     */
    void add(int idx, T dx) {
        ++idx;
        val[idx] += dx;
        while (idx < arr.size()) {
            //std::cout << idx <<  " " << dx << "\n";
            arr[idx] += dx;
            idx += idx & -idx;
        }
    }	

    /**
     * Prints the internal arrays for the values
     * and the partial sums. Primarily for debugging purposes.
     */
    void print() {
        print_vec(val);
        print_vec(arr);
    }


private:
    std::vector<T> val;
    std::vector<T> arr;
};




#endif














