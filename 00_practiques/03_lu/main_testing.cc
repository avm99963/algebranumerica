#include <iostream>
#include <cmath>
#include <fstream>
#include "pointers.h"
#include "lu.h"
#include "resol.h"
#include "inversa.h"
using namespace std;

const double TOL = 10e-12;
const string ARXIU_OUTPUT = "solucioSL.dat";

int main(int argc, char *argv[]) {
  // Obrim el fitxer d'entrada
  ifstream file;
  if (argc >= 2) {
    file.open(argv[1]);
  } else {
    cout << "=== AJUDA ===:\n\nPer utilitzar el programa, executeu \"./program MOO.DAT\", on MOO.DAT\nes el fitxer amb la matriu.\n\nDespres del nom del fitxer, podeu introduir la opcio 'v' per mostrar\nmes informacio a la pantalla, o 'l' per tal que es mostrin menys\ndecimals per pantalla (aixo no afecta a la precisio dels nombres\nal fitxer generat).\n\nLa opcio 'v' es util per mostrar la inversa explicitament.\n\nExemples d'utilitzacio:\n\n./program MOO.DAT\n./program MM/M00.DAT v\n./program MM/M42.DAT lv\n";
    return 0;
  }

  if (!file.good()) {
    cerr << "Error: el fitxer d'entrada especificat no existeix.\n";
    return 3;
  }

  // Activem el mode verbose si es crida el programa com a "./program MOO.dat v"
  bool verbose = false;
  int precision = 6;
  if (argc >= 3) {
    if (string(argv[2]) == "v") {
      verbose = true;
    } else if (string(argv[2]) == "vl" || string(argv[2]) == "lv") {
      verbose = true;
      precision = 3;
    } else if (string(argv[2]) == "l") {
      precision = 3;
    }
  }

  int n;
  file >> n;

  //cout << "Fitxer d'entrada: " << argv[1] << "\nDimensio: " << n << "\n\n";

  // Inicialitzem la matriu A
  double** A;
  A = (double**) calloc(n, sizeof(double*));
  if (A == NULL) {
    cerr << "Error: memoria insuficient.\n";
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    A[i] = (double*) calloc(n, sizeof(double));
    if (A[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      return 1;
    }
    for (int j = 0; j < n; ++j) A[i][j] = 0;
  }

  // Establim la precisio i el mode cientific per la sortida de doubles
  cout.setf(ios::scientific);
  cout.precision(precision);

  // Llegim informacio del fitxer
  int k;
  file >> k;
  for (int i = 0; i < k; ++i) {
    int r, c;
    file >> r >> c;
    file >> A[r][c];
  }

  if (verbose) {
    cout << "Matrix A:\n";
    print_matrix(A, n);
  }

  double b[n];
  for (int i = 0; i < n; ++i) b[i] = 0;

  file >> k;
  for (int i = 0; i < k; ++i) {
    int r;
    file >> r;
    file >> b[r];
  }

  if (verbose) {
    cout << "\nVector b:\n";
    print_vector(b, n);
    cout << "\n";
  }

  // Al'right, let's start with the LU party!!
  //cout << "Al'right, let's start with the LU party!!\n\n";
  //cout << "Comencem a calcular LU\n\n";

  int p[n];
  double** Aprima = copia_punter(A, n, n);
  double** A_lu = copia_punter(A, n, n);
  int sig = lu(A_lu, n, p, TOL);

  //cout << "sig = " << sig << "\n\n";

  if (sig == 0) {
    cout << "La matriu no es regular, per tant terminem el programa amb codi de sortida 42.\n";
    return 42;
  }

  if (verbose) {
    cout << "A_lu:\n";
    print_matrix(A_lu, n);
    cout << "\n";
  }

  //cout << "p: ";
  //print_vector(p, n);
  
  double det = sig;
  for (int i = 0; i < n; ++i) {
    det *= A_lu[i][i];
  }
  //cout << "\nDeterminant: " << det << "\n";

  // Intercanviem files d'A per obtenir PA segons P
  bool* visited;
  visited = (bool*) calloc(n, sizeof(bool));

  for (int i = 0; i < n; ++i) visited[i] = false;

  int i = 0;
  while (i < n) {
    if (!visited[i]) {
      if (!visited[p[i]] && i != p[i]) intercanvia(Aprima, n, i, p[i]);
      visited[i] = true;
      i = p[i];
    } else {
      ++i;
    }
  }

  //cout << "Amb intercanvis:\n\n";
  //print_matrix(Aprima, n);

  // Calculem LU
  double** mlu;
  mlu = (double**) calloc(n, sizeof(double*));
  if (mlu == NULL) {
    cerr << "Error: memoria insuficient.\n";
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    mlu[i] = (double*) calloc(n, sizeof(double));
    if (mlu[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      return 1;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mlu[i][j] = 0;
      for (int k = 0; k < n; ++k) {
        mlu[i][j] += ((i < k) ? 0 : ((i > k) ? A_lu[i][k] : 1))*((k <= j) ? A_lu[k][j] : 0); // Ningu sap per que, pero funciona :)
      }
    }
  }

  if (verbose) {
    cout << "\nL*U:\n";
    print_matrix(mlu, n);
  }

  // Calculem el residu r = PA-LU
  double** residu = matrix_subtraction(Aprima, mlu, n, n);
  if (verbose) {
    cout << "\nr = PA-LU:\n";
    print_matrix(residu, n);
  }

  // Veiem quines son les seves normes
  //cout << "\nNormes de PA-LU: norma_1 = " << norma_m1(residu, n) << ", norma_inf = " << norma_minf(residu, n) << "\n";
  cout << norma_m1(residu, n) << " " << norma_minf(residu, n) << " ";

  double x[n];

  double* bprima = copia_punter(b, n);

  // Resolem el sistema d'equacions
  resol(A_lu, x, bprima, n, p);

  if (verbose) {
    cout << "x (solucio):\n";
    print_vector(x, n);
  }

  //cout << "\nS'ha guardat la solucio x al fitxer " << ARXIU_OUTPUT << "\n\n";

  // Escrivim solucio a l'arxiu solucioSL.dat
  //fstream output(ARXIU_OUTPUT, fstream::out | ios::trunc);
  //output.setf(ios::scientific);
  //output.precision(11);

  //for (int i = 0; i < n; ++i) output << i << " " << x[i] << "\n";

  // Calculem el residu r=Ax-b
  double residu_2[n];
  for (int i = 0; i < n; ++i) {
    residu_2[i] = 0;
    for (int j = 0; j < n; ++j) {
      residu_2[i] += A[i][j]*x[j];
    }
  }

  for (int i = 0; i < n; ++i) residu_2[i] -= b[i];

  if (verbose) {
    cout << "Ax-b:\n";
    print_vector(residu_2, n);
  }

  //cout << "Normes de Ax-b: norma_1 = " << norma_1(residu_2, n) << ", norma_inf = " << norma_inf(residu_2, n) << "\n\n";
  cout << norma_1(residu_2, n) << " " << norma_inf(residu_2, n) << " ";
  // Calculem la inversa
  double** inv_A = create_pointer(n, n);
  inversa_nolu(A_lu, inv_A, n, p);

  if (verbose) {
    cout << "Inversa de A:\n";
    print_matrix(inv_A, n);
  }

  // Calculem les normes
  double ** Id = matrix_multiplication(A, inv_A, n, n, n);
  for (int i = 0; i < n; ++i) {
    Id[i][i] -= 1;
  }

  //cout << "Normes de A*A^(-1) - Id: norma_1 = " << norma_m1(Id, n) << ", norma_inf = " << norma_minf(Id, n) << "\n";
  cout << norma_m1(Id, n) << " " << norma_minf(Id, n) << "\n";
}
