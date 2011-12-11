/*
 * SERIE 3
 */

/**
 * Compute the square root of the (positive) argument.
 */
float chem_sqrt(float);

/**
 * Compute the cube root of the (positive) argument.
 */
float chem_cbrt(float);

/*
 * SERIE 4
 */

/**
 * Tell sign of argument. +1 if x>0, -1 if x<0, 0 otherwise.
 */
int chem_sgn(float);

/**
 * Return the smallest real root, or the real part of the roots of
 * the a * x^2 + b * x + c polynomial.
 */
float chem_smallest_root(float a, float b, float c);

/*
 * SERIE 5
 */

/**
 * Return the floating-point remainder of dividing x by y.
 */
float chem_fmod(float x, float y);

/*
 * SERIE 6
 */

/**
 * Return the GCD of two positive integers
 */
int chem_gcd(int a, int b);

/**
 * Return the sine of x in radians
 */
float chem_sin(float x);

/*
 * SERIE 7
 */

/**
 * Allocate an m-row, n-column matrix
 */
float** chem_matrix_new(int m, int n);

/**
 * Free a previously allocated matrix
 */
void chem_matrix_free(float**);

/**
 * Calculate the mean of a vector of floats
 */
float chem_mean(float* v, int n);

/**
 * Calculate the sample variance of a vector of floats
 */
float chem_var(float* v, int n);

/**
 * Calculate the trace of a (square) matrix of floats
 */
float chem_trace(float** M, int n);

/**
 * Multiply a matrix A(mxn) by a matric B(nxo), save result in C(mxo)
 */
void chem_matrix_multiply(float** A, float** B, int m, int n, int o, float** C);

/*
 * SERIE 8
 */

/**
 * Integrate a function between a and b with n intervals
 */
float chem_integrate(float (*f)(float x), float a, float b, int n);

/**
 * Find a root of a function with the Newton method
 */
float chem_root(float (*f)(float x), float (*fp)(float x), float x);

/**
 * Find the fixed point of a function close to x
 */
float chem_fixed_point(float (*f)(float x), float x);

/**
 * Transpose a matrix A into B
 */
void chem_transpose(float** A, float** B, int n, int m);

/**
 * Compute dot product between two vectors
 */
float chem_dot_product(float* V, float* U, int n);

/**
 * Multiply a n-vector by a m-by-n matrix, put result in m-vector U
 */
void chem_matrix_times_vector(float** M, float* V, float* U, int m, int n);

/*
 * SERIE 9
 */

/**
 * Calculate nth Fibonacci number, i.e. fib(1) = 1, fib(2) = 1, etc
 */
long chem_fibonacci(int n);

/**
 * Calculate factorial of n
 */
long chem_fact(int n);

/**
 * Return a random integer between 0 and n (exclusive)
 */
int chem_rand_int(int n);

/**
 * Return a random float between 0 and x (inclusive)
 */
float chem_rand_float(float x);

/*
 * SERIE 9
 */

/**
 * Find maximum of unimodal function
 */
float chem_function_max(float (*f)(float x), float a, float b);

/**
 * Find area of given surface by Monte-Carlo integration
 */
float chem_monte_carlo(int (*f)(float x, float y), float x_min, float y_min, float x_max, float y_max, int n);
