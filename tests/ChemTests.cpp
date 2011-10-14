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
