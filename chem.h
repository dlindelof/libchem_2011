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
