#include <iostream>
#include <cmath>
#include <fstream>
#include "pointers.h"
#include "lu.h"
using namespace std;

int main(int argc, char *argv[]) {
  ifstream file;
  if (argc >= 2) {
    file.open(argv[1]);
  } else {
    cerr << "Error: sisplau, especifica un fitxer d'entrada.\n";
    return 2;
  }

  int n;
  file >> n;

  cout << "Dimensio: " << n << "\n\n";

  double** A;
  A = (double**) calloc(n, sizeof(double*));
  if (A == NULL) {
    cerr << "Error: memoria insuficient.\n";
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    A[i] = (double*) calloc(n, sizeof(double));
    if (A[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      return 1;
    }
    for (int j = 0; j < n; ++j) A[i][j] = 0;
  }

  // Llegim informacio del fitxer
  int k;
  file >> k;
  for (int i = 0; i < k; ++i) {
    int r, c;
    file >> r >> c;
    file >> A[r][c];
  }

  print_matrix(A, n);

  double* b;
  b = (double*) calloc(n, sizeof(double));
  if (b == NULL) {
    cerr << "Error: memoria insuficient.\n";
    return 1;
  }
  for (int i = 0; i < n; ++i) b[i] = 0;

  file >> k;
  for (int i = 0; i < k; ++i) {
    int r;
    file >> r;
    file >> b[r];
  }

  cout << "\n";
  print_vector(b, n);

  cout << "\nAl'right, let's start with the LU party!!\n\n";

  int p[n];
  double** Aprima = copia_punter(A, n, n);
  int sig = lu(A, n, p, 10e-12);

  cout << "sig = " << sig << "\n\n";

  if (sig == 0) return 0;

  cout << "A:\n";
  print_matrix(A, n);

  cout << "\np:\n";
  print_vector(p, n);
  
  double det = sig;
  for (int i = 0; i < n; ++i) {
    det *= A[i][i];
  }
  cout << "\nDeterminant: " << det << "\n";

  // Intercanviem files d'A per obtenir PA segons P
  bool* visited;
  visited = (bool*) calloc(n, sizeof(bool));

  for (int i = 0; i < n; ++i) visited[i] = false;

  int i = 0;
  while (i < n) {
    if (!visited[i]) {
      if (!visited[p[i]] && i != p[i]) intercanvia(Aprima, n, i, p[i]);
      visited[i] = true;
      i = p[i];
    } else {
      ++i;
    }
  }

  cout << "Amb intercanvis:\n\n";
  print_matrix(Aprima, n);

  // Calculem LU
  double** mlu;
  mlu = (double**) calloc(n, sizeof(double*));
  if (mlu == NULL) {
    cerr << "Error: memoria insuficient.\n";
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    mlu[i] = (double*) calloc(n, sizeof(double));
    if (mlu[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      return 1;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mlu[i][j] = 0;
      for (int k = 0; k < n; ++k) {
        mlu[i][j] += ((i < k) ? 0 : ((i > k) ? A[i][k] : 1))*((k <= j) ? A[k][j] : 0); // Ningu sap per que, pero funciona :)
      }
    }
  }

  cout << "L*U:\n\n";
  print_matrix(mlu, n);

  double** residu = matrix_subtraction(Aprima, mlu, n, n);
  cout << "r = PA-LU:\n\n";
  print_matrix(residu, n);
}
