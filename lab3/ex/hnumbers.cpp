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
vector<bool> factors(llong n){
	
  vector<bool> notprime(n+1); //note - only iter over odd #s, evens can be wrong
  
  llong target = (llong)(sqrt(n+1)) + 1;
  for(llong curr = 5; curr < target; curr += 4){
      if(!notprime[curr]){
        //any smaller nonprime is 1*c, 2*c, 3*c ... (c-1)c
        for(llong i = curr*curr; i <= (n/5)+1; i += 4*curr) 
        {
          notprime[i] = true;
        }
      }
  }
  return notprime;
}


llong semprimes(llong n, const vector<bool>& nonprime){
    vector<llong> errvec;
	vector<llong> vec;
    for(llong curr = 5; curr <= (n/5)+1; curr += 4){
      if(!nonprime[curr]){
        vec.push_back(curr);
	cerr << "Found H-prime: " << curr << endl;
      }
    }
    llong cum = 0;
    for(size_t i = 0; i < vec.size(); ++i){
	if(vec[i]/5 > n) break;
	for(size_t j = i; j < vec.size(); ++j){
	    
	    if(vec[i]*vec[j] <= n){
		//~ cerr << "Made H-semiprime: " << vec[i] << '*' << vec[j] << '=' << vec[i]*vec[j] << endl;
		errvec.push_back( vec[i]*vec[j]);
		++cum;
	    }else break;
	}
    }
    sort(errvec.begin(), errvec.end());
    for(auto& a : errvec) cerr << a << endl;
    return cum;
}

int main(){
	
	llong n;
	
	cin >> n;
	while(n != 0)
	{
		auto res = factors(n);

		//~ for(int i = 5; i <=n; ++++++++i){
			//~ cerr << res[i] << ' ';
		//~ }
		//~ cerr << '\n';
		
		for(int i = 5; i <=n; i += 4){
			if(res[i] == 2) cerr << i << ' ';
		}

		cout<< n <<  ' ' << semprimes(n, res) << '\n';
		cin >> n;
	}
}