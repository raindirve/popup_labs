#ifndef ___INTERVAL_COVER___
#define ___INTERVAL_COVER___

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
#include <limits>

using namespace std;

template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end);

/**
 * returns empty vector on fail
 */
template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end) {
	size_t size = end - begin;

	vector<pair<pair<double, double>, int>> candidates(size);

	//  vector<int> indices(size);

	iterator_type current = begin;
	//  iterator<pair<int, int>> current = begin;
	for (int i = 0; i < size; ++i) {
		candidates[i] = pair<pair<double, double>, int>(*current, i);
		++current;
	}

	sort(candidates.begin(), candidates.end());


	double current_point = interval.first;
	double target = interval.second;
	double maxend = -std::numeric_limits<double>::max(); // notice the "-"
	int maxindex = -1;
	vector<int> chosens;
	for (int i = 0; i < size; ++i) {
		double ivl_start = candidates[i].first.first;
		double ivl_end = candidates[i].first.second;
		//irrelevant
		if (ivl_end < current_point) { continue; }

		if (ivl_start > current_point) { // current interval starts after curretn point
			if (maxend < current_point) { // no ivl could cover the point
				return vector<int>(0); // fial
			} else { // we have a winner
				chosens.push_back(maxindex);
				current_point = maxend;
				//std::cout << "chosen " << maxindex << "\n";
				maxindex = -1;
			}
		}

		
		if (ivl_start <= current_point) { // starts before or at current point => consider interval
			if (ivl_end > maxend) {
				//std::cout << ivl_start << "\n";
				maxend = ivl_end;
				maxindex = candidates[i].second;
				
				if (ivl_end >= target) { // win
					chosens.push_back(maxindex);
					return chosens;
				}
			}
		} else { // fail
			return vector<int>(0); // fial
		}

	}
	//end for
	//  if(candidates[chosens.back()].second < target) return vector<int>(0);
	return vector<int>(0);

}

/*typedef int valtype;
vector<int> knapsack(int capacity, const vector<valtype> & value, const vector<int> & weight);
*/

/**

 *//*
template<typename T>
unsigned int maxIndex(const T* a, unsigned int size);
   */

 
	    










#endif
