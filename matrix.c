#include <stddef.h>

#include "chem.h"

float** chem_matrix_new(int m, int n) {
  float** M;
  int i;
  M = malloc(m * sizeof(float*));
  if (M==NULL) return NULL;
  M[0] = malloc(m*n*sizeof(float));
  if (M[0] == NULL) {
    free(M);
    return NULL;
  }
  for (i=1; i<m; i++) {
    M[i] = M[0] + i*n;
  }
  return M;
}

void chem_matrix_free(float** M) {
  free(M[0]);
  free(M);
}
