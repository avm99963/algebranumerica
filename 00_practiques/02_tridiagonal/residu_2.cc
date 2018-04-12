#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
#include "lib/core.cc"
#include "lib/matrix.cc"

typedef double Decimal;

const Decimal epsilon = 1e-12;

/*void print_matrix(const Matrix &m) {
  int r = m.size();
  int c = m[0].size();

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      cout << m[i][j] << (j < c-1 ? " " : "");
    }
    cout << "\n";
  }
}*/

int main(int argc, char *argv[]) {
  //cout.setf(ios::fixed);
  //cout.precision(13);

  ifstream matriu_a;
  ifstream matriu_x;
  ifstream matriu_q;

  matriu_a.open(argv[1]);
  matriu_x.open(argv[2]);
  matriu_q.open(argv[3]);

  int n;
  matriu_a >> n;

  vector<Decimal> a(n);
  vector<Decimal> b(n-1);
  vector<Decimal> c(n-1);
  Decimal d;
  Decimal e;

  for (int i = 0; i < n; ++i) matriu_a >> a[i];
  for (int i = 0; i < n-1; ++i) matriu_a >> b[i];
  for (int i = 0; i < n-1; ++i) matriu_a >> c[i];
  matriu_a >> d;
  matriu_a >> e;

  Matrix original(n, vector<Decimal>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) original[i][j] = a[i];
      else if (i == j+1) original[i][j] = b[j];
      else if (i+1 == j) original[i][j] = c[i];
      else if (i == n-1 && j == 0) original[i][j] = d;
      else if (i == 0 && j == n-1) original[i][j] = e;
      else original[i][j] = 0;
    }
  }

  Matrix x(n, vector<double>(1));

  for (int i = 0; i < n; ++i) matriu_x >> x[i][0];

  Matrix p(n, vector<double>(1));
  for (int i = 0; i < n; ++i) matriu_q >> p[i][0];

  Matrix r = matrix_subtraction(matrix_multiplication(original, x), p);

  /*cout << "Matriu original\n";
  print_matrix(original);
  cout << "Matriu x:\n";
  print_matrix(x);
  cout << "Matriu p:\n";
  print_matrix(p);

  cout << "Matriu original*x:\n";
  print_matrix(matrix_multiplication(original, x));*/

  cout << "Matriu r:\n";
  print_matrix(r);

  double norma_sub1 = 0;
  double max = 0;
  for (int i = 0; i < n; ++i) {
    norma_sub1 += abs(r[i][0]);
    if (abs(r[i][0]) > max) max = abs(r[i][0]);
  }

  cout << "Norma sub_1: " << norma_sub1 << "\n";
  cout << "Maxim norma: " << max << "\n";
}
