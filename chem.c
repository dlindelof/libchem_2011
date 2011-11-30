#include "chem.h"

#define EPS 0.000001

static float fabsf(float x) {
  return x < 0 ? -x : x;
}

/*******************************/

static int sqrt_good_enough(float x, float guess) {
  if (x < 0.1) return fabsf(guess*guess - x) < EPS;
  else return fabsf(guess*guess - x)/x < EPS;
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
  if (x<0.1) return fabsf(guess*guess*guess) -x < EPS;
  else return fabsf((guess*guess*guess - x)/x) < EPS;
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
	float delta;

	delta = b*b - 4*a*c;
	if (delta >= 0) {
		return (-b - chem_sqrt(delta))/(2*a);
	} else {
		return -b/(2*a);
	}
}

/*******************************/
float chem_fmod(float x, float y) {
	while (x>=y) x -= y;
	return x;
}

/*******************************/
int chem_gcd(int a, int b) {
	if (b == 0) return a;
	else return chem_gcd(b, a % b);
}

float chem_sin(float x) {
	float term;
	if (fabsf(x) < 0.01) return x;
	else {
		term = chem_sin(x/3);
		return 3*term - 4*term*term*term;
	}
}

/*******************************/
void chem_matrix_multiply(float** A, float**B, int m, int n, int o, float**C) {
  int i,j,k;
  float sum;
  for (i=0;i<m;i++)
    for (j=0;j<o;j++) {
      sum = 0.;
      for (k=0;k<n;k++)
        sum+=A[i][k]*B[k][j];
      C[i][j] = sum;
    }
}

float chem_mean(float* v, int n) {
  float sum = 0;
  int i;
  for (i=0;i<n;i++)
    sum+=v[i];
  return sum/n;
}

float chem_var(float* v, int n) {
  float mean, sum=0;
  int i;
  mean = chem_mean(v,n);
  for (i=0;i<n;i++)
    sum+=(v[i]-mean)*(v[i]-mean);
  return sum/(n-1);
}

float chem_trace(float** M, int n) {
  float sum=0;
  int i;
  for (i=0;i<n;i++)
    sum+=M[i][i];
  return sum;
}

/*******************************/
float chem_integrate(float (*f)(float), float a, float b, int n) {
  float x = a;
  float result = f(x)/2;
  float h = (b-a)/n;
  int i;

  for (i=1; i<n; i++) {
    x += h;
    result += f(x);
  }
  result += f(b)/2;
  result *= h;
  return result;
}

float chem_root(float (*f)(float), float (*fp)(float), float x) {
  while (fabsf(f(x))>EPS)
    x -= f(x)/fp(x);
  return x;
}

float chem_fixed_point(float (*f)(float), float x) {
  float fx = f(x);
  while (fabsf(fx-x)>EPS) {
    x = fx;
    fx = f(fx);
  }
  return fx;
}

void chem_transpose(float** A, float** B, int n, int m) {
  int i,j;
  for (i=0;i<n;i++)
    for (j=0;j<m;j++)
      B[j][i] = A[i][j];
}

float chem_dot_product(float* V, float* U, int n) {
  float result = 0;
  int i;

  for (i=0;i<n;i++)
    result += V[i]*U[i];

  return result;
}

void chem_matrix_times_vector(float** M, float* V, float* U, int m, int n) {
  int i,j;

  for (i=0;i<m;i++) {
    U[i] = 0;
    for (j=0;j<n;j++)
      U[i] += M[i][j]*V[j];
  }
}
