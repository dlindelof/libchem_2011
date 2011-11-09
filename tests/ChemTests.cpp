#include "CppUTest/TestHarness.h"
#include <stdio.h>

extern "C" {
#include "chem.h"
}

#define EPS 0.0001
#define PI 3.1415926535

TEST_GROUP(CHEM) {
	void setup() {}
	void teardown() {}
};

/*******************************/
/********* SERIE 3 *************/
/*******************************/
TEST(CHEM, SquareRootOfSeveralNumbers) {
	float square;
	float root;

	for (square = 0; square < 2000.f; square += 1.5f) {
		root = chem_sqrt(square);
/*		printf("%f is the root of %f\n", root, square);*/
		if (square<0.01) DOUBLES_EQUAL(square, root*root, EPS)
		else DOUBLES_EQUAL(1.f, (root*root)/square, EPS)
	}
}

TEST(CHEM, CubeRootOfSeveralNumbers) {
	float cube;
	float root;

	for (cube = 1; cube < 200.f; cube += 1.5f) {
		root = chem_cbrt(cube);
/*		printf("%f is the cube root of %f\n", root, cube);*/
		if (cube<0.01) DOUBLES_EQUAL(cube, root*root*root, EPS)
		else DOUBLES_EQUAL(1.f, (root*root*root)/cube, EPS)
	}
}

/*******************************/
/********* SERIE 4 *************/
/*******************************/
TEST(CHEM, SignOfNumber) {
	CHECK_EQUAL(1, chem_sgn(23.f));
	CHECK_EQUAL(-1, chem_sgn(-.0000001f));
	CHECK_EQUAL(0, chem_sgn(0));
}

TEST(CHEM, SmallestRoots) {
	float a, b, c;
	float x1, x2;

	for (a=1;a<30;a++)
		for (b=0;b<30;b++)
			for (c=0;c<40;c++) {
				if (b*b - 4*a*c < 0) continue;
				//printf("a=%f, b=%f, c=%f\n", a,b,c);
				x1 = chem_smallest_root(a,b,c);
				x2 = -b/a - x1;
				DOUBLES_EQUAL(0, a*x1*x1 + b*x1 + c, EPS);
				DOUBLES_EQUAL(0, a*x2*x2 + b*x2 + c, EPS);
				CHECK(x1<x2+EPS);
			}
}

/*******************************/
/********* SERIE 5 *************/
/*******************************/
TEST(CHEM, Modulus) {
	float x, y;
	int div;

	for (x = 1; x < 200.f; x += 1.5f) {
		for (y = 1; y < x; y += 1.5f) {
			div = x/y;
			DOUBLES_EQUAL(x, y*div + chem_fmod(x,y), EPS);
		}
	}
}

/*******************************/
/********* SERIE 6 *************/
/*******************************/
TEST(CHEM, GCD) {
	int a, b;
	int gcd;
	for (a = 1; a < 100; a++) {
		for (b = 1; b < a; b++) {
			gcd = chem_gcd(a,b);
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
