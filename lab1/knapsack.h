#ifndef ___KNAPSACK___
#define ___KNAPSACK___

#include <iterator>
#include <vector>
#include <iostream>
#include <utility> //pair
#include <algorithm>
#include <numeric>

/**
 * @author Michal Horemuz michalh 
 * @author Sean Wenstrom seanw
 *
 * Solves the knapsack problem. Implemented as exercise in popup17 lab1 at KTH.
 */



/**
 * Assumes no weights are negative!
 * 
 * Value type is templated, weights are assumed to be ints.
 * Complexity of O(values.size() * capacity) makes high weights impractical.
 * 
 * Can take any type that can be added, subtracted,  transitively compared, and set to -1 and 0.
 */
template<typename valtype>
vector<int> knapsack(int capacity, const vector<valtype> & value, const vector<int> & weight){
	int size = weight.size()+1;

	//assert(value.size() == weight.size());
	if(value.size() != weight.size()){
		cerr << "FAIL: Passed value and weight vectors of different sizes to knapsack!" << endl;
		exit(1);
	}

	//  cerr << "Constructing for x=" << size << ", y=" << capacity+1 << endl;

	vector<vector<valtype>> a(size, vector<valtype>(capacity+1, valtype(-1)));   // [1-indexed element][total weight]
	vector<vector<bool>> included(size, vector<bool>(capacity+1));
	a[0][0] = 0; //start point, no elm included, no value

	int xpos, ypos, target, myweight;
	valtype sum;
	for(xpos = 1; xpos < size; ++xpos){
		for(ypos = 0; ypos <= capacity; ++ypos){
			//Question: include this item or no?

			sum = a[xpos-1][ypos];
			if(a[xpos-1][ypos] == -1) continue; //this cell has not been reached

			//TODO??? cut away all heavier, less valuable, than last line's maxvalue?

			//case: don't include this item
			target = a[xpos][ypos];
			if(target < sum){
				included[xpos][ypos] = false;
				a[xpos][ypos] = sum;
			}


			//case: include this item
			myweight = ypos + weight[xpos-1];
			sum += value[xpos-1];
			if(myweight > capacity){
				continue; //including would exceed weight limit
			}
			
			target = a[xpos][myweight];
			if(target < sum){
				included[xpos][myweight] = true;
				a[xpos][myweight] = sum;
			}


		}
	}
  

  
	//find highest value on last row

	int maxpos = 0, maxval = 0; 
	for(ypos = 0; ypos <= capacity; ++ypos){
		if(a[size-1][ypos] > maxval){
			maxval = a[size-1][ypos];
			maxpos = ypos;
		}
	}

	// DO NOT USE, CONTAINS QUANTUM BUG
	//  int maxpos = maxIndex<valtype>(a[size-1].data(), capacity+1);
	//int maxval = a[size-1][maxpos];

	//backtrack to find included elements, will be reverse sorted by index
	ypos = maxpos;

	vector<int> backtrack;
	for(xpos = size-1; xpos > 0; --xpos){
		if(included[xpos][ypos]){
			backtrack.push_back(xpos-1);
			ypos -= weight[xpos-1];
			//      cerr << "Found one!" << endl;
		}
	}

	return backtrack;
}

#endif
