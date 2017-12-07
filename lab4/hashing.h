/**
 * Implements a polynomial hash with configurable constants.
 *
 * The struct builds its hashes in O(n) arithmetic time and
 * accepts queries of the hash of a substring in constant arithmetic.
 *
 * Note that arithmetic time can be O(log n) if constants are large
 * enough to require safe modular multiplication. This is indicated
 * by toggling comments in the code, and on by default.
 *
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include <iostream>
using std::cerr;
using std::endl;

#include "modmath.h"
#include <cassert>


typedef long long ll;
typedef unsigned long long ull;

#define POPUP_PRIME ll(131) //ASCII default
#define POPUP_LPRIME ll(10939058860032031)
//log2(LPRIME) + log2(PRIME) < 61 - so LPRIME * PRIME + LPRIME still safe within LL-bounds

// #define POPUP_LPRIME ((ll)(2147483647)) 
//2^31-1 prime -> no overflow even when squared, so safe for arbitrary x*y mod M, use when collision risk < speed requirements




template <typename T> //T collection, e.g. vector, string etc
struct PolyHash{
	
	PolyHash(T s, ll bb = POPUP_PRIME, ll mm = POPUP_LPRIME) : data(s), M(mm), B(bb), forw(s.size()), bpow(s.size()) {
		// cerr << "=== CONSTRUCTION ===" << endl;
		ll hash = 0;
		ll bp = 1;
		for(size_t i = 0; i < s.size(); ++i){
			bpow[i] = (bp = mod(bp*B, M));
			forw[i] = (hash = mod(B*hash + data[i], M));
			// cerr << "for i = " << i << ", bpow[i] " << bpow[i] << ", forw[i] "<< forw[i] << endl;
		}
		// cerr << "=== END CONSTRUCTION ===" << endl;
	}
	
	/* hash of the substring from index FIRST to index LAST, inclusive */
	ll query(size_t first, size_t last){
		assert(last >= first);
		if(first == 0) return forw[last];
		
		
		ll lhs = mult_mod(forw[first-1], bpow[last-first], M);
		//ll lhs = mod(forw[first-1]*bpow[last+1-first], M);
		
    
    // cerr << lhs << " is lhs" << endl;
		// cerr << forw[last] << " is forw_last" << endl;
		
    
    return mod(forw[last] - lhs, M);
		
		
	}
	
	
	
	
	
	T data;
	llong M, B;
	vector<ll> forw; //forw[i] contains H(s_0 : s_i)
	vector<ll> bpow;
};

