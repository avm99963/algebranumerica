#include <iostream>
using namespace std;

void escriure_matriu(double** m, int n) {
	cout << m << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; j++) {
			cout << m[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	int n = 1000000000;
	double** m;
	m = (double**) calloc(n, sizeof(double*));
	if (m == NULL) {
		cerr << "Couldn't allocate more memory\n";
		return 1;
	}
	for (int i = 0; i < n; ++i) {
		m[i] = (double*) calloc(n, sizeof(double));
		if (m == NULL) {
			cerr << "Couldn't allocate more memory\n";
			return 1;
		}
	}

	m[0][0] = 2;
	m[0][1] = 2;
	m[1][0] = 0;
	m[1][1] = 2;

	escriure_matriu(m, n);
}
