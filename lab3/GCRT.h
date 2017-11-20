/**
 * Header for solving systems of modular congruences, with or without coprimality.
 * @author Michal Horemuz
 * @author Sean Wenström
 */

#include "modmath.h"


typedef long long llong;



/**
 * Returns x (mod nm) where x = a mod n = b mod m
 * Requires that n*m, a, and b are 
 * less than half of LLONG_MAX, and of course
 * a < n, b < m
 */
llong crt_coprime(llong a, llong n, llong b, llong m){
  // cerr << "CRT_coprime taking " << a << " mod " << n << " = " << b << " mod " << m << endl;
  llong x, y;
  assert(gcd_recursive(n, m, x, y) == 1LL);
  // euclid(n, m, x, y);
  llong solb = mult_mod(mod(y, n), a, n) * m;
  llong sola = mult_mod(mod(x, m), b, m) * n;
  // cerr << "CRT_coprime returning " << add_mod(solb, sola, n*m) << endl;
  return add_mod(solb, sola, n*m);
}



/**
 * Returns x (mod lcm(n,m)) where x = a mod n = b mod m
 * Requires that n, m, lcm(n*m), a, and b are 
 * less than half of LLONG_MAX, and of course
 * a < n, b < m
 */
llong crt_general(llong a, llong n, llong b, llong m, llong& ret_mcm){
  llong g = __gcd(n, m);
  // cerr << "Taking " << a << " mod " << n << " = " << b << " mod " << m << endl;
  // cerr << "Found GCD " << g << endl;
  b = sub_mod(b, a, m);
  ret_mcm = n/g*m;
  if(mod(b, g)) return -1; //cannot rotate to multiple+remainder
  return add_mod(a, mult_mod(g, crt_coprime(0, n/g, b/g, m/g), ret_mcm), ret_mcm);
}