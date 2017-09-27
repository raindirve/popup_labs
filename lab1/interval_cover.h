#ifndef ___INTERVAL_COVER___
#define ___INTERVAL_COVER___

/**
 * Implements a function for interval cover.
 *
 * @author Michal Horemuz michalh
 * @author Sean Wenstrom seanw
 */

#include <iterator>
#include <vector>
#include <iostream>
#include <utility> //pair
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

/**
 * Outputs the indexes of the minimal set of intervals from 
 * the supplied collection, that inclusively covers the entire
 * given interval.
 *
 * Takes intervals in a pair<double, double> form, an 
 * iterator to a collection of pair<double, double> intervals,
 * and an end iterator for the collection.
 *
 * Returns an empty vector on fail.
 */
template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end);

template<class iterator_type>
vector<int> cover(const pair<double, double> & interval, const iterator_type & begin, const iterator_type & end) {
	size_t size = end - begin;

	vector<pair<pair<double, double>, int>> candidates(size);

	
	iterator_type current = begin;
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
		//irrelevant element
		if (ivl_end < current_point) { continue; }

		if (ivl_start > current_point) { // current interval starts after current point
			if (maxend < current_point) { // no ivl could cover the current point
				return vector<int>(0);
			} else { // we have a winner
				chosens.push_back(maxindex);
				current_point = maxend;
				maxindex = -1;
			}
		}

		
		if (ivl_start <= current_point) { // starts before or at current point => consider this interval
			if (ivl_end > maxend) {
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
	
	// Reaching the end means we haven't completely covered the interval - fail.
	return vector<int>(0);

}


 
	    










#endif
