#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
#include "lib/core.cc"
#include "lib/matrix.cc"

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
    //clog << "Calculant alpha, beta amb i=" << i << "\n";
    alpha[i] = (i == 0 ? a[0] : a[i] - beta[i-1]*c[i-1]);

    cout << "alpha[" << i << "]=" << alpha[i];

    comprovacio_epsilon(alpha[i]);

    if (i < n-2) {
      beta[i] = b[i]/alpha[i];
      cout << "  beta[" << i << "]=" << beta[i] << "\n";
    }
  }

  eps[0] = e;
  cout << "\neps[0]=" << eps[0] << "\n";
  for (int i = 1; i < n-1; ++i) {
    eps[i] = -beta[i-1]*eps[i-1];
    if (i < n-2) cout << "eps[" << i << "]=" << eps[i] << "\n";
  }
  eps[n-2] += c[n-2];
  cout << "eps[" << n-2 << "]=" << eps[n-2] << "\n";

  delta[0] = d/alpha[0];
  cout << "delta[0]=" << delta[0] << "\n";
  for (int i = 1; i < n-1; ++i) {
    delta[i] = -(c[i-1]*delta[i-1])/alpha[i];
    if (i < n-2) cout << "delta[" << i << "]=" << delta[i] << "\n";
  }
  delta[n-2] += b[n-2]/alpha[n-2];
  cout << "delta[" << n-2 << "]=" << delta[n-2] << "\n";

  alpha[n-1] = a[n-1];
  for (int i = 0; i < n-1; ++i) alpha[n-1] -= eps[i]*delta[i];
  cout << "alpha[" << n-1 << "]=" << alpha[n-1] << "\n";

  clog << "\nAcabat de calcular la descomposicio LU\n\n";
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

vector<Decimal> solve_sly(const vector<Decimal> &beta, const vector<Decimal> &delta, const vector<Decimal> &p) {
  int n = beta.size() + 2;

  vector<Decimal> y(n);
  y[0] = p[0];

  for (int i = 1; i < n-1; ++i) y[i] = p[i] - beta[i-1]*y[i-1];

  y[n-1] = p[n-1];
  for (int i = 0; i < n; ++i) y[n-1] -= delta[i]*y[i];

  return y;
}

vector<Decimal> solve_sux(const vector<Decimal> &alpha, const vector<Decimal> &eps, const vector<Decimal> &c, const vector<Decimal> &y) {
  int n = alpha.size();

  vector<Decimal> x(n);

  comprovacio_epsilon(alpha[n-1], epsilon);
  x[n - 1] = y[n-1]/alpha[n-1];
  x[n - 2] = (y[n-2] - eps[n-2]*x[n-1])/alpha[n-2];

  for (int i = n - 3; i >= 0; --i) {
    comprovacio_epsilon(alpha[i], epsilon);
    x[i] = (y[i] - c[i]*x[i+1] - eps[i]*x[n-1])/alpha[i];
  }

  return x;
}

int main(int argc, char *argv[]) {
  cout.setf(ios::fixed);
  cout.precision(13);

  ifstream file;
  ifstream p_file;
  if (argc >= 3) {
    file.open(argv[1]);
    p_file.open(argv[2]);
  } else {
    cerr << "Sisplau, especifica com a parametre on esta l'arxiu amb la matriu tridiagonal i l'arxiu amb la matriu p.\n";
    return 1;
  }

  int n;
  file >> n;

  cout << "Llegint matriu A de mida " << n << "...\n";

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

  cout << "Calculant descomposicio LU...\n";

  vector< vector<Decimal> > result = stridiagonal_lu(a, b, c, d, e, n);

  cout.unsetf(ios::fixed);
  cout.precision(6);

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

  cout << "\nCalculem la multiplicacio de les matrius L i U.\n";

  Matrix mult = matrix_multiplication(l, u);

  cout << "\nMatriu A llegida anteriorment:\n";

  Matrix original(n, vector<double>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) original[i][j] = a[i];
      else if (i == j+1) original[i][j] = b[j];
      else if (i+1 == j) original[i][j] = c[i];
      else if (i == n-1 && j == 0) original[i][j] = d;
      else if (i == 0 && j == n-1) original[i][j] = e;
      else original[i][j] = 0;
      cout << original[i][j] << (j < n ? " " : "");
    }
    cout << "\n";
  }

  Matrix r = matrix_subtraction(mult, original);

  cout << "\nMatriu r = L*U - A:\n";

  print_matrix(r);

  Decimal max = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (abs(r[i][j]) > max) {
        max = abs(r[i][j]);
      }
    }
  }

  cout << "\nError: " << max << "\n";

  cout.setf(ios::fixed);
  cout.precision(13);

  cout << "\nDeterminant: " << tridiagonal_lu_determinant(result[0]) << "\n\n";

  vector<Decimal> p(n);

  for (int i = 0; i < n; ++i) p_file >> p[i];

  cout << "Trobant la solucio al sistema Ly=p...\n";
  vector<Decimal> y = solve_sly(result[1], result[3], p);

  cout << "Trobant la solucio al sistema Ux=y...\n";
  vector<Decimal> x = solve_sux(result[0], result[2], c, y);

  cout << "\nSolucio trobada! Es la seguent:\n";

  for (int i = 0; i < n; ++i) {
    cout << x[i] << (i < n-1 ? " " : "");
  }
  cout << "\n";

  if (argc >= 4) {
    cout << "\nEscrivint a '" << argv[3] << "' el vector solucio x...\n";
    fstream output(argv[3], fstream::out | ios::trunc);

    output.setf(ios::fixed);
    output.precision(20);

    print_vector(x, output);
  }
}
