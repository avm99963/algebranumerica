#include <iostream>
using namespace std;

void print_vector(double* v, int n) {
  for (int i = 0; i < n; ++i) cout << v[i] << (i < n-1 ? " " : "");
  cout << "\n";
}

void print_vector(int* v, int n) {
  for (int i = 0; i < n; ++i) cout << v[i] << (i < n-1 ? " " : "");
  cout << "\n";
}

void print_matrix(double** m, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << m[i][j] << (j < n-1 ? " " : "");
    }
    cout << "\n";
  }
}

void intercanvia(double** a, const int &n, const int &i, const int &j) {
  swap(a[i], a[j]); // New and better implementation
  //for (int k = 0; k < n; ++k) swap(a[i][k], a[j][k]); // Old implementation
}

// m: files m1, n: columnes m1/files m2, k: columnes m2
double** matrix_multiplication(double** m1, double** m2, const int &m, const int &n, const int &k) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(k, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      for (int k = 0; k < n; ++k) {
        r[i][j] += m1[i][k]*m2[k][j];
      }
    }
  }
  return r;
}

// return m1 - m2
double** matrix_subtraction(double** m1, double** m2, const int &m, const int &n) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j)
      r[i][j] = m1[i][j] - m2[i][j];
  }

  return r;
}

double** copia_punter(double** a, const int &m, const int &n) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) r[i][j] = a[i][j];
  }

  return r;
}

