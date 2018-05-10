#include <iostream>
#include <cmath>
#include "pointers.h"
using namespace std;

void resol(double **a, double x[], double b[], int n, int perm[]) {
  // Obtenim Pb
  bool* visited;
  visited = (bool*) calloc(n, sizeof(bool));

  for (int i = 0; i < n; ++i) visited[i] = false;

  int i = 0;
  while (i < n) {
    if (!visited[i]) {
      if (!visited[perm[i]] && i != perm[i]) {
        swap(b[i], b[perm[i]]); //intercanvia(Aprima, n, i, p[i]);
        //cout << "Exchanging " << i << " with " << perm[i] << "\n";
      }
      visited[i] = true;
      i = perm[i];
    } else {
      ++i;
    }
  }

  // Resolem Ly=b'
  double y[n];
  for (int i = 0; i < n; ++i) {
    y[i] = b[i];
    for (int j = 0; j < i; ++j) y[i] -= a[i][j]*y[j];
    //cout << i << ": " << y[i] << "\n";
  }

  // Resolem Ux=y
  for (int i = n-1; i >= 0; --i) {
    x[i] = y[i];
    for (int j = i+1; j < n; ++j) x[i] -= a[i][j]*x[j];
    x[i] /= a[i][i];
    //cout << i << ":: " << x[i] << "\n";
  }
}
