#include <iostream>
#include <cmath>
#include "stdlib.h" 
using namespace std;


double maxim_en_valor_absolut(double** M, int files, int columnes) {
	double m = -1;
	for (int j = 0; j < columnes; ++j) {
		double suma = 0;
		for (int i = 0; i < files; ++i) suma += abs(M[i][j]);
		m = max(m,suma);
	}
	return m;
}


double **multiplica_matrius(double** A, double** B,int n,int m,int k) {
	// Declarem la matriu resultant del producte
	double **AB;
    AB = (double **) calloc(n, sizeof(double*));
    for (int i = 0; i < n; ++i) AB[i] = (double *) calloc(k, sizeof(double));
    
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			for (int l = 0; l < m; ++l) {
				AB[i][j] += A[i][l]*B[l][j];
			}
		}
	}
	
    return AB;
}
