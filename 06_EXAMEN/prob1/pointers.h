void print_vector(double* v, int n);
void print_vector(int* v, int n);
void print_matrix(double** m, int n);
void intercanvia(double **a, const int &n, const int &i, const int &j);
double** matrix_multiplication(double** m1, double** m2, const int &m, const int &n, const int &k);
double** matrix_subtraction(double** m1, double** m2, const int &m, const int &n);
double** copia_punter(double** a, const int &m, const int &n);
double* copia_punter(double* v, const int &n);
double** create_pointer(const int &n, const int &m);
double norma_m1(double** m, const int &n);
double norma_minf(double** m, const int &n);
double norma_1(double* v, const int &n);
double norma_inf(double* v, const int &n);
double condition_number_1(double** m, double** inv_m, const int &n);
double condition_number_inf(double** m, double** inv_m, const int &n);

