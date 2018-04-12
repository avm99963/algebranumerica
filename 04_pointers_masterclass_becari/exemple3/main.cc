/* Programa que llegeix dues matrius, calcula el seu producte i
 * calcula el màxim de la suma en valor absolut. Les matrius es
 * guarden amb punters. */

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "stdlib.h" 
using namespace std;

double maxim_en_valor_absolut(double** M, int files, int columnes);
double **multiplica_matrius(double** A,double** B,int n, int m, int k);

ifstream fileIn;
ofstream fileOut;

int main(int argc, char *argv[]){
	// Fitxer d'entrada
	if (argc >= 2) fileIn.open(argv[1]); // obrim el fitxer per llegir les dades.
	else {cerr << "ERROR: no hi ha fitxer d'entrada" << endl; return 0;}
    
    if (!fileIn.is_open()) {
        cerr << "Error: no s'ha pogut obrir el fitxer " << argv[1]
            << " per llegir les dades" << endl;
        return 0;
    }
    
    // Llegim dimensió matriu
    int n, m;
    fileIn >> n >> m;
    
    // Creem matriu A amb punters
    double **A;
    A = (double **) calloc(n, sizeof(double*));
    for (int i = 0; i < n; ++i) A[i] = (double *) calloc(m, sizeof(double));
    
    
    // Llegim components matriu A
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) fileIn >> A[i][j];
	}
	
	int m2, k;
	fileIn >> m2 >> k;
	// Creem matriu B amb punters
    double **B;
    B = (double **) calloc(m2, sizeof(double*));
    for (int i = 0; i < m2; ++i) B[i] = (double *) calloc(k, sizeof(double));
    
    // Llegim components matriu B
    for (int i = 0; i < m2; ++i) {
		for (int j = 0; j < k; ++j) fileIn >> B[i][j];
	}
	
	// Tanquem el fitxer d'entrada
	fileIn.close();
	
	
	// Comprovem que les dimensions coincideixen
	if (m2 != m) {
		cerr << "Les dimensions no coincideixen: no es poden multiplicar les matrius" << endl;
		return 0;
	}
	
	// Multipliquem les matrius
	double **AB;
    AB = (double **) calloc(n, sizeof(double*));
    for (int i = 0; i < n; ++i) AB[i] = (double *) calloc(k, sizeof(double));
    AB = multiplica_matrius(A,B,n,m,k);
    
	// Calculem el màxim per columnes del valor absolut
	double max_columnes = maxim_en_valor_absolut(AB,n,k);
	
	
	
	// Fitxer de sortida
	if (argc == 3) fileOut.open(argv[2], ofstream::out);
	else {cerr << "ERROR: no hi ha fitxer de sortida" << endl; return 0;}
	
	if (!fileOut.is_open()) {
		cerr << "Error: no s'ha pogut obrir el fitxer " << argv[2]
			<< " per escriure els resultats. " << endl;
		return 0;
	}
	
	// Escrivim al fitxer de sortda
	// Escrivim la matriu producte
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			fileOut << (j ? " " : "") << AB[i][j];
		}
		fileOut << endl;
	}
	// Escrivim el màxim en valor absolut
	fileOut << "Maxim en valor absolut per columes = " << max_columnes << endl;
	// Tanquem el fitxer de sortida
	fileOut.close();
}
