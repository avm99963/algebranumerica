#include <iostream>
#include <vector>
#include <fstream> 	//fitxers
using namespace std;

typedef double Decimal;

typedef vector<Decimal> Row;
typedef vector<Row> Matrix;


void print_square_matrix(const Matrix& M) {
	int ncols = (int)M[0].size();
	int nrows = (int)M.size();
	for (int i = 0; i < nrows; ++i) {
		for (int j = 0; j < ncols; ++j) {
			cout << (j ? "\t" : "") << M[i][j]; 
		}
		cout << endl;
	}
}


void print_square_matrix(double **M, int ncols, int nrows) {
	for (int i = 0; i < nrows; ++i) {
		for (int j = 0; j < ncols; ++j) {
			cout << (j ? "\t" : "") << M[i][j]; 
		}
		cout << endl;
	}
}


void print_vector(const Row& v) {
	int n = v.size();
	for (int i = 0; i < n; ++i) cout << (i ? " " : "") << v[i];
	cout << endl;
}


void print_vector(double *v, int n) {
	for (int i = 0; i < n; ++i) cout << (i ? " " : "") << v[i];
	cout << endl;
}

void print_vector(int v[], int n) {
	for (int i = 0; i < n; ++i) cout << (i ? " " : "") << v[i];
	cout << endl;
}


/*
void print_vector_file(const Row& v) {
	int n = v.size();
	for (int i = 0; i < n; ++i) file_out << (i ? " " : "") << v[i];
	file_out << endl;
}
*/



Matrix matrix_product(const Matrix& M, const Matrix& N) {
	int nrows = (int)M.size();
    int nout = (int)M[0].size();
    int ncols = (int)N[0].size();
    Matrix MN = Matrix(nrows, Row(ncols,0));
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            for (int l = 0; l < nout; ++l) {
                MN[i][j] += M[i][l]*N[l][j];
            }
        }
    }
    return MN;
}

void matrix_product(double **M, int nrows, int nout, double **N, int ncols, double** MN) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            for (int l = 0; l < nout; ++l) {
                MN[i][j] += M[i][l]*N[l][j];
            }
        }
    }
}

void matrix_vector_product(double **M, int nrows, int ncols, double *v, double* Mv) {
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
                Mv[i] += M[i][j]*v[j];
        }
    }
}



void matrix_sum(double **M, double **N, int nrows, int ncols, double **MN) {	
	/* sums M + N matrices of size nrows x ncols and saves the result in MN matrix */
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            MN[i][j] = M[i][j] + N[i][j];
        }
    }
}

void matrix_sum(double *v, double *w, int n, double *vw) {
	/* sums v + w vectors of size n x 1 and saves the result in vw vector */
    for (int i = 0; i < n; ++i) {
        vw[i] = v[i] + w[i];
	}
}

void matrix_substraction(double **M, double **N, int nrows, int ncols, double **MN) {
	/* rests M - N matrices of size nrows x ncols and saves the result in MN matrix */
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            MN[i][j] = M[i][j] - N[i][j];
        }
    }
}


void matrix_substraction(double *v, double *w, int n, double *vw) {
	/* rests v - w vectors of size n x 1 and saves the result in vw vector */
    for (int i = 0; i < n; ++i) {
        vw[i] = v[i] - w[i];
	}
}



Row solve_back_sys(const Matrix& M, const Row& v) {
	/* given an UPPER TRIANGULAR square matrix n*n and a vector v, 
	 * it returns the solution (vector x) of the linear system
	 * */
	Row x(v.size(),0);
	int n = M.size();	//square matrix
	for (int k = n-1; k >= 0; --k) {
		Decimal sum = 0;
		for (int i = k + 1; i < n; ++i) {
			sum += x[i]*M[k][i];
		}		
		x[k] = 1/M[k][k]*(v[k] - sum);
	}
	return x;
}

void solve_back_sys(double** M, int n, double* v) {
	/* given an UPPER TRIANGULAR square matrix n*n and a vector v of size ncols, 
	 * it returns the solution (vector x) of the linear system
	 * */
	double x[n];
	for (int k = n-1; k >= 0; --k) {	//for each row starting from down
		Decimal sum = 0;
		for (int i = k + 1; i < n; ++i) {	//for each column from diagonal to end
			sum += x[i]*M[k][i];
		}		
		x[k] = 1/M[k][k]*(v[k] - sum);
	}
	print_vector(x, n);
}
	
	
	
Row solve_forward_sys(const Matrix& M, const Row& v) {
	/* given a LOWER TRIANGULAR square matrix n*n and a vector v, 
	 * it returns the solution (vector x) of the linear system
	 * */
	Row x(v.size(),0);
	int n = M.size();	//square matrix
	for (int k = 0; k < n; ++k) {
		Decimal sum = 0;
		for (int i = 0; i < k-1; ++i) {
			sum += x[i]*M[k][i];
		}		
		x[k] = 1/M[k][k]*(v[k] - sum);
	}
	return x;
}	

void solve_forward_sys(double** M, int n, double* v) {
	/* given a LOWER TRIANGULAR square matrix n*n and a vector v, 
	 * it returns the solution (vector x) of the linear system
	 * */
	double x[n];
	for (int k = 0; k < n; ++k) { //for each row starting from up
		Decimal sum = 0;
		for (int i = 0; i < k-1; ++i) {	//for each column until diagonal
			sum += x[i]*M[k][i];
		}		
		x[k] = 1/M[k][k]*(v[k] - sum);
	}
	print_vector(x, n);
}		
	

double** create_matrix_pointer(int nrows, int ncols) {
	double** A = (double**) calloc(nrows, sizeof(double*));	//makes space for nrows
	if (A == NULL) {
		cerr << "Error: memoria insuficient.\n";
		exit(1);
	}
    for (int i = 0; i < nrows; ++i) {
		A[i] = (double*) calloc(ncols, sizeof(double));
		if (A[i] == NULL) {
			cerr << "Error: memoria insuficient.\n";
			exit(1);
		}
		for (int j = 0; j < ncols; ++j) A[i][j] = 0;	//l'inicialitzem amb 0s
	}
	return A;
}
	
double* create_vector_pointer(int n) {
	double* b = (double*) calloc(n, sizeof(double));
	if (b == NULL) {
		cerr << "Error: memoria insuficient.\n";
		exit(1);
	}
	for (int i = 0; i < n; ++i) b[i] = 0;
	return b;
}
	
	
	
	
void exchange(Decimal&a, Decimal&b) {
    Decimal c = a;
    a = b;
    b = c;    
}

void transpose(Matrix& M) {
    int ncols = (int)M[0].size();
	int nrows = (int)M.size();
	for (int i = 0; i < nrows; ++i) {
		for (int j = i + 1; j < ncols; ++j) exchange(M[j][i], M[i][j]);
    }
}

void transpose(double **M, int nrows, int ncols) {
	Decimal c;
	for (int i = 0; i < nrows; ++i) {
		for (int j = i+1; j < ncols; ++j) exchange(M[j][i], M[i][j]);
    }
}
