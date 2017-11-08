#include "suffix_vector.h"
#include <iostream>
using namespace std;
int main(){
	
	string s = "haibbbsup";
	SuffixVector sv(s);
	
	sv.v = {1, 3, 4, 5, 0, 2, 8, 6, 7};
	trav(a, sv.v) cerr << sv.suffix(a) << endl;
	
}
