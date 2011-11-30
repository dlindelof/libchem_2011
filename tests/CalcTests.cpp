#include <stdlib.h>
#include "CppUTest/TestHarness.h"

extern "C" {
#include "getop.h"
#include "getch.h"
#include "Getchar_Spy.h"
}

#define EPS 0.00001

TEST_GROUP(CALC) {
  char s[MAXOP];
  int op;

  int (*old_getchar)(void);

  void setup() {
    old_getchar = calc_getchar;
    calc_getchar = getchar_next;
  }

  void teardown() {
    calc_getchar = old_getchar;
  }
};

TEST(CALC, getopReadsANumber) {
  getchar_expect("42.23");

  op = getop(s);

  CHECK_EQUAL(NUMBER, op);
  DOUBLES_EQUAL(42.23, atof(s), EPS);
}

TEST(CALC, getopReadsNegativeNumbers) {
  getchar_expect("-9");

  op = getop(s);
  
  CHECK_EQUAL(NUMBER, op);
  DOUBLES_EQUAL(-9, atof(s), EPS);
  
}

TEST(CALC, getopReadsArithmeticOperands) {
  getchar_expect("5 9 +");

  getop(s);
  getop(s);
  op = getop(s);

  CHECK_EQUAL('+', op);
}

TEST(CALC, getopReadsSqrt) {
  getchar_expect("sqrt");

  op = getop(s);

  CHECK_EQUAL(SQRT, op);
}

TEST(CALC, getopReadsSingleLetterOperators) {
  getchar_expect("5 p");

  getop(s);
  op = getop(s);

  CHECK_EQUAL('p', op);
}

