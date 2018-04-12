#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
  ifstream input;
  ofstream matrix_a;
  ofstream vector_p;

  if (argc >= 4) {
    input.open(argv[1]);
    matrix_a.open(argv[2]);
    vector_p.open(argv[3]);
  } else {
    cerr << "ERROR, indica els fitxers.\n";
    return 1;
  }

  int n;
  input >> n;
  matrix_a << n << "\n";

  for (int i = 0; i < 3*n - 2; ++i) {
     string k;
     input >> k;
     matrix_a << k << "\n";
  }

  for (int i = 0; i < n; ++i) {
    string k;
    input >> k;
    vector_p << k << "\n";
  }
}
