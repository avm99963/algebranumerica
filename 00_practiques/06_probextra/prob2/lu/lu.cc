#include <iostream>
#include <cmath>
#include "pointers.h"
using namespace std;

int lu(double **a, int n, int perm[], double tol) {
  int sig = 1;

  // Inicialitzem el vector permutacio
  for (int i = 0; i < n; ++i) {
    perm[i] = i;
  }

  // Comencem fent Gauss
  for (int pas = 1; pas < n; ++pas) {
    // Mirem si cal fer intercanvi de files
    double max = 0;
    int fila = pas-1;
    for (int i = pas-1; i < n; ++i) {
      double max_el = 0;
      for (int j = pas-1; j < n; ++j) {
        if (abs(a[i][j]) > max_el) max_el = abs(a[i][j]);
      }
      if (max_el == 0) return 0;
      max_el = abs(a[i][pas-1]/max_el);
      if (max_el > max) {
        max = max_el;
        fila = i;
      }
    }

    if (fila != pas-1) {
      // Toca intercanviar files
      //cout << "Intercanviem files " << pas-1 << " i " << fila << "\n";
      sig *= -1; // Invertim el signe de la permutacio
      intercanvia(a, n, pas-1, fila);
      swap(perm[pas-1], perm[fila]);
    }

    // Mirem si el pivot esta dins de la tolerancia acceptada
    if (abs(a[pas-1][pas-1]) < tol) return 0;

    // Procedim a calcular els multiplicadors i fer les cl de files
    for (int i = pas; i < n; ++i) {
      a[i][pas-1] /= a[pas-1][pas-1];
      for (int j = pas; j < n; ++j) a[i][j] -= a[i][pas-1]*a[pas-1][j];
    }

    //print_matrix(a, n);
    //cout << "\n";
  }

  return sig;
}
