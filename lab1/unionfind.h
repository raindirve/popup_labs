#ifndef _POPUP17SM_UNION_
#define _POPUP17SM_UNION_

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
    
    for (long i = 0; i < n; ++i) {
      data[i] = i;
      parent[data[i]] = i;
      rank[i] = 0;
    }
  }
  
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
    } else if (rank[p_root] < rank[q_root]) {
      parent[p_root] = q_root;
    } else {
      parent[q_root] = p_root;
      ++rank[q_root];
    }
    
  }

  bool query(const long & p, const long & q) {
    long p_root = find(p);
    long q_root = find(q);
    
    return (p_root == q_root);
  }
  
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


















#endif


















