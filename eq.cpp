/**
 * @author michalh
 * @author seanw
 * WIP lab1 Linear Equation Solver
 */

typedef unsigned int uint;

<template typename<T>> //templated for any comparable number type
class Matrix<T>{
private:
  uint rows, cols;
  Vector<Vector<T>> outer;
  Vector<uint> 

  

public:
  Matrix(uint r, uint c): rows(r), cols(c){
    outer(rows, Vector<T>(cols));
  }

  int setRow
  
  /**
   * sets row[operand] = row[operand] + mult*row[source]
   * where mult is a (possibly negative) scalar.
   * Returns the leftmost (lowest) index of the row that
   * contains a nonzero element after the operation.
   */
  int addRow(uint operand, uint source, int mult){
    Vector<T>& op = outer[operand];
    const Vector<T> & sr = outer[source];
    for(int i = 0; i < cols; ++i){
      op[i] += mult*sr[i];
    }
  }

  

  

  
}





<template typename<T>> //templated for any comparable number type
class LinearEquationSystem{
private:
  uint rows, columns; //cols will also be size of (implicit) variable vector and solution
  Matrix<T> m;

  
  
  


  
}
