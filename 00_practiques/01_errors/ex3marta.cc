#include <iostream>
#include <cmath>
using namespace std;
typedef double decimal;
#define N 16

decimal talla_3(decimal n) {
    return trunc(n*1000)/1000;
}

int main() {
	decimal sum_nat = 0;
	decimal sum_inv = 0;
	
	for (int i = 1; i <= N; ++i)
sum_nat = talla_3(sum_nat + talla_3(1/decimal(i*i))); //sumatori des de i=1 fins a 16 de 1/i²
	cout << "\nSuma decreixent o natural (1 + 1/4 +...): \t" << sum_nat << "\n" << endl;
	
	for (int j = N; j >= 1; --j)
sum_inv = talla_3(sum_inv + talla_3(1/decimal(j*j))); //sumatori des de i=15 fins a 1 de 1/i²
	cout << "\nSuma creixent o invers (1/225 + 1/196 + ...): \t" << sum_inv << endl;
}

