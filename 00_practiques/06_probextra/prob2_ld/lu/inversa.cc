#include <iostream>
#include "resol.h"
#include "pointers.h"
#include "lu.h"
using namespace std;

void inversa_nolu(double **a, double **inv_a, int n, int *perm) {
  double e[n];
  for (int j = 0; j < n; ++j) {
    // Inicialitzem e_j
    for (int i = 0; i < n; ++i) e[i] = (i == j ? 1 : 0);

    double x[n];
    resol(a, x, e, n, perm);
   
    // Escribim resultat a la columna de la matriu inversa
    for (int i = 0; i < n; ++i) inv_a[i][j] = x[i];
  }
}

int inversa(double **a, double **inv_a, int n, double *det_a, double tol) {
  // Calcula LU i cridaa a la inversa_nolu
  int perm[n];
  *det_a = (double)lu(a, n, perm, tol);

  if (det_a == 0) return 0;

  for (int i = 0; i < n; ++i) *det_a *= a[i][i];

  inversa_nolu(a, inv_a, n, perm);

  return 1;
}
