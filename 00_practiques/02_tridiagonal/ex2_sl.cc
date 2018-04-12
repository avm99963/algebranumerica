#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
#include "lib/core.cc"
#include "lib/matrix.cc"

typedef double Decimal;

const Decimal epsilon = 1e-8;

void print_vector(const vector<double> &v, fstream &file) {
  int n = v.size();
  for (int i = 0; i < n; ++i) {
    file << v[i] << (i < n - 1 ? " " : "");
  }
  file << "\n";
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
  ifstream file;
  ifstream pfile;
  if (argc >= 3) {
    file.open(argv[1]);
    pfile.open(argv[2]);
  } else {
    cerr << "Sisplau, especifica com a parametres on esta l'arxiu amb la descomposicio LU de la matriu tridiagonal i on esta l'arxiu amb el vector p.\n";
    return 1;
  }

  int n;
  file >> n;

  clog << "Llegint descomposicio LU...\n";
  
  vector<Decimal> alpha(n);
  vector<Decimal> beta(n-2);
  vector<Decimal> eps(n-1);
  vector<Decimal> delta(n-1);
  vector<Decimal> c(n-2);
  vector<Decimal> p(n);

  for (int i = 0; i < n; ++i) file >> alpha[i];
  for (int i = 0; i < n-2; ++i) file >> beta[i];
  for (int i = 0; i < n-1; ++i) file >> eps[i];
  for (int i = 0; i < n-1; ++i) file >> delta[i];
  for (int i = 0; i < n-2; ++i) file >> c[i];
  for (int i = 0; i < n; ++i) pfile >> p[i];
  
  clog << "Trobant la solucio al sistema Ly=p...\n";
  vector<Decimal> y = solve_sly(beta, delta, p);
  clog << "Trobant la solucio al sistema Ux=y...\n";
  vector<Decimal> x = solve_sux(alpha, eps, c, y);
  clog << "Solucio trobada! Es la seguent:\n";
  
  for (int i = 0; i < n; ++i) {
    cout << x[i] << (i < n-1 ? " " : "");
  }
  cout << "\n";
}
