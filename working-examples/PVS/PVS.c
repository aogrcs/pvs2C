// ---------- PVS definitions  -------------

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "PVS.h"

// -------- BigInt --------



void pvsInt(BigInt result, const char* s) {
  mpz_set_str( result, s, 10 );
}

void pvsAdd(BigInt result, const BigInt a, const BigInt b) {
  mpz_add( result, a, b );
}

BigInt pvsSub(const BigInt a, const BigInt b) {
  mpz_t *res = malloc( sizeof(mpz_t) );
  mpz_init( *res );
  mpz_sub( *res, a, b );
  return *res;
}

BigInt pvsNeg(const BigInt a) {
  mpz_t *res = malloc( sizeof(mpz_t) );
  mpz_init( *res );
  mpz_neg( *res, a );
  return *res;
}

BigInt pvsTimes(const BigInt a, const BigInt b) {
  mpz_t *res = malloc( sizeof(mpz_t) );
  mpz_init( *res );
  mpz_mul( *res, a, b );
  return *res;
}


// ---- BigInt comparisons -----

int intEq(const BigInt a, const BigInt b) {
  return mpz_cmp(a, b) == 0;
}

int pvsLe(const BigInt a, const BigInt b) {
  return mpz_cmp(a, b) < 0;
}

int pvsGe(const BigInt a, const BigInt b) {
  return mpz_cmp(a, b) > 0;
}

int pvsLeq(const BigInt a, const BigInt b) {
  return mpz_cmp(a, b) <= 0;
}

int pvsGeq(const BigInt a, const BigInt b) {
  return mpz_cmp(a, b) >= 0;
}







// Debugging functions
void debug(int n) {
  if (_debug_) {
    printf( "Debug: %d\n", n);
  }
}

void printBigInt(BigInt a) {
  //mpz_t aux;
  //  aux[0] = *a;
  printf("%s\n", mpz_get_str(NULL , 10, a ) );
}






/*

// -------- Closures --------

typedef BigInt int_void(void*);

struct BigIntClosure {
  void* args;
  int_void body;
};

BigIntClosure mk_int_lambda( int_void f , void* args ) {
  struct BigIntClosure res;
  res.args = args;
  res.body = f;
  return res;
}

void passArg(BigIntClosure l, int i , void* arg) {
  l.args[i] = arg;
}

BigInt eval(BigIntClosure l) {
  return l.body( l.args );
}




//*/


/*
TODO :

Destructive update for pvsAdd, pvsSubb, ...
if the number of reference on paramtere object is zero


Closures

GC

//*/






