#include <bits/stdc++.h>
#include "sieve.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef unsigned long long ull;
int main(){
  cin.sync_with_stdio(false);
  cin.tie(NULL);
	
  //sieve
  llong n;
  cin >> n;
  vector<bool> notprime = odd_nonprimes(n+1); //note - only iter over odd #s, evens can be wrong
  
  llong cum = numprimes(n, notprime);
  cout << cum << endl;

  int q, t;
  llong a;
  cin >> q;
  // if(n == 1) while(q-->0) cout << 0 << '\n'; else
  while(q-->0){
    cin >> a;
    
    if(a < 3){
      t = a - 1;
    } else {
      t = (((a & 1) == 0) || notprime[a]) ? (0) : (1);
    }
    cout << t << "\n";
  }
}