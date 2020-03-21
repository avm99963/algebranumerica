#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<long double> > Matrix;

int main(int argc, char* argv[]) {
  cout.setf(ios::scientific);
  cout.precision(100);

  if (argc < 2) {
    cerr << "Sisplau, digue'm de quina dimensio vols generar la matriu de Hilbert com a parametre\n";
    return 1;
  }

  int n = atoi(argv[1]);

  Matrix M(n, vector<long double>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      M[i][j] = (long double)1/(i+j+1);
    }
  }

  vector<long double> x(n, 1);
  vector<long double> b(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      b[i] += M[i][j]*x[j];
    }
  }

  cout << n << "\n";
  cout << n*n << "\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << i << " " << j << " " << M[i][j] << "\n";
    }
  }
  cout << n << "\n";
  for (int i = 0; i < n; ++i) cout << i << " " << b[i] << "\n";
}
