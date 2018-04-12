#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include "stdlib.h"
FILE *fitxer;
using namespace std;
typedef float Decimal;
typedef vector< vector <Decimal> > Matrix;

ofstream fileOut;

#define N 20

Matrix taula(4, vector<Decimal>(20, 0));     //La matriu estarà disponible per totes les funcions


Decimal integral_1(int n) {				//calcula el valor de la integral int(0_1)[x^n * e^(x-1) dx]
    Decimal I1_N = 0;
    for (int i = 0; i <= n; ++i) {
        if (i == 0) I1_N = 1;	//cas base: I_1
        else I1_N = 1 - i*I1_N;
        taula[1][i] = I1_N;
//        cout << "Integral 1: " << I1_N << endl;
    }
    return I1_N;
}

Decimal integral_2(int n) {					//calcula el valor de la integral int(0_1)[x^n * e^(x-1) dx]
    Decimal I2_N;
    for (int j = 20; j >= 20 - n; --j) {
        cout << "hi" << endl;
        if (j == 20) {
            I2_N = 0;
        } else {
            I2_N = (1- I2_N)/j;
        }
        taula[2][j] = I2_N;                      //aquí la fila 1 correspondrà al resultat de I2_20 i l'última fila a I2_12
        cout << j << ": " << I2_N << "\n";
//        cout << "Integral 2: " << I2_N << endl;
    }
    return I2_N;
}

int factorial(int n) {			//calcula el factorial de n de manera iterativa
	int res = 1;
	for (int o = 2; o <= n; ++o) res = o*res;
	return res;
} 

float taylor(int n) {
	float sum = 0;
	for (int l = 0; l <= 10; ++l) {
		sum += 1/Decimal(factorial(l))/(n+l+1);	//sumatori de la fórmula: E(de 0 fins a 10)1/k!*1/(n+k+1)
//        cout << "Suma de moment: 'e-1 * ' " << sum << endl;
	}
//	cout << "Taylor final: " << exp(-1)*sum << endl;
	return sum = exp(-1)*sum;			//el sumatori finalment es multiplica per 1/e
}

int main(int argc, char *argv[]) {
//	Matrix taula(4, vector<Decimal>(N_Taylor));			//Creem la matriu on anirem guardant els resultats
	for (int i = 0; i <= N; ++i) taula[0][i] = i;		//Omplim la primera columna1
	
	//Apartat 2)	MANERA 1: Calcular I_N com a = 1 - I_(N-1)
	float value_1 = integral_1(N);			//fa la integral I_N	
        cout << "4.2. Valor aproximat de I_12 amb precisio simple: \t" << value_1 << "\n" << "____________" << endl;	//escriu el valor de I_N

	//Apartat 3)		A mi no em dona un valor negatiu...
	
	//Apartat 4)    MANERA 2: I_(N-1) = 1/n - I_N/N 
	float value_2 = integral_2(N);
        cout << "4.4. Valor aproximat de I_12 emprant I_20 = 0: \t" << value_2 << "\n" << "____________" << endl;
	
	//Apartat 5)	MANERA 3: Utilitzant Taylor
	
	float value_3 = taylor(N);
        cout << "4.5. Taylor: " << value_3 << "\n" << "____________" << endl;
	for (int p = 0; p <= N; ++p) taula[3][p] = taylor(p);
	

	
	// Fitxer de sortida
	if (argc == 2) fileOut.open(argv[1], ofstream::out);
	else {cerr << "ERROR: no hi ha fitxer de sortida" << endl; return 0;}
	
	if (!fileOut.is_open()) {
		cerr << "Error: no s'ha pogut obrir el fitxer " << argv[1]
			<< " per escriure els resultats. " << endl;
		return 0;
	}
	
	// Escrivim al fitxer de sortda
	for (int k = 0; k <= N; ++k) {
		for (int j = 0; j <= 3; ++j) {
			fileOut << (j ? "\t" : "") << taula[j][k];   //enlloc de cout. "si j és true, fes espai, si fals, no en fas
		}
		fileOut << endl;
	}
	
	// Tanquem el fitxer de sortida
	fileOut.close();
}

