#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

/**
 * @author michalh
 * @author seanw
 * lab1 wip unionfind - adaptation of the prettier of our AUF solutions
 */


class AlmostUnionFind {
public:
  AlmostUnionFind(const long & n_) : n(n_) {
    data = std::vector<long>(n);
    parent = std::vector<long>(n);
    rank = std::vector<long>(n);
    //counter = std::vector<long>(n + 1);
    //sums = std::vector<long>(n + 1);
    
    for (long i = 0; i < n; ++i) {
      data[i] = i;
      parent[data[i]] = i;
      rank[i] = 0;
      //      counter[i] = 1;
      //      sums[i] = i;
    }
  }
  
  //long find(const long & p) {
  //	long x = data[p];
  //	while (parent[x] != x) {
  //		x = parent[x];
  //	}
  
  //	parent[data[p]] = x;
  //	//data[p] = x;
  //	return x;
  //}
  
  long find(const long & p) {
    long x = data[p];

    return find_rec(x);
  }
  
  
  long find_rec(const long & x) {
    if(parent[x] == x) return x;
    int p = parent[x];
    parent[x] = find_rec(p);
    return parent[x];
  }
  
  void unite(const long & p, const long & q) {
    long p_root = find(p);
    long q_root = find(q);
    
    if(p_root == q_root) return;
    
    if (rank[p_root] > rank[q_root]) {
      parent[q_root] = p_root;
      //counter[p_root] += counter[q_root];
      //sums[p_root] += sums[q_root];
    } else if (rank[p_root] < rank[q_root]) {
      parent[p_root] = q_root;
      //counter[q_root] += counter[p_root];
      //sums[q_root] += sums[p_root];
    } else {
      parent[q_root] = p_root;
      //counter[p_root] += counter[q_root];
      //sums[p_root] += sums[q_root];
      ++rank[q_root];
    }
    
  }

  bool query(const long & p, const long & q) {
    long p_root = find(p);
    long q_root = find(q);
    
    return (p_root == q_root);
  }
  
  /*
  void move(const long & p, const long & q) {
    long p_root = find(p);
    long q_root = find(q);
    
    if(p_root == q_root) return;
    
    data[p] = q_root;
    //++counter[q_root];
    //--counter[p_root];
    
    //sums[q_root] += p;
    //sums[p_root] -= p;
  }
  */
  /*long count(const long & p) {
    return counter[find(p)];
  }
   */
  /*
  long sum(const long & p) {
    return sums[find(p)];
  }
   */
  friend std::ostream& operator<<(std::ostream& os, const AlmostUnionFind & auf);

private:	
  long n;
  std::vector<long> data;
  std::vector<long> parent;
  std::vector<long> rank;
  std::vector<long> counter;
  std::vector<long> sums;
  
  
};

std::ostream& operator<<(std::ostream& os, const AlmostUnionFind & auf) {
  for (long i = 0; i < auf.data.size(); ++i) {
    os << auf.data[i] << " ";
  }
  os << "\n";
  
  for (long i = 0; i < auf.data.size(); ++i) {
    os << auf.parent[i] << " ";
  }
  os << "\n";
  
  
  
  return os;
}



int main() {
  
  long n, m;
  
  int c = 0;
  while(std::cin >> n >> m) {
    ++c;
    AlmostUnionFind auf(n);
    
    //std::cout << auf;
    
    char operation;
    long p, q;
    
    for (long k = 0; k < m; ++k) {
      std::cin >> operation;
      
      switch (operation) {
      case '=': // union
	std::cin >> p >> q;
	auf.unite(p,q);
	break;
	/*case 2: // move
	std::cin >> p >> q;
	auf.move(p,q);
	break;
	*/
      case '?': // prlong
	std::cin >> p >> q;			
	//std::cout << auf.count(p) << " " << auf.sum(p) << "\n";
	std::cout << ( auf.query(p, q) ? "yes" : "no" ) << '\n';
	break;
#ifdef DEBUG
      default:
	std::cerr << "Don't recognise operation " << operation << std::endl;
	exit(1);
#endif
      }
    
      
      //std::cout << auf;
    }
    
    
  }
  

  



  return 0;
}
































