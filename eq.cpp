/**
 * @author michalh
 * @author seanw
 * WIP lab1 Linear Equation Solver
 */

#include <algorithm>
#include <stdexcept>

typedef unsigned int uint;
using namespace std;

<template typename<T>> //templated for any comparable number type
class Matrix<T>{
private:
  uint rows, cols;
  Vector<Vector<T>> outer;
  Vector<uint> first;

  

public:
  Matrix(uint r, uint c): rows(r), cols(c){
    outer(rows, Vector<T>(cols));
    first(rows);
  }

  /**
   * 
   */
  int setRow(uint idx, Vector<T> v){
    outer[idx] = v;
  }
  
  /**
   * sets row[operand] = row[operand] + mult*row[source]
   * where mult is a (possibly negative) scalar.
   * Returns the leftmost (lowest) index of the row that
   * contains a nonzero element after the operation.
   */
  int addRow(uint operand, uint source, T mult){
    Vector<T>& op = outer[operand];
    const Vector<T> & sr = outer[source];
    for(int i = 0; i < cols; ++i){
      op[i] += mult*sr[i];
    }
    if(op[first[operand]] == 0) _calcFirstRow(op);
  }

  int extendRow(uint operand, T mult){
    if(T==0) cerr << "pls don't do this" << endl;
    Vector<T>& op = outer[operand];
    for(int i = 0; i < cols; ++i){
      op[i] *= mult;
    }
  }

  /**
   * Returns the first nonzero index of the given vector.
   */
  int _calcFirstRow(Vector<T> v){
    for(int i = 0; i < v.size(); ++i){
      if(v[i]) return i;
    }
    return -1;
  }
  
  void calcFirsts(){
    for(int i = 0; i < rows; ++i){
      first[i] = _calcFirstRow(outer[i]);
    }
  }
  
  
  /**
   * Reorders the rows of the matrix to ascending first indexes,
   * i.e. first line has the furthest-to-the-left highest index
   */
  void reorder(){
    calcFirsts();
    for(int i = 0; i < cols-1; ++i){
      if(first[i] > firsts[i+1]){
	swap(first[i], first[i+1]);
	swap(outer[i], outer[i+1]);
      }
    }
  }
}





<template typename<T>> //templated for any comparable number type
                       //may do weird things with integer type systems
class LinearEquationSystem{
private:
  uint rows, columns; //cols will also be size of (implicit) variable vector and solution
  Matrix<T> m;
  bool solved = false;
  //  Vector<T> b; //"real numbers part" of equation 

  Set<uint> solutions;

  /*int eqAddRow(uint operand, uint source, int mult){
    m.addRow(operand, source, mult);
    b[operand] = b[operand]+b[source]*mult;
    }*/
public:
  LinearEquationSystem(uint r, uint c) : m(r,c+1), rows(r), columns(c){
    
  }
  


  void GaussReduce(){
    //TODO
    m.reorder();
    for(int i = 0; i < rows; i++){

    }
    solved = true;
  }

  
  Vector<T> solve(){
    //assume matrix has r rows, c+1 columns, [c] contains solutions

    // matrix is now minimally reduced to a triangular
    // matrix with values in (as close as possible to) a diagonal with last-row values
    GaussReduce();


    Vector<T> values(columns);
    //
    for(int i = 0; i < rows; ++1){
      if(m.first[i] == columns){ //0+0+0+0+0... = 3
	inconsistent = true;
      }else if(m.first[i] == 0){
	break;
      }else{
	solutions.add(i);
	
      }
    }
  }
  
  Vector<uint> solutions(){
    if(solved){
      return solutons;
    }else{
      throw invalid_argument("queried for solutions of unsolved system");
    }
  }


  
}
