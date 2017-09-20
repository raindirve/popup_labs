#include "lab1.h"

/**

 * @author seanw
 * @author michalh
 */

int main(){
  double C;
  int n;
  cin >> C >> n;
  
  while(!cin.eof()){

    //TODO whole number double->int conversion should be safe right? denominator 1=2^0
    int c = int(c);
    
    int v, w;
    vector<int> vals(n), weis(n);
    for(int i = 0; i < n; ++i){
      cin >> v >> w;
      vals[i] = v;
      weis[i] = w;
    }
    
    vector<int> idxs = knapsack(c, vals, weis);

    cout << idxs.size() << endl;
    printiter(idxs.begin(), idxs.end());




    cin >> C >> n;
  }
}
