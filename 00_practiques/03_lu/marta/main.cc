#include <iostream>
#include "matrixlib.h"
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;


typedef double Decimal;

typedef vector<Decimal> Row;
typedef vector<Row> Matrix;


ofstream file_out;
ifstream file_in;


Decimal tol = 10e-12;






bool is_singular(Decimal a, Decimal tol) {
	// Detects wheter has a smaller value than tol given
	if (a < tol) {
		cout << "\nThe matrix is SINGULAR! We'll stop the process." << endl;
		return true;
	}
	return false;
}

	
	
bool singular = false;
bool permutacions = true;

Decimal max_row(double **A, int n, const int& k, int row) { //n = matrix size; row = number of row in the matrix
	/* Returns the maximum absolute value of the row row of a matrix A of size n in step k
	 * */
	Decimal max_val = 0;
	for (int i = k; i < n; ++i) {
		if (abs(A[row][i]) > max_val) {
			max_val = abs(A[row][i]);
		}
	}
	//singular = is_singular(max_val, tol); //DETECCIÓ DE MATRIU SINGULAR (si una fila són tots 0s en algun moment del pivotatge)
	if (is_singular(max_val, tol)) { exit(0); return(0); }	//voldria posar primer return(0) i després exit(0) però llavors segueix calculant
	
//	cout << "La matriu no es singular. Seguim amb el proces." << endl;	
	return max_val;
}	


int lu(double **A, int n, int perm[], double tol) {
	// DESCOMPOSICIÓ LU amb pivotatge parcial esglaonat
		
	// càlcul de LU
//	cout << "\nCOMENCEM LA DESCOMPOSICIO LU" << endl;
	for (int k = 0; k < n-1; ++k) { 	// per cada fila (k=fila, realment pensant com si fos l'el de la diagonal)
//		cout << "\n-----------COLUMNA " << k << "------------\n" << endl;
		Decimal pivot_norm;
//		cout << "pivot inicial: " << pivot_norm << endl;
		pivot_norm = abs(A[k][k]/max_row(A, n, k, k)); 	//pivot actual normalitzat
//		cout << "pivot inicial normalitzat: " << pivot_norm << endl;
		
		int max_pivot_pos = k;
		Decimal max_pivot_val = pivot_norm;
		
		for (int fila = k+1; fila < n; ++fila) { 	//guardarà el pivot màxim
			//mirem com és el pivot de cada fila normalitzat
			// i si és major que el que tenim guardat, aquest serà el nou pivot més gran
//			cout << "Llegint pivot: " << A[fila][k] << endl;
			
			if (abs(A[fila][k]/max_row(A, n, k, fila)) > max_pivot_val) {
				max_pivot_val = abs(A[fila][k]/max_row(A, n, k, fila));
				max_pivot_pos = fila;
//				cout << "hi ha un pivot mes gran! " << max_pivot_val << endl;
			}
		}
	
//		cout << "Valor absolut del pivot maxim es: " << max_pivot_val << endl;

		
		// permutem les files
		if (max_pivot_pos != k) { 	//si hem trobat un candidat a pivot major
			permutacions = not permutacions;
			Row temporal(n);	//guardem la fila que permutarem
			int canvi;			//guardem el nombre de la fila que permutarem
			for (int i = 0; i < n; ++i) temporal[i] = A[k][i];	//permutem les files de la matriu
			for (int i = 0; i < n; ++i) A[k][i] = A[max_pivot_pos][i];
			for (int i = 0; i < n; ++i) A[max_pivot_pos][i] = temporal[i];
			canvi = perm[k];		//guardem la informació de la fila permutada al vector permutació p
			perm[k] = perm[max_pivot_pos];
			perm[max_pivot_pos] = canvi;
		}
	
//		cout << "Ara la matriu un cop havent canviat les files mirant els pivots normalitzats es: \n" << endl;
//		print_square_matrix(A, n, n);
//		cout << "Vector permutacio: \n" << endl;
//		print_vector(perm, n);
		
//		cout << "GAUSS" << endl;
		//ara ja podem procedir a fer Gauss
		for (int i = k + 1; i < n; ++i) {	//per cada fila
			A[i][k] = A[i][k]/A[k][k];	//guardem a on quedaria 0 el multiplicador que ens servirà per transformar la seva fila
			for (int j = k + 1; j < n; ++j) {	//per cada el (per columnes)
				A[i][j] = A[i][j] - A[i][k]*A[k][j];	//algoritme de Gauss
			}
		}
//		cout << "Un cop fet Gauss, tenim: \n" << endl;
//		print_square_matrix(A, n, n);
		
	}
	
	if (is_singular(abs(A[n-1][n-1]), tol)) {exit(0); return(0); }
/*		singular = true;
		cout << "En l'ULTIM PAS, la matriu es SINGULAR!!! Aturarem el proces." << endl;
		exit(0);
		return(0);
	}
	
	if (singular) return 0;
	*/
	if (permutacions) return 1; 
	return -1;		
}


void resol(double **A, double x[], double b[], int n, int perm[]) {
	// Abans de res hem de PERMUTAR b:
	bool* visited_2;
	visited_2 = (bool*) calloc(n, sizeof(bool));

	for (int i = 0; i < n; ++i) visited_2[i] = false;

	int s = 0;
	while (s < n) {
		if (!visited_2[s]) {
			if (!visited_2[perm[s]] && s != perm[s]) swap(b[s], b[perm[s]]);
			visited_2[s] = true;
			s = perm[s];
		}	else ++s;
	}
	// Un cop tenim PA, sabent que PAx=b <=> LUx=b <=> Ly=b i Ux=y
	
	// TROBEM y TAL QUE Ly=b, que és resoldre un sistema TRIANGULAR INFERIOR tenint en compte que haurem d'escriure 1s a la diagonal que la matriu PA no té
	
	Decimal y[n];
	y[0] = b[0];	//primer pas de l'algorisme

	for (int i = 1; i < n; ++i) {	//for each row starting from up
		Decimal sum = 0;
		for (int j = 0; j < i; ++j) {	//sum for each column until diagonal
			sum += y[j]*A[i][j];
		} y[i] = b[i] - sum;	//com que l_ii = 1, no cal dividir entre l_ii i l'algoritme queda més senzill
	}
//	cout << "\nVector y: ";
//	print_vector(y, n);
//	print_vector(x, n);
	// TROBEM x TAL QUE Ux=y, que és resoldre un sistema TRIANGULAR SUPERIOR
	
	x[n-1] = y[n-1]/A[n-1][n-1]; 	//primer element
	for (int i = n-2; i >= 0; --i) {	//for each row starting from down
		Decimal sum = 0;
		for (int j = i; j < n; ++j) {	//for each column from diagonal to end
			sum += x[j]*A[i][j];
		}		
		x[i] = (y[i] - sum)/A[i][i];
	}
	
//	cout << "\nVECTOR solucio x = ";
//	print_vector(x, n);
	
	
	// escrivim el vector solució al fitxer de sortida:
	for (int i = 0; i < n; ++i) {
		file_out << i << "\t" << x[i] << endl;
		}

}



int inversa(double **A, double **invA, int n, double *detA, double tol, int perm[]) {
	/* calcula la inversa de A i l'escriu a invA. 
	 * No fa res amb detA i tol perquè ja ho calculem i detectem a altres passos del codi.
	 * En canvi, afegeixo un paràmetre, el perm[] perquè el necessito per calcular la inversa.
	 * */
	 
	// Creem vector identitat
	Decimal *e;
	e = create_vector_pointer(n);
	
//	cout << "\nComencem a calcular la inversa A^-1\n" << endl;
	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < n; ++i) e[i] = 0; 	//tot el vector e = 0
		e[j] = 1; 		//li posem 1 a la posició que toca
		resol(A, invA[j], e, n, perm);		//resolem pel vector j
		//cout << "\nMatriu INVERSA de moment: " << endl;
		//print_square_matrix(invA, n, n);
	}
	// transposem A^-1 perquè hem guardat els vectors en files i no en columnes
	transpose(invA, n, n);
//	cout << "\nINVERSA: " << endl;
//	print_square_matrix(invA, n, n);
	
	return 1;
}









int main(int argc, char *argv[]) {			//demana nom fitxer: ./a.out matriu_vec.txt
	//cout.setf(ios::fixed);
	//cout.precision(2);
	
	//Obrim FITXER D'ENTRADA
	if (argc >= 2) file_in.open(argv[1]); // obrim el fitxer per llegir la matriu.
	else {cerr << "ERROR: no hi ha fitxer d'entrada" << endl; return 0;}
	    
    if (!file_in.is_open()) {
        cerr << "Error: no s'ha pogut obrir el fitxer " << argv[1]
            << " per llegir les dades" << endl;
        return 0;
    }
	cout << "\nData input file: " << argv[1] << endl;  
	
	
	// LLEGIM MATRIU
//	cout << "\nMATRIU" << endl;
    // Llegim dimensió matriu i nombre components no nul.les
    int n;
    file_in >> n; 
    cout << "Dimension n=" << n << endl;
    
    
	//CREEM I GUARDEM ELS PUNTERS on guardarem la matriu
	double **A = create_matrix_pointer(n, n);

    
    // Llegim components
    int m;
    file_in >> m;
//    cout << "Nombre de components no nul.les: " << m << endl;

    Decimal a;	//valor de l'element actual que estarem llegint
	int i;	//fila de la matriu on estarà l'element
	int j;	//columna on estarà l'element
	
    for (int l = 0; l < m; ++l) {
		file_in >> i;
		file_in >> j;
		file_in >> a;
//		cout << "Llegint component " << l << " que estara a fila " << i << " columna " << j << " amb valor " << a << endl;
		A[i][j] = a;
	}
	
	//fem dues còpies de la matriu
	double **B = create_matrix_pointer(n, n); //treballarem amb la A i la B sera l'original
	double **PA = create_matrix_pointer(n, n); // a PA li aplicarem la permutació 
	for (int u = 0; u < n; ++u) {
		for (int o = 0; o < n; ++o) { B[u][o] = A[u][o]; PA[u][o] = A[u][o];}
	}
	
	// LLEGIM VECTOR
//	cout << "\nVECTOR" << endl;
	// Llegim nombre components no nul.les del vector
    int k;
    file_in >> k; 
 //   cout << "Nombre de components no nul.les: " << k << endl;
	
	
	// VECTOR b (TERME INDEPENDENT) NO PUNTERS
	Decimal b[n];	// original, no el permutarem
	Decimal b2[n]; 	// còpia de b, el que permutarem

	for (int i = 0; i < n; ++i) { b[i] = 0; b2[i] = 0;	}//inicialitzem el vector amb 0s
	for (int l = 0; l < k; ++l) {
		file_in >> i;
		file_in >> a;
		b[i] = a;
		b2[i] = a;
	}
//	cout << "\nVector b (terme independent): " << endl;
//	print_vector(b, n);
		
/*
	//VECTOR passat per punters
	double *b = create_vector_pointer(n);
	
	for (int l = 0; l < k; ++l) {
		file_in >> i;
		file_in >> a;
		b[i] = a;
//		cout << "Component " << i << " te valor: " << a << endl;
	}
*/

	// Tanquem el fitxer d'entrada
	file_in.close();
	
	
	// IMPRIMIM matriu i vector
/*	cout << "\nMatriu: " << endl;
	print_square_matrix(A, n, n);
	cout << "\nVector: " << endl;
	print_vector(b, n);	
	*/
	
	// creem vector p de PERMUTACIÓ
	int p[n];
	for (int l = 0; l < n; ++l) p[l] = (int)l;
//	cout << "\nVector permutacio inicial: " << endl;
//	print_vector(p, n);
	
	
		
	// DESCOMPOSICIÓ LU
	int result = lu(A, n, p, tol);
	if (result == 0) exit(0);
//	cout << "\nRETORN funcio LU: \n\t 0 \t matriu singular" << endl;
//	cout << "\t 1 \t nombre parell permutacions" << endl << "\t -1 \t nombre senar permutacions\n" << result << endl;


	// DETERMINANT D'A
	Decimal det = 1;
	for (int i = 0; i < n; ++i)	det *= A[i][i];
	cout << "\nDeterminant of A: " << det << endl;

	// PERMUTATION VECTOR
	cout << "\nPermutation vector:" << endl;
	print_vector(p, n);
	
	
	// CÀLCUL PA
	// Intercanviem files d'A per obtenir PA segons P (on la nostra A és la B perquè l'A l'hem canviat per LU i B és l'original)

	bool* visited;
	visited = (bool*) calloc(n, sizeof(bool));

	for (int i = 0; i < n; ++i) visited[i] = false;

	int h = 0;
	while (h < n) {
		if (!visited[h]) {
			if (!visited[p[h]] && h != p[h]) swap(PA[h], PA[p[h]]);
			visited[h] = true;
			h = p[h];
		}	else ++h;
	}
	
//	cout << "\nMatriu PA\n" << endl;
//	print_square_matrix(PA, n, n);	//matriu PA

	//Ara la matriu A és la LU juntes i la B és la PA
	
		
	// CÀLCUL L*U (que tenim guardada junta a A)
	double** mLU = create_matrix_pointer(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			mLU[i][j] = 0;
			for (int k = 0; k < n; ++k) {
				mLU[i][j] += ((i < k) ? 0 : ((i > k) ? A[i][k] : 1))*((k <= j) ? A[k][j] : 0); // Ningu sap per que, pero funciona :)
			}
		}
	}

//	cout << "\nMatriu L*U:\n\n";
//	print_square_matrix(mLU, n, n);
	
	
	
	
	// NORMES
	
	cout << "\nChecking the norm of the residue: |PA-LU|" << endl;
	
	// CÀLCUL R = PA - LU
	
	double **R = create_matrix_pointer(n, n);
	for (int w = 0; w < n; ++w) {
		for (int v = 0; v < n; ++v) R[w][v] = PA[w][v] - mLU[w][v];
	}	
//	cout << "\nMatriu Residu R = PA - LU:\n" << endl;
//	print_square_matrix(R, n, n);
	
	
	// CÀLCUL NORMA_1 I NORMA_INF
	Decimal norm_inf = 0;		//norma_1 és el màxim de la suma de les Columnes en valor absolut
	Decimal norm_1 = 0;			//norma_inf és el màxim de les files
	Decimal sum_row, sum_col;
	for (int i = 0; i < n; ++i) {
		sum_row = 0;
		sum_col = 0;
		for (int j = 0; j < n; ++j) {
			sum_row += abs(R[i][j]);		//calculem les normes amb la matriu Residu
			sum_col += abs(R[j][i]);
		} if (sum_row > norm_inf) norm_inf = sum_row;
		if (sum_col > norm_1) norm_1 = sum_col;
	}
//	cout << "\nNORMES:\n" << endl;
	cout << "1-norm: " << norm_1 << endl;
	cout << "supremum norm: " << norm_inf << endl;

	

	// FITXER DE SORTIDA (no tocar tot això)
	if (argc == 3) file_out.open(argv[2], ofstream::out);
	else {cerr << "ERROR: no hi ha fitxer de sortida" << endl; return 0;}
	
	if (!file_out.is_open()) {
		cerr << "Error: no s'ha pogut obrir el fitxer " << argv[2]
			<< " per escriure els resultats. " << endl;
		return 0;
	}	
		
	// CÀLCUL x SOLUCIÓ DEL SISTEMA Ax=b + ESCRIURE x AL FITXER DE SORTIDA
		
	// Ara utilitzem la funció resol per obtenir x
	double x[n];
	for (int i = 0; i < n; ++i) x[i] = 0;	//inicialitzem el vector amb 0s
	cout << "\nSolving Ax=b:" << endl;
	resol(A, x, b2, n, p);
	
	
	// NORMES
	
	// CÀLCUL r = Ax - b
	
	double *r = create_vector_pointer(n);
	double *Ax = create_vector_pointer(n);
	matrix_vector_product(B, n, n, x, Ax);	//multipliquem la matriu original (guardada a B) per x solució trobada
//	print_vector(Ax, n);
//	print_vector(b, n);
	matrix_substraction(Ax, b, n, r);	//fa la resta Ax - b i ho guarda al vector r
//	cout << "\nVector residu r = Ax - b:" << endl;
//	print_vector(r, n);
		
	
	// CÀLCUL NORMA_1 I NORMA_INF
	Decimal norm_inf_r = 0;		//norma_1 és el màxim de la suma de les Columnes en valor absolut, que en aquest cas és la suma dels elements del vector (té només 1 columna)
	Decimal norm_1_r = 0;			//norma_inf és el màxim de les files
	Decimal sum_row_r;
	for (int i = 0; i < n; ++i) {
		sum_row_r = abs(r[i]);		//calculem les normes amb el vector residu
		if (sum_row_r > norm_inf_r) norm_inf_r = sum_row_r;	
		norm_1_r += abs(r[i]);
	}

//	cout << "\nNORMES:" << endl;
	cout << "1-norm of the residue vector Ax-b: " << norm_1_r << endl;
	cout << "supremum norm of the residue vector Ax-b: " << norm_inf_r << endl;

		
	// Tanquem el fitxer de sortida
	file_out.close();
	
	
	
	// CÀLCUL A^(-1)
	
	// PAA-1 = PI
	Decimal **invA;
	invA = create_matrix_pointer(n, n);
		
	//apliquem la funció creada que calcula la inversa
	int reg;	//no serveix de res aquí però demanen que retorni si és o no regular
	double *detA;
	cout << "\nWe compute the inverse of A:" << endl;
	reg = inversa(A, invA, n, detA, tol, p);
	
	
	// NORMES
	
	// CÀLCUL R2 = AA^-1 - Id
	double **AA = create_matrix_pointer(n, n); // producte A*A^-1
	matrix_product(B, n, n, invA, n, AA);
	
	double **R2 = create_matrix_pointer(n, n);
	for (int w = 0; w < n; ++w) R2[w][w] = AA[w][w] - 1;
//	cout << "\nMatriu Residu R2 = A*invA - Id:\n" << endl;
//	print_square_matrix(R2, n, n);
	
	// CÀLCUL NORMA_1 I NORMA_INF
	Decimal norm_inf_2 = 0;		//norma_1 és el màxim de la suma de les Columnes en valor absolut
	Decimal norm_1_2 = 0;			//norma_inf és el màxim de les files
	Decimal sum_row_2, sum_col_2;
	for (int i = 0; i < n; ++i) {
		sum_row_2 = 0;
		sum_col_2 = 0;
		for (int j = 0; j < n; ++j) {
			sum_row_2 += abs(R2[i][j]);		//calculem les normes amb la matriu Residu
			sum_col_2 += abs(R2[j][i]);
		} if (sum_row_2 > norm_inf_2) norm_inf_2 = sum_row_2;
		if (sum_col_2 > norm_1_2) norm_1_2 = sum_col_2;
	}
//	cout << "\nNORMES:\n" << endl;
	cout << "1-norm of A*inv(A) - I: " << norm_1_2 << endl;
	cout << "supremum norm of A*inv(A) - I: " << norm_inf_2 << endl;


}
