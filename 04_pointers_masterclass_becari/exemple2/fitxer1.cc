/* Programa que mostra l'ús de la definició de funcions creades
 * en un altre fitxer. */
 
#include <iostream>
#include <cmath>
#include <fstream>
//#include "aln.h"
#include "stdlib.h"
using namespace std;


ifstream fileIn;
ofstream fileOut;

double suma(const double& x,const double& y);
double producte(const double& x,const double& y);

int main(int argc, char *argv[]){
	// Fitxer d'entrada
	if (argc >= 2) fileIn.open(argv[1]); // obrim el fitxer per llegir les dades.
	else {cerr << "ERROR: no hi ha fitxer d'entrada" << endl; return 0;}
    
    if (!fileIn.is_open()) {
        cerr << "Error: no s'ha pogut obrir el fitxer " << argv[1]
            << " per llegir les dades" << endl;
        return 0;
    }
    
    
    // Fitxer de sortida
	if (argc == 3) fileOut.open(argv[2], ofstream::out);
	else {cerr << "ERROR: no hi ha fitxer de sortida" << endl; return 0;}
	
	if (!fileOut.is_open()) {
		cerr << "Error: no s'ha pogut obrir el fitxer " << argv[2]
			<< " per escriure els resultats. " << endl;
		return 0;
	}
    
    
    double x, y;
    while (fileIn >> x >> y) {
		fileOut << x << "+" << y << " = " << suma(x,y) << endl;
		fileOut << x << "*" << y << " = " << producte(x,y) << endl;
	}
    // Tanquem el fitxer d'entrada
	fileIn.close();
	// Tanquem el fitxer de sortida
	fileOut.close();
}
