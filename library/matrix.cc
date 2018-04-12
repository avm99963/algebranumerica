#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<double> > Matrix;

Matrix matrix_multiplication(const Matrix &m1, const Matrix &m2) {
    Matrix r(m1.size(), vector<double>(m2[0].size(), 0));
    for (int i = 0; i < (int)m1.size(); ++i) {
        for (int j = 0; j < (int)m2[0].size(); ++j) {
            for (int k = 0; k < (int)m2.size(); ++k) {
                r[i][j] += m1[i][k]*m2[k][j];
            }
        }
    }
    return r;
}

// return m1 - m2
Matrix matrix_subtraction(const Matrix &m1, const Matrix &m2) {
  Matrix r(m1.size(), vector<double>(m2[0].size()));
  for (int i = 0; i < (int)m1.size(); ++i) {
    for (int j = 0; j < (int)m1[0].size(); ++j)
      r[i][j] = m1[i][j] - m2[i][j];
  }

  return r;
}

double max_matriu(const Matrix &m) {
    double max = 0;
    for (int j = 0; j < (int)m[0].size(); ++j) {
        double suma;
        for (int i = 0; i < (int)m.size(); ++i) suma += abs(m[i][j]);
        if (suma >= max) max = suma;
    }
    return max;
}

void print_matrix(const Matrix &m) {
  for (int i = 0; i < (int)m.size(); ++i) {
    for (int j = 0; j < (int)m[0].size(); ++j) {
      cout << m[i][j] << (j < (int)m[0].size() ? " " : "");
    }
    cout << "\n";
  }
}

