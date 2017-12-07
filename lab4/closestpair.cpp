#include "point.h"
#include <vector>

// #define DEBUG
// #define SEANW_VERIFY

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
typedef long long ll;
typedef long long llong;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;

typedef double T;
typedef Point<T> P;



int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  vector<P> points;
  points.reserve(100000);
  llong n;
  T x, y;
  cin >> n;
  while(n > 0){
    //cerr << "hlelo" << endl;
    points.clear();
    rep(i, 0, n){
      cin >> x >> y;
      points.push_back(P(x,y,i));
    }
    //cerr << "u fool" << endl;

	std::pair<Point<T>, Point<T>> a = closest_pair(points);
    cout << a.first.x << ' ' << a.first.y << ' ' << a.second.x << ' ' << a.second.y << '\n';


    //cerr << "i <3 u" << endl;






    cin >> n;
  }
}
