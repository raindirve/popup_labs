#include <bits/stdc++.h>
using namespace std;
typedef long long llong;

/**
 * @author seanw
 */

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef unsigned long long ull;

struct TrieNode{
  map<char, TrieNode> letters;
  //~ bool word = false;
  int num_trees = 0;
  //~ TrieNode* daddy;
  void addword(const string & s, int i){
    if(i == sz(s)){
	//~ word = true;
	num_trees += 1;
    }
    else{
      if(letters.count(s[i]) < 1) letters[s[i]] = TrieNode(s[i], this);
      letters[s[i]].addword(s, i+1);
    }
  }
  
  bool has(char c){ return letters.count(c) > 0;}
  
  
  void dfs_cerr(){
    string s;
  }
  
  
  TrieNode& operator[](char c){
    return letters[c];
  }
  
  //~ TrieNode(char c_, TrieNode* cool) :daddy(cool){}
  TrieNode(){}
};


// a (op) b eq. cmpi(a, b) (op) 0 - NOTE! SAME DEPTH.
int cmpi_(const TrieNode * a, const TrieNode * b, char ac, char bc){
  if (a == b) //standin for equality - we know same TrieNode iff same word
    return (int)(ac) - (int)(bc);
  else return cmpi_(a->daddy, b->daddy, a->c, b->c);
}
int cmpi(const TrieNode * a, const TrieNode * b){ //lexicographical_compare
  return cmpi_(a, b, '\0', '\0');
}
bool cmp(const TrieNode * a, const TrieNode * b){
  return cmpi(a, b) < 0;
}




int main(){
  int w;
  int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};


}

void dfsprint(TrieNode& t, char name[33], int d, const double tot){
	if(t.num_trees > 0)
		cout << name << " " << (double)(t.num_trees)/tot << "\n";
	for(auto a : trees.letters()){
		name[d+1] = a.first;
		dfsprint(a.second, name, d+1, tot);
	}
	name[d+1]=0;
	return;
}

int main(){
	
	//~ map<string, llong> trees;
	TrieNode root;
	string s;
	llong tot = 0;
	
	getline(cin, s);
	while(cin){
		trees.add_word(s);
		tot++;
		getline(cin, s);
	}
	
	char name[33] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	dfsprint(root, name, 0, (double)(tot/100.0));
	
	
	return 0;
	
	
}