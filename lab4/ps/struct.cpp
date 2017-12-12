
#include "point.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


#define POPUP_PRIME ll(5) //ASCII default
#define POPUP_LPRIME (ll)(2147483647)

llong ctoidx(char x){
	return x-'A';
}

llong hash(char x){
	
}

int main(){
	const llong b = POPUP_PRIME, M = POPUP_LPRIME;
	
	string s;
	
	//~ getline(cin, s);
	
	char varname;
	string type;
	
	std::unordered_map<std::string,llong> primitive_types;
	primitive_types["int"] = 1; 
	primitive_types["real"] = 2; 
	primitive_types["char"] = 3; 
	
	
	std::vector<llong> hashes(26, 0);
	std::iota(hashes.begin(),hashes.end(),26);
	
	
	std::cin >> s;
	while(s != "--") {
		
		while(s[0] != '-') {
			
			std::cin >> varname;
			std::cin >> s;
			std::cin >> type;
			
			if(primitive_types.count(type)) {
				hashes[ctoidx(varname)] = primitive_types[type];
			} else if(type.size() == 1){
				hashes[ctoidx(varname)] = hashes[ctoidx(type[0])];
			} 
			else {
				llong chash = hashes[ctoidx(type[7])];
				while(type.back() != ')'){
					cin >> type;
					chash = ((chash * b) + hashes[ctoidx(type[0])]) % M;
					//~ chash += hashes[ctoidx(type[0])] % M;
				}
				hashes[ctoidx(varname)] = chash;
			}
			

			
			
			
			cin >> s;
		}
		
		std::unordered_map<llong, string> mupp;
		for(int i = 0; i < hashes.size(); ++i){
			if(hashes[i] != 0){
				if(mupp.count(hashes[i])){
					
					std::string ss = mupp[hashes[i]] ;
					//~ ss +=  (" " + char(i+'A'));
					ss.push_back(' ');
					ss.push_back(char(i) + 'A');
					mupp[hashes[i]] = ss;
				}else{
					//~ mupp[hashes[i]] = ""+char(i+'A');
					std::string ss;
					//~ ss +=  (" " + char(i+'A'));
					
					ss.push_back(char(i) + 'A');
					mupp[hashes[i]] = ss;
					
				}
			}
		}
		
		for(auto & a : mupp){
			cout << a.second << '\n';
		}
		cout << '\n';
		
		
		cin >> s;
	}
	
	return 0;
	
}