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
 * h-numbers
 */
vector<llong> funfactors(llong n){
 //sieve
  vector<llong> factors(n+1); //number of factors for valid h-numbers
  
  llong target = (llong)((n+1)/5) + 1;
  //~ llong count = 0;
  for(llong curr = 5; curr < target; curr += 4){
      if(factors[curr] == 0){
        //~ //any smaller nonprime is 1*c, 2*c, 3*c ... (c-1)c
	//~ llong csq = curr * curr;
        for(llong i = curr+4*curr; i <= n; i += 4*curr) 
        {
          factors[i] += 1;
        }
	//~ for(llong i = curr*curr; i <= n; i += 4*curr*curr) 
        //~ {
          //~ factors[i] += 1;
	  //~ if((i / curr) % csq == 0) factors[i] += 2;
        //~ }
	for(llong i = curr*curr, ctr = 1; i <= n && i > 0; i *= curr, ++ctr){
		factors[i] += ctr;
	}
	
	//~ for(llong i = curr*curr*curr*curr; i <= n && i > 0; i += 4*curr*curr*curr*curr) 
        //~ {
          //~ factors[i] += 2;
        //~ }
      }
  }
  return factors;
}

/**
 * Given an odd-prime-inverse function (as from odd_nonprimes) of at least size n+1, 
 * returns the number of primes <=n.
 */
llong semprimes(llong n, const vector<llong>& factors){
    if(n == 1) return 0; else{
    llong cum = 0; // 2 prime
    for(llong curr = 5; curr <= n; curr += 4){
      if(factors[curr] == 2){
        ++cum;
      }
    }
    return cum;
  }
}

int main(){
	
	//~ llong test;
	//~ test = 200009;
	//~ cout << test << ", " << test*test << test*test*test << ", " << test*test*test*test << ", " << 4*test*test*test*test << endl;
	
	llong n;
	
	
	auto res = funfactors(1000009);
	
	cin >> n;
	while(n != 0)
	{

		//~ for(int i = 5; i <=n; ++++++++i){
			//~ cerr << res[i] << ' ';
		//~ }
		//~ cerr << '\n';
		
		//~ for(int i = 5; i <=n; i += 4){
			//~ if(res[i] == 2) cerr << i << '\n';
		//~ }

		cout<< n <<  ' ' << semprimes(n, res) << '\n';
		cin >> n;
	}
}