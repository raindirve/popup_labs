/**
 * Contains a sieve for generating primes in time O(n log log n) and an associated prime counter.
 *
 * @author Sean Wenström
 * @author Michal Horemuz 
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef unsigned long long ull;


/**
 * Returns a bool-vector indicating for all odd 2<i<=n, odd_nonprimes[i] iff i is not a prime.
 * Even indices, and numbers i<3, are not to be trusted.
 */
vector<bool> odd_nonprimes(llong n){
 //sieve
  vector<bool> notprime(n+1); //note - only iter over odd #s, evens can be wrong
  
  llong target = (llong)(sqrt(n+1)) + 1;
  for(llong curr = 3; curr < target; curr += 2){
      if(!notprime[curr]){
        //any smaller nonprime is 1*c, 2*c, 3*c ... (c-1)c
        for(llong i = curr*curr; i <= n; i += 2*curr) 
        {
          notprime[i] = true;
        }
      }
  }
  return notprime;
}

/**
 * Given an odd-prime-inverse function (as from odd_nonprimes) of at least size n+1, 
 * returns the number of primes <=n.
 */
llong numprimes(llong n, const vector<bool>& notprime){
  if(n == 1) return 0; else{
    llong cum = 1; // 2 prime
    for(llong curr = 3; curr <= n; curr += 2){
      if(!notprime[curr]){
        ++cum;
      }
    }
    return cum;
  }
}