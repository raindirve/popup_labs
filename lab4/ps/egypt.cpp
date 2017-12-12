
#include "point.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ll a, b, c;
	cin >> a >> b >> c;
	while(a != 0){
		ll a2 = sq(a), b2 = sq(b), c2 = sq(c);
		if(a2 == b2 + c2 || b2 == a2 + c2 || c2 == a2 + b2){
			cout << "right\n";
		}
		else{
			cout << "wrong\n";
		}
		cin >> a >> b >> c;
	}
}