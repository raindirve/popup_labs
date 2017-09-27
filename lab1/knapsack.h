#ifndef ___LAB1
#define ___LAB1

/**
 * @author Michal Horemuz michalh
 * @author Sean Wenstrom seanw
 *
 * WIP version of popup17 lab 1 implementation.
 * "Master document" - may be split for final version. 
 */

#include <iterator>
#include <vector>
#include <iostream>
#include <utility> //pair
#include <algorithm>
#include <numeric>

using namespace std;


/**
 * returns empty vector on fail
 */
template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end);


typedef int valtype;
vector<int> knapsack(int capacity, const vector<valtype> & value, const vector<int> & weight);


/**

 */
template<typename T>
unsigned int maxIndex(const T* a, unsigned int size);

template<class iterator_type>
void printiter(const iterator_type & begin, const iterator_type & end){
iterator_type current = begin;
while(current != end){
cout << *current << ' ';
++current;
}
cout << endl;
}

template<class iterator_type>
void printiterr(const iterator_type & begin, const iterator_type & end){
iterator_type current = begin;
while(current != end){
cerr << *current << ' ';
++current;
}
cerr << endl;
}
 
	    










#endif
