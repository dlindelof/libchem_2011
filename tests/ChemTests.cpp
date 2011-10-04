#include "CppUTest/TestHarness.h"

extern "C" {
#include "chem.h"
}

#define EPS 0.00001

TEST_GROUP(CHEM) {
  void setup() {}
  void teardown() {}
};

TEST(CHEM, SquareRoot) {
  float square = 2;
  float root = chem_sqrt(square);
  DOUBLES_EQUAL(square, root*root, EPS);
}

TEST(CHEM, CubeRoot) {
  float cube = 5;
  float root = chem_cbrt(cube);
  DOUBLES_EQUAL(cube, root*root*root, EPS);
}
