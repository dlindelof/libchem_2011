#include "CppUTest/TestHarness.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern "C" {
#include "chem.h"
}

#define EPS 0.0001
#define PI 3.1415926535

TEST_GROUP(CHEM) {
  void setup() {
  }
  void teardown() {
  }
};

/*******************************/
/********* SERIE 3 *************/
/*******************************/TEST(CHEM, SquareRootOfSeveralNumbers) {
  float square;
  float root;

  for (square = 0; square < 2000.f; square += 1.5f) {
    root = chem_sqrt(square);
    /*		printf("%f is the root of %f\n", root, square);*/
    if (square < 0.01)
      DOUBLES_EQUAL(square, root*root, EPS)
    else
      DOUBLES_EQUAL(1.f, (root*root)/square, EPS)
  }
}

TEST(CHEM, CubeRootOfSeveralNumbers) {
  float cube;
  float root;

  for (cube = 1; cube < 200.f; cube += 1.5f) {
    root = chem_cbrt(cube);
    /*		printf("%f is the cube root of %f\n", root, cube);*/
    if (cube < 0.01)
      DOUBLES_EQUAL(cube, root*root*root, EPS)
    else
      DOUBLES_EQUAL(1.f, (root*root*root)/cube, EPS)
  }
}

/*******************************/
/********* SERIE 4 *************/
/*******************************/TEST(CHEM, SignOfNumber) {
  CHECK_EQUAL(1, chem_sgn(23.f));
  CHECK_EQUAL(-1, chem_sgn(-.0000001f));
  CHECK_EQUAL(0, chem_sgn(0));
}

TEST(CHEM, SmallestRoots) {
  float a, b, c;
  float x1, x2;

  for (a = 1; a < 30; a++)
    for (b = 0; b < 30; b++)
      for (c = 0; c < 40; c++) {
        if (b * b - 4 * a * c < 0)
          continue;
        //printf("a=%f, b=%f, c=%f\n", a,b,c);
        x1 = chem_smallest_root(a, b, c);
        x2 = -b / a - x1;
        DOUBLES_EQUAL(0, a*x1*x1 + b*x1 + c, EPS);
        DOUBLES_EQUAL(0, a*x2*x2 + b*x2 + c, EPS);
        CHECK(x1<x2+EPS);
      }
}

/*******************************/
/********* SERIE 5 *************/
/*******************************/TEST(CHEM, Modulus) {
  float x, y;
  int div;

  for (x = 1; x < 200.f; x += 1.5f) {
    for (y = 1; y < x; y += 1.5f) {
      div = x / y;
      DOUBLES_EQUAL(x, y*div + chem_fmod(x,y), EPS);
    }
  }
}

/*******************************/
/********* SERIE 6 *************/
/*******************************/TEST(CHEM, GCD) {
  int a, b;
  int gcd;
  for (a = 1; a < 100; a++) {
    for (b = 1; b < a; b++) {
      gcd = chem_gcd(a, b);
      // Check that gcd divides a and b
      CHECK(a % gcd == 0);
      CHECK(b % gcd == 0);
      // Check that it was the greatest divisor
      while (++gcd < b) {
        CHECK(b % gcd != 0 || a % gcd != 0);
      }
    }
  }
}

TEST(CHEM, Sine) {
  DOUBLES_EQUAL(1, chem_sin(PI/2), EPS);
  DOUBLES_EQUAL(0, chem_sin(PI), EPS);
  DOUBLES_EQUAL(chem_sqrt(2)/2, chem_sin(PI/4), EPS);
}

#define M 10
#define N 15
#define O 20

/*
 * Test matrices for matrix multiplication.
 * C = A x B
 */
float A[M][N] = { { 5, 39, 36, 30, 78, 38, 31, 93, 27, 27, 55, 89, 66, 75, 24 },
    { 91, 25, 83, 75, 49, 82, 48, 44, 61, 81, 53, 92, 50, 51, 89 }, { 95, 41, 2,
        19, 44, 54, 24, 19, 72, 3, 24, 80, 78, 48, 3 }, { 50, 10, 5, 69, 45, 36,
        85, 91, 23, 93, 49, 10, 72, 91, 49 }, { 49, 14, 17, 19, 31, 94, 20, 98,
        12, 74, 63, 27, 91, 61, 17 }, { 34, 95, 65, 37, 51, 88, 23, 44, 30, 49,
        68, 34, 90, 62, 98 }, { 91, 96, 74, 63, 52, 56, 18, 12, 32, 58, 40, 68,
        34, 86, 72 }, { 37, 58, 65, 79, 82, 63, 23, 26, 43, 24, 37, 14, 70, 81,
        51 }, { 12, 6, 46, 9, 80, 59, 44, 41, 51, 46, 99, 73, 20, 58, 48 }, {
        79, 24, 55, 93, 65, 21, 32, 60, 9, 97, 4, 11, 4, 19, 6 } };

float B[N][O] = { { 69, 44, 44, 55, 57, 59, 88, 64, 43, 29, 1, 20, 68, 85, 65,
    94, 15, 34, 95, 75 }, { 5, 83, 2, 95, 89, 23, 82, 4, 10, 68, 47, 74, 64, 84,
    55, 98, 59, 43, 33, 83 }, { 8, 9, 99, 42, 67, 39, 27, 7, 27, 70, 43, 25, 95,
    26, 73, 20, 27, 28, 68, 79 }, { 53, 14, 17, 99, 20, 59, 60, 32, 16, 7, 47,
    92, 21, 62, 53, 14, 5, 20, 44, 32 }, { 10, 18, 11, 31, 37, 26, 3, 54, 29,
    26, 78, 27, 71, 59, 100, 70, 76, 83, 84, 54 }, { 82, 40, 38, 71, 47, 30, 43,
    66, 45, 23, 33, 77, 24, 55, 22, 10, 25, 43, 77, 9 }, { 82, 84, 20, 67, 99,
    62, 32, 41, 53, 67, 79, 19, 12, 87, 11, 53, 45, 89, 17, 12 }, { 73, 81, 49,
    54, 16, 27, 17, 82, 46, 85, 48, 29, 61, 27, 11, 54, 69, 40, 87, 14 }, { 15,
    7, 34, 70, 86, 83, 18, 72, 88, 35, 4, 10, 46, 32, 7, 87, 36, 77, 99, 68 }, {
    66, 40, 96, 67, 65, 99, 43, 97, 52, 79, 18, 58, 46, 12, 41, 49, 74, 40, 52,
    50 }, { 52, 53, 93, 18, 38, 74, 10, 54, 95, 68, 73, 69, 67, 94, 45, 40, 40,
    81, 89, 19 }, { 98, 42, 6, 13, 20, 35, 60, 33, 64, 1, 48, 55, 78, 65, 37,
    68, 69, 76, 59, 50 }, { 65, 66, 74, 100, 43, 59, 48, 11, 96, 61, 16, 43, 36,
    48, 77, 75, 71, 38, 16, 15 }, { 81, 63, 27, 18, 49, 11, 70, 62, 25, 39, 35,
    65, 67, 64, 63, 53, 45, 22, 20, 6 }, { 46, 30, 43, 4, 13, 91, 70, 78, 68,
    92, 61, 65, 42, 55, 78, 35, 2, 80, 41, 86 } };

float C[M][O] = { { 40883, 34985, 28951, 34569, 30769, 30969, 28486, 35023,
    36494, 34477, 33073, 34763, 40901, 39828, 35431, 39626, 37608, 38498, 41389,
    25829 },
    { 54913, 39157, 44552, 49345, 45767, 53338, 45587, 51340, 49913, 46247,
        38793, 47745, 52169, 53853, 48582, 50104, 39107, 50982, 59353, 44948 },
    { 35468, 27892, 21375, 34306, 31068, 28764, 30240, 28827, 33489, 22800,
        20068, 26704, 32988, 37693, 29575, 40482, 28076, 32247, 37736, 25928 },
    { 48528, 39655, 36129, 43188, 36960, 42223, 34204, 45145, 39779, 42334,
        32908, 38205, 36740, 43068, 36698, 40811, 35909, 39016, 41415, 25716 },
    { 44030, 35549, 35950, 38436, 30570, 34025, 28976, 39097, 37741, 36405,
        26038, 34713, 35277, 36502, 31797, 35725, 34014, 32638, 41426, 21176 },
    { 44058, 40406, 40071, 46591, 41703, 43962, 41065, 41493, 44119, 47389,
        37030, 46579, 46389, 49720, 46931, 45878, 37350, 44611, 47966, 38824 },
    { 43694, 36522, 34959, 43878, 42493, 41894, 45244, 40624, 37707, 40196,
        33950, 44892, 48803, 50663, 47268, 47604, 34496, 41496, 48619, 42805 },
    { 36302, 31230, 31403, 42184, 36480, 35698, 34256, 34898, 34474, 35504,
        31854, 38916, 40000, 43012, 42591, 39238, 31250, 36608, 42172, 32336 },
    { 38251, 29307, 32163, 28503, 32149, 35710, 24858, 38231, 38746, 34031,
        33367, 33164, 39295, 39725, 33515, 35367, 32548, 42077, 44447, 27348 },
    { 30214, 23081, 26766, 35142, 28336, 30791, 26102, 31967, 22083, 27639,
        22811, 27401, 30920, 29602, 29973, 29837, 25168, 25447, 36600, 26939 } };

TEST(CHEM, MatrixMultiply) {

  float** M_A = chem_matrix_new(M, N);
  float** M_B = chem_matrix_new(N, O);
  float** M_C = chem_matrix_new(M, O);
  int i, j;

  /* copy A to M_A and B to M_B */
  memcpy(M_A[0], A[0], M * N * sizeof(float));
  memcpy(M_B[0], B[0], N * O * sizeof(float));

  chem_matrix_multiply(M_A, M_B, M, N, O, M_C);

  for (i = 0; i < M; i++)
    for (j = 0; j < O; j++)
      DOUBLES_EQUAL(C[i][j], M_C[i][j], EPS);

  chem_matrix_free(M_A);
  chem_matrix_free(M_B);
  chem_matrix_free(M_C);
}

TEST(CHEM, VectorMean) {
  float v[] = { 0.7943, 0.3112, 0.5285, 0.1656, 0.6020, 0.2630, 0.6541, 0.6892,
      0.7482, 0.4505 };
  float mean = chem_mean(v, 10);
  DOUBLES_EQUAL(0.52066, mean, EPS);
}

TEST(CHEM, VectorVariance) {
  float v[] = { 0.365070967053021, 0.341660328311553, 0.915387712213923,
      0.171213743884432, 0.193373411062736, 0.966211629043158,
      0.461039454334853, 0.734878282109131, 0.086795347696784,
      0.215335461216343, 0.570569912238872, 0.323566081683997,
      0.957257841426681, 0.590393498319034, 0.120141812048495,
      0.276718396567295, 0.145665094562066, 0.719139751387948,
      0.755145537055251, 0.847926149368648, 0.160876569003879,
      0.426930285328150, 0.801657242185846, 0.206384531434810,
      0.656937438648436, 0.290158896778862, 0.685802182830369,
      0.308792152487870, 0.942700205261103, 0.238910324973161 };
  float result = chem_var(v, 30);
  DOUBLES_EQUAL(0.084252143588425, result, EPS);
}

TEST(CHEM, MatrixTrace) {
  float** M_A = chem_matrix_new(M, M);
  int i, j;
  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      M_A[i][j] = A[i][j];

  DOUBLES_EQUAL(412, chem_trace(M_A, M), EPS);

  chem_matrix_free(M_A);
}

/*******************************/
/********* SERIE 8 *************/
/*******************************/

TEST(CHEM, IntegrateSineFromZeroToTwoPi) {
  float result = chem_integrate(sinf, 0, 2 * PI, 1000);

  DOUBLES_EQUAL(0, result, EPS);
}

TEST(CHEM, IntegrateSineFromZeroToPi) {
  float result = chem_integrate(sinf, 0, PI, 1000);

  DOUBLES_EQUAL(2, result, EPS);
}

TEST(CHEM, RootFindsZeroOfSin) {
  float result = chem_root(sinf, cosf, 2);

  DOUBLES_EQUAL(PI, result, EPS);
}

TEST(CHEM, FindsFixedPointOfCos) {
  float result = chem_fixed_point(cosf, 1);

  DOUBLES_EQUAL(0.739, result, EPS);
}

TEST(CHEM, Transpose) {
  float** M_A = chem_matrix_new(M, N);
  float** M_B = chem_matrix_new(N, M);
  int i, j;

  /* copy A to M_A */
  memcpy(M_A[0], A[0], M * N * sizeof(float));

  chem_transpose(M_A, M_B, M, N);

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      DOUBLES_EQUAL(M_A[j][i], M_B[i][j], EPS);

  chem_matrix_free(M_A);
  chem_matrix_free(M_B);
}

TEST(CHEM, DotProduct) {
  float v[] = { 0.7943, 0.3112, 0.5285, 0.1656, 0.6020, 0.2630, 0.6541, 0.6892,
      0.7482, 0.4505 };
  float result = chem_dot_product(v, v, 10);

  DOUBLES_EQUAL(3.1317, result, EPS);
}

float D[5][10] = { { 0.171946, 0.554345, 0.751048, 0.173334, 0.418687, 0.960050,
    0.508382, 0.014056, 0.280216, 0.138072 }, { 0.131187, 0.199326, 0.500767,
    0.757852, 0.342699, 0.745347, 0.445451, 0.623754, 0.443094, 0.097774 }, {
    0.054106, 0.521988, 0.799229, 0.287897, 0.578384, 0.198533, 0.246216,
    0.069602, 0.609864, 0.540952 }, { 0.421508, 0.523226, 0.905645, 0.615777,
    0.458281, 0.705363, 0.366085, 0.886581, 0.454470, 0.370105 }, { 0.830624,
    0.284863, 0.684162, 0.637152, 0.791745, 0.041580, 0.472750, 0.144468,
    0.533211, 0.911033 } };

TEST(CHEM, MatrixTimesVector) {
  float** M_D = chem_matrix_new(5, 10);
  float V[] = { 0.7943, 0.3112, 0.5285, 0.1656, 0.6020, 0.2630, 0.6541, 0.6892,
      0.7482, 0.4505 };
  float U[5];
  float U_expect[] = { 1.8533, 2.0555, 1.9849, 2.8969, 2.9212 };
  int i;

  memcpy(M_D[0], D[0], 50 * sizeof(float));

  chem_matrix_times_vector(M_D, V, U, 5, 10);

  for (i = 0; i < 5; i++)
    DOUBLES_EQUAL(U_expect[i], U[i], EPS);

  chem_matrix_free(M_D);
}

/*******************************/
/********* SERIE 9 *************/
/*******************************/
TEST(CHEM, Fibonacci) {
  int i;
  CHECK_EQUAL(1, chem_fibonacci(1));
  CHECK_EQUAL(1, chem_fibonacci(2));
  for (i=2; i<50; i++)
    CHECK_EQUAL(chem_fibonacci(i-1)+chem_fibonacci(i-2), chem_fibonacci(i));
}

TEST(CHEM, Fact) {
  int i;
  CHECK_EQUAL(1, chem_fact(1));
  for (i=2; i<100; i++)
    CHECK_EQUAL(i*chem_fact(i-1), chem_fact(i));
}

#define RAND_N 967
#define RAND_TRIALS 10000000
TEST(CHEM, RandomInteger) {
  int counts[RAND_N] = {0};
  int i;
  double chi_square = 0;
  srand(1222);
  for (i=0; i<RAND_TRIALS; i++)
    counts[chem_rand_int(RAND_N)]++;
  for (i=0; i<RAND_N; i++)
    chi_square += (counts[i]*counts[i]);
  chi_square /= RAND_TRIALS;
  chi_square *= RAND_N;
  chi_square -= RAND_TRIALS;
  CHECK(chi_square <= 1040);
  CHECK(chi_square >= 895);
}

TEST(CHEM, RandomFloat) {
  /* Discretize 0-1 interval in RAND_N bins, and apply chi-square test */
  int counts[RAND_N] = {0};
  int i;
  double chi_square = 0;
  srand(1443);
  for (i=0; i<RAND_TRIALS; i++)
    counts[(int)(chem_rand_float(1.)*RAND_N)]++;
  for (i=0; i<RAND_N; i++)
    chi_square += (counts[i]*counts[i]);
  chi_square /= RAND_TRIALS;
  chi_square *= RAND_N;
  chi_square -= RAND_TRIALS;
  CHECK(chi_square <= 1040);
  CHECK(chi_square >= 895);
}

/*******************************/
/********* SERIE 9 *************/
/*******************************/
TEST(CHEM, FindsMaxOfSine) {
  DOUBLES_EQUAL(PI/2, chem_function_max(sinf, 0, PI), EPS);
}

static float function_max_test_function(float x) {
  return 1-(x-5)*(x-5);
}

TEST(CHEM, FindsMaxOfFunnyFunction) {
  float result = chem_function_max(function_max_test_function, 0, 10);
  DOUBLES_EQUAL(5, result, EPS);
}

#define RADIUS 5
static int circle_function(float x, float y) {
  return (x*x + y*y) <= RADIUS*RADIUS;
}

TEST(CHEM, AreaOfCircle) {
  float area = chem_monte_carlo(circle_function, -6, -6, 6, 6, 1e7);
  DOUBLES_EQUAL(PI*RADIUS*RADIUS, area, 0.01);
}
