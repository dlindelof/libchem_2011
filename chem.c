#include "chem.h"

#define EPS 0.0001

static float fabsf(float x) {
  return x < 0 ? -x : x;
}

/*******************************/

static int sqrt_good_enough(float x, float guess) {
  return (fabsf(guess*guess - x) < EPS);
}

static float sqrt_improve(float guess, float x) {
  return (guess + x/guess)/2;
}

static float sqrt_iter(float x, float guess) {
	if (sqrt_good_enough(x, guess))
		return guess;
	else
		return sqrt_iter(x, sqrt_improve(guess, x));
}

float chem_sqrt(float x) {
  return sqrt_iter(x, 1.0);
}

/*******************************/

static float cbrt_good_enough(float x, float guess) {
  return (fabsf(guess*guess*guess - x) < EPS);
}

static float cbrt_improve(float guess, float x) {
  return (x/(guess*guess) + 2*guess)/3;
}

static float cbrt_iter(float x, float guess) {
  if (cbrt_good_enough(x, guess))
    return guess;
  else
    return cbrt_iter(x, cbrt_improve(guess, x));
}

float chem_cbrt(float x) {
  return cbrt_iter(x, 1.0);
}

/*******************************/

int chem_sgn(float x) {
	if (x<0) return -1;
	if (x>0) return 1;
	return 0;
}

/*******************************/
float chem_smallest_root(float a, float b, float c) {
	float x1, x2, delta;

	delta = b*b - 4*a*c;
	if (delta >= 0) {
		x1 = (-b + chem_sqrt(delta))/(2*a);
		x2 = (-b - chem_sqrt(delta))/(2*a);
		return x1 < x2 ? x1 : x2;
	} else {
		x1 = -b/(2*a);
		return x1;
	}
}
