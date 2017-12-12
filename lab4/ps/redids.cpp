
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef long long llong;
typedef long double ld;




int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	llong G;
	std::cin >> G;
	
	
	std::bitset<1000000> nuqid(0);
	
	llong temp;
	std::vector<llong> sins;
	sins.reserve(G);
	while(G --> 0) {		
		std::cin >> temp;		
		sins.push_back(temp);		
	}
	
	for(int m = sins.size(); m<1e6-1; ++m) {
		bool found = true;
		nuqid.reset();
		for(llong & s : sins) {
			temp = s % m;
			if(nuqid[temp]){
				found = false;
				break;
			}
			nuqid.set(temp);//[temp] = 1
		}
		if(found){
			cout << m << '\n';
			break;
		}
	}
	return 0;
	
}