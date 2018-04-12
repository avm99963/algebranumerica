//g++ -Wall main.cc lu.cc resol.cc sistema.cc
//./a.out input output

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>
//#include "aln.h"
#include "stdlib.h"
#include "stdio.h"
using namespace std;


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
    int n;
    fileIn >> n;
    // Creem matriu A
    vector <vector<double> > A(n, vector<double>(n,0));
    
    // Llegim nombre components no nul·les de la matriu
    int m;
    fileIn >> m;
    // Llegim components no nul·les
    int i, j;
    for (int k = 0; k < m; k++) {
		fileIn >> i >> j;
		fileIn >> A[i][j];
	}
	// Tanquem el fitxer d'entrada
	fileIn.close();
	
	
	// Fem algo amb la matriu
	
	
	// Fitxer de sortida
	if (argc == 3) fileOut.open(argv[2], ofstream::out);
	else {cerr << "ERROR: no hi ha fitxer de sortida" << endl; return 0;}
	
	if (!fileOut.is_open()) {
		cerr << "Error: no s'ha pogut obrir el fitxer " << argv[2]
			<< " per escriure els resultats. " << endl;
		return 0;
	}
	// Escrivim al fitxer de sortda
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fileOut << (j ? " " : "") << A[i][j];
		}
		fileOut << endl;
	}
	
	// Tanquem el fitxer de sortida
	fileOut.close();
}
