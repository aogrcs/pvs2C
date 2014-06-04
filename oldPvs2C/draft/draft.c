/*
Typical pvs2C output

PVS Code:

a:int = 2

*/


#include<stdio.h>
#include "PVSprelude.h"


//

// Defines the type [int -> int]
typedef BigNum (*int_int)(BigNum);
typedef BigNum (*int_int_int_int)(BigNum, BigNum, BigNum);




//PVS : a:int = 2
int a() {
  return 2;
}
int _a() {
  return 2;
}
int a!() {
  return 2;
}

// PVS : b(x:int):int = x+1
int_int b() {
  return _b;
}
int _b(int x) {
  return x+1;
}
int a!(int x) {
  return x+1;
}

// PVS :  c:int = let inc = b in inc(0)
int_int inc = b();
int c = (*inc)(0)

// or
int c_expr(int_int inc) = inc(0);
int c = c_expr( b() );



// PVS :  add(a:int,b:int):[int -> int] =
//   lambda(x:int):x+a+b



lambda_1(int a,b,x) {
  return x + a + b;
}
struct lambda_1_s {
  int arg_a, int_argb
  int int_int_int_int f
}
int eval(lambda_1_s l, int x) {
  return l.f(l.arg_a, l.arg_b, x);
}




// Choose between curry form and partial evaluations


lambda_1(int a,b,x) {
  return x + a + b;
}


int f(void* a) {
  b = *(BigNum*)a

}


typedef int (*int_void)(void*);
typedef int (*eval_fun)(void);





//  Header

struct int_lambda {
  void* args;
  int body(void*);
}

typedef int int_void(void*);

int_lambda mk_int_lambda( int_void f , void* args ) {
  int_lambda res;
  res.args = args;
  res.body = f;
  return res;
}
passArg(int_lambda l, int i , void* arg) {
  l.args[i] = arg;
}
eval(int_lambda l) {
  return l.body( l.args );
}

// add : [int,int -> int -> int ]





// PVS :  add(a:int,b:int):[int -> int] =
//   lambda(x:int): a*x + b

int add_body_1(void* args) {
  Bignum a = (BigNum)args[0];
  Bignum b = (BigNum)args[1];
  Bignum x = (BigNum)args[2];
  return add( times(a,x), b);
}

int_lambda add(BigNum a, BigNum b) {
  return mk_int_lambda( body_1, [a,b, null] )
}


// PVS :  c = let inc = add(1,1) in inc(0)
int_lambda inc = add(1, 1);
passArg(l, 0);
int c = eval(inc);  // eval(inc, 0);


























