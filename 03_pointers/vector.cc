#include <iostream>
#include <vector>
using namespace std;

void asdf(double *v, int n);

int main() {
	int n = 4;
	double *v;
	v = (double*) calloc(n, sizeof(double));
	v[0] = 3.1415926535;
	v[1] = 99963;
	v[2] = 13;
	v[3] = -4;
	asdf(v, n);
}
