#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "lib/matrix.cc"
using namespace std;

typedef double Decimal;

const Decimal epsilon = 1e-8;

void comprovacio_epsilon(Decimal valor) {
  if (abs(valor) < epsilon) {
    cerr << "ERROR: La matriu es singular (" << abs(valor) << " < " << epsilon << "). No procedirem amb la descomposicio LU.\n";
    exit(2);
  }
}

void print_vector(const vector<Decimal> &v, fstream &file) {
  int n = v.size();
  for (int i = 0; i < n; ++i) {
    file << v[i] << (i < n - 1 ? " " : "");
  }
  file << "\n";
}

vector< vector<Decimal> > stridiagonal_lu(const vector<Decimal> &a, const vector<Decimal> &b, const vector<Decimal> &c, const Decimal &d, const Decimal &e, const int &n) {
  vector< vector<Decimal> > ret;
  vector<Decimal> alpha(n);
  vector<Decimal> beta(n-2);
  vector<Decimal> eps(n-1);
  vector<Decimal> delta(n-1);

  for (int i = 0; i < n-1; ++i) {
    clog << "Calculant alpha, beta amb i=" << i << "\n";
    alpha[i] = (i == 0 ? a[0] : a[i] - beta[i-1]*c[i-1]);  

    comprovacio_epsilon(alpha[i]);
    
    if (i < n-2) beta[i] = b[i]/alpha[i];
  }

  eps[0] = e;
  for (int i = 1; i < n-1; ++i) eps[i] = -beta[i-1]*eps[i-1];
  eps[n-2] += c[n-2];

  delta[0] = d/alpha[0];
  for (int i = 1; i < n-1; ++i) {
    delta[i] = -(c[i-1]*delta[i-1])/alpha[i];
    cout << "delta[" << i << "] = -" << c[i-1] << "*" << delta[i-1] << "/" << alpha[i-1] << " = " << delta[i] << "\n";
  }
  delta[n-2] += b[n-2]/alpha[n-2];

  alpha[n-1] = a[n-1];
  for (int i = 0; i < n-1; ++i) alpha[n-1] -= eps[i]*delta[i];

  clog << "Terminat de calcular la descomposicio LU\n\n";
  ret.push_back(alpha);
  ret.push_back(beta);
  ret.push_back(eps);
  ret.push_back(delta);
  return ret;
}

Decimal tridiagonal_lu_determinant(const vector<Decimal> &alpha) {
  Decimal ret = 1;
  for (int i = 0; i < (int)alpha.size(); ++i) ret *= alpha[i];

  return ret;
}

int main(int argc, char *argv[]) {
  ifstream file;
  if (argc >= 2) file.open(argv[1]);
  else {
    cerr << "Sisplau, especifica com a parametre on esta l'arxiu amb la matriu tridiagonal\n";
    return 1;
  }

  int n;
  file >> n;

  clog << "Llegint matriu A...\n";

  vector<Decimal> a(n);
  vector<Decimal> b(n-1);
  vector<Decimal> c(n-1);
  Decimal d;
  Decimal e;

  for (int i = 0; i < n; ++i) file >> a[i];
  for (int i = 0; i < n-1; ++i) file >> b[i];
  for (int i = 0; i < n-1; ++i) file >> c[i];
  file >> d;
  file >> e;

  cout << "\n";

  clog << "Calculant descomposicio LU...\n";

  vector< vector<Decimal> > result = stridiagonal_lu(a, b, c, d, e, n);

  Matrix l(n, vector<double>(n));

  cout << "Matriu L:\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == n-1 && j < n-1) l[i][j] = result[3][j];
      else if (i == j) l[i][j] = 1;
      else if (i == j+1) l[i][j] = result[1][j];
      else l[i][j] = 0;
      cout << l[i][j] << (j < n ? " " : "");
    }
    cout << "\n";
  }

  Matrix u(n, vector<double>(n));

  cout << "\nMatriu U:\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == n-1 && i < n-1) u[i][j] = result[2][i];
      else if (i == j) u[i][j] = result[0][j];
      else if (i+1 == j) u[i][j] = c[i];
      else u[i][j] = 0;
      cout << u[i][j] << (j < n ? " " : "");
    }
    cout << "\n";
  }

  clog << "Calculem la multiplicacio de les matrius L i U.\n";

  Matrix mult = matrix_multiplication(l, u);

  cout << "\nMatriu A llegida anteriorment:\n";

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) cout << a[i] << " ";
      else if (i == j+1) cout << b[j] << " ";
      else if (i+1 == j) cout << c[i] << " ";
      else if (i == n-1 && j == 0) cout << d << " ";
      else if (i == 0 && j == n-1) cout << e << " ";
      else cout << "0 ";
    }
    cout << "\n";
  }

  cout << "\nMatriu L*U:\n";

  print_matrix(mult);

  cout << "\nDeterminant: " << tridiagonal_lu_determinant(result[0]) << "\n";

  if (argc >= 3) {
    clog << "Es guardara el resultat de la descomposicio LU en l'arxiu " << argv[2] << "\n";

    fstream fileOut(argv[2], fstream::out | ios::trunc);

    fileOut << n << "\n";
    for (int i = 0; i < (int)result.size(); ++i) print_vector(result[i], fileOut);
    c.pop_back();
    print_vector(c, fileOut);
  }
}
