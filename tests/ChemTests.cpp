#include "CppUTest/TestHarness.h"
#include <stdio.h>

extern "C" {
#include "chem.h"
}

#define EPS 0.0001

TEST_GROUP(CHEM) {
	void setup() {}
	void teardown() {}
};

TEST(CHEM, SquareRootOfSeveralNumbers) {
	float square;
	float root;

	for (square = 1; square < 200.f; square += 1.5f) {
		root = chem_sqrt(square);
/*		printf("%f is the root of %f\n", root, square);*/
		DOUBLES_EQUAL(square, root*root, EPS);
	}
}

TEST(CHEM, CubeRootOfSeveralNumbers) {
	float cube;
	float root;

	for (cube = 1; cube < 200.f; cube += 1.5f) {
		root = chem_cbrt(cube);
/*		printf("%f is the cube root of %f\n", root, cube);*/
		DOUBLES_EQUAL(cube, root*root*root, EPS);
	}
}

TEST(CHEM, SignOfNumber) {
	CHECK_EQUAL(1, chem_sgn(23.f));
	CHECK_EQUAL(-1, chem_sgn(-.0000001f));
	CHECK_EQUAL(0, chem_sgn(0));
}

TEST(CHEM, SmallestRoots) {
	float a, b, c;
	float x1, x2;

	for (a=1;a<10;a++)
		for (b=0;b<10;b++)
			for (c=0;c<10;c++) {
				if (b*b - 4*a*c < 0) continue;
				x1 = chem_smallest_root(a,b,c);
				x2 = -b/a - x1;
				DOUBLES_EQUAL(0, a*x1*x1 + b*x1 + c, EPS);
				DOUBLES_EQUAL(0, a*x2*x2 + b*x2 + c, EPS);
				CHECK(x1<x2);
			}
}
