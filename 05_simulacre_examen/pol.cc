#include <iostream>
#include <cmath>
using namespace std;

const double TOL = 1e-30;
const int MAXITS = 500;

double g(const double &x) {
  return cbrt(1000 - x);
  //return (double)(2000*x)/pow(x*x + 1, 2);
}

int main() {
  cout.setf(ios::scientific);
  cout.precision(14);

  double x = 100, prevx = 0, absvalue = 1;
  int its = 0;
  
  while (absvalue > TOL && its < MAXITS) {
    cout << x << "\n";
    prevx = x;
    x = g(x);
    absvalue = abs(x - prevx);
    its++;
  }

  cout << "X: " << x << "\n";
  cout << "Norm: " << absvalue << "\n";
  cout << "Number of iterations: " << its << "\n";
  cout << "x^3 + x - 1000 = " << x*x*x + x - 1000 << "\n";
}
