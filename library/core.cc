void comprovacio_epsilon(double valor, double epsilon) {
  if (abs(valor) < epsilon) {
    cerr << "ERROR: s'ha violat un epsilon. No procedirem amb el programa.\n";
    exit(2);
  }
}

