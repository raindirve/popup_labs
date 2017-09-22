#include "lab1.h"

/**
 * @author Michal Horemuz michalh 
 * @author Sean Wenstrom seanw
 *
 * WIP version of popup17 lab 1 implementation.
 * "Master document" - may be split for final version.
 */

template<typename T>
vector<int>
cover
(const pair<double, double> & interval,
 const T/*iterator<pair<double, double>>*/ & begin,
 const T /*iterator<pair<int, int>>*/ & end){

  //<<start, end>, old_index>

  int size = end - begin;

  vector<pair<pair<double, double>, int>> candidates(size);

  //  vector<int> indices(size);

  T current = begin;
  //  iterator<pair<int, int>> current = begin;
  for(int i = 0; i < size; ++i){
    candidates[i] = pair<pair<double, double>, int>(*current, i);
    ++current;
  }
  
  sort(candidates.begin(), candidates.end());

  

  double current_point = interval.first;
  double target = interval.second;
  double maxend = current_point;
  int maxindex = -1;
  vector<int> chosens;
  for(int i = 0; i < size; ++i){
    double ivl_start = candidates[i].first.first;
    double ivl_end = candidates[i].first.second;
    
    //irrelevant
    if(ivl_end < current_point){ continue;}
    
    //"base" case - no longer covers our point
    if(ivl_start > current_point){
      if(maxend > current_point){
	chosens.push_back(maxindex);
	current_point = maxend;
	//	maxcover = 0;
	maxindex = -1;
      }else{
	return vector<int>(0);
      }
    }
    
    //if still right of current - gap we can't cover - fail
    if(ivl_start > current_point){
      return vector<int>(0);
    }

    //standard iteration - check for max
    if(ivl_end > maxend){
      maxend = ivl_end;
      maxindex = candidates[i].second;
      if( ivl_end >= target ){
	chosens.push_back(maxindex);
	return chosens;
      }
    }
    
    
  }
  //end for
  //  if(candidates[chosens.back()].second < target) return vector<int>(0);
  return vector<int>(0);
  
}

/**
 * Return the index of the maximum value, given an array pointer.
 * WARNING: UNUSABLE: CONTAINS QUANTUM BUG
 * DOES NOT RETURN CORRECT CORRECT OUTPUT UNLESS CLOSELY MONITORED
 * TODO: debug
 *//*
template<typename T>
unsigned int maxIndex(T* a, unsigned int size){
  exit(662607004);
  unsigned int maxi = 0;
  T maxval;
  
  T* c = a;
  for(int i = 0; i < size; ++i){
    //    clog << "looping " << i << endl;

    if(*c > maxval){
      maxval = *c;
      maxi = i;
    }
    ++c;
  }
  return maxi;
}
   */
/**
 * Assumes no weights are negative! (Negative values will not matter thanks to the algorithm.)
 * 
 * Currently takes vector<int> as value vector with typedeffability to other, can probably be 
 * easily templated.
 * 
 * Can take any type that can be added, subtracted,  transitively compared, and set to -1 and 0.
 *//*
typedef int valtype;
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

      //      cerr << "Internal loop on (" << xpos << "," << ypos << ")" << endl;
      
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
   
#ifdef DEBUG  
  //debug output
  for(xpos = 0; xpos < size; ++xpos){
    printiterr(a[xpos].begin(), a[xpos].end());
    printiterr(included[xpos].begin(), included[xpos].end());
  }
  xpos = size;
#endif
  
  //find highest value on last row

  int maxpos = 0, maxval = 0; 
  for(ypos = 0; ypos <= capacity; ++ypos){
    if(a[size-1][ypos] > maxval){
      maxval = a[size-1][ypos];
      maxpos = ypos;
    }
  }
   */
  // DO NOT USE, CONTAINS QUANTUM BUG
  //  int maxpos = maxIndex<valtype>(a[size-1].data(), capacity+1);
  //int maxval = a[size-1][maxpos];
/*
  //backtrack to find included elements, will be reverse sorted by index
  ypos = maxpos;
#ifdef DEBUG
  cerr << "Maxpos: " << maxpos << endl;
#endif
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
*/
