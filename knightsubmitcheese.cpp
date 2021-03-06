/**
 * @author seanw
 */

#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef unsigned long long ull;
typedef unordered_set<ull> ullset;

const ull MASK_POS = (1 << 25)-1;
const ull MASK_REST = (0-1) ^ MASK_POS;
//lowest 25 bits - 1 for black, 0 for white or blank
//rest >> 25: position of blank [0, 24]
const ull TARGET_STATE = 0b1111101111000110000100000 + (12 << 25);
//const ull TARGET_STATE_WHITEPOS = 0b0000010000110001111011111 + (12 << 25); //inverted without blank - for scoring of white

inline void epstate(ull a){
	return;
	cerr << "Blank " << ((a >> 25) / 5) << ',' << ((a >> 25) % 5);
	rep(i, 0, 25){
		if(i % 5 == 0) cerr << endl;
		cerr << (((1 << (24-i)) & a) ? '1' : '0');
	}
	cerr << endl;
}

inline bool check_add_option(ullset & new_front, ull from, ull to, ull ostate, const ullset & vis, const ullset & targets/*, int max_depth = 11*/){
	ull fbit = (ostate >> from) & 1;
	ull tbit = (ostate >> to) & 1;
	
	// ull unchanged_bits = (MASK_POS ^ ((1 << from) + (1 << to))) & ostate;
	// ull new_pos = unchanged_bits | (fbit << to) | (tbit << from);
	// ull new_state = new_pos | (to << 25);
	
	ull new_state = ((MASK_POS ^ ((1 << from) + (1 << to))) & ostate) | (fbit << to) | (tbit << from) | (to << 25);
	
	
	if( !vis.count(new_state)
			
			) {
		cerr << "Adding new state:" << endl;
		epstate(new_state);
		new_front.insert(new_state);
	}
	
	return targets.count(new_state) > 0;
}

// returns the new "frontier" of the 
unordered_set<ull> deepen(const ullset & vis, const ullset & front, const ullset & targets){
	ullset new_frontier;
	bool found_sol = false; //TODO actually tell someone we solved it
	trav(o, front){
		//right to left, up to down
		ull blank = o >> 25;
		ull active = -1;
		// cerr << blank << " is blank" << endl;
		cerr << "Deepening from state: " << endl;
		epstate(o);
		if(blank % 5 > 1 && (active = blank + 3) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		if(blank % 5 > 1 && (active = blank - 7) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		
		if(blank % 5 > 0 && (active = blank + 9) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		if(blank % 5 > 0 && (active = blank - 11) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		
		if(blank % 5 < 4 && (active = blank + 11) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		if(blank % 5 < 4 && (active = blank - 9) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		
		if(blank % 5 < 3 && (active = blank + 7) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
		if(blank % 5 < 3 && (active = blank - 3) < 25){
			if(check_add_option(new_frontier, blank, active, o, vis, targets)) found_sol = true;
		}
	}
	if(found_sol){
		cerr << "NOTICE: Solved in call ";// << Dcount << endl;
		return ullset();
	}
	if(new_frontier.size() == 0){
		cerr << "UNEXPECTED EVENT: The new frontier in call "/* << Dcount*/ << " is empty!" << endl;
		exit(1);
	}
	return new_frontier;
}

int main(){

	int cases = 0;
	cin >> cases;
	while(cases-->0){
	
		//TODO read start state
		ull start = 0;
		char xc;
		rep(i, 0, 25){
			cin >> std::noskipws >> xc;
			while(isspace(xc) && xc != ' ') cin >> std::noskipws >> xc; //because whitespace is a bitch
			switch(xc){
			case '0':
				break;
			case '1':
				start = start | (1 << (24-i));
				break;
			case ' ':
				// cerr << "Read a space!" << endl;
				start = start | ((24-i) << 25);
				break;
			}
				
		}
		
		//test
		cerr << "Read starting state: " << start << endl;
		epstate(start);
		
		
		
		if(start == TARGET_STATE){
			cout << "Solvable in 0 move(s)." << endl;
			continue;
		}
		
		
		
		unordered_map<ull, int> cheesemap;
		cheesemap.reserve(70000);
		
		#include "cheeseout"
		
		
		if(cheesemap.count(start)){
			int d = cheesemap[start];
			cout << "Solvable in " << d << " move(s)." << endl;
		} else{
			cout << "Unsolvable in less than 11 move(s)." << endl;
		}
		
		
	
	
	
	
	
	}


}