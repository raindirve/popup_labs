#include <bits/stdc++.h>
#include "hashing.h"

using namespace std;
typedef long long ll;
typedef unsigned long long ull;


int main(){
	string s;
	cin >> s;
	PolyHash<string> ph(s);
	int q;
	cin >> q;
	while(q-->0){
		size_t L, R;
		cin >> L >> R;
		cout << (ph.query(L, R-1)) << '\n';
	}
}