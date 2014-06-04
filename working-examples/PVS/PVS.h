/*
PVS definitions
*/
#ifndef PVS_H
#define PVS_H

#include<stdio.h>
#include<stdlib.h>
#include <gmp.h>

// -------- BigInt --------

// typedef __mpz_struct BigInt;
typedef mpz_t BigInt;
typedef BigInt Rational;  // for now...
typedef BigInt number; // for now...


BigInt pvsInt(const char* s);
BigInt pvsAdd(const BigInt a, const BigInt b);
BigInt pvsSub(const BigInt a, const BigInt b);
BigInt pvsNeg(const BigInt a);
BigInt pvsTimes(const BigInt a, const BigInt b);
int intEq(const BigInt a, const BigInt b);
int pvsLe(const BigInt a, const BigInt b);
int pvsGe(const BigInt a, const BigInt b);
int pvsLeq(const BigInt a, const BigInt b);
int pvsGeq(const BigInt a, const BigInt b);


// ------------ Debuging functions ------------
int _debug_ = 1;
void debug(int n);
void printBigInt(BigInt a);

#endif


/*


//*/













