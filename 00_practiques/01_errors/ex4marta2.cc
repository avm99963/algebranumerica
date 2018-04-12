#include <iostream>
#include <cmath>
using namespace std;

typedef float Decimal;

const Decimal N_Taylor = 10;

int factorial(int n) {		//calcula el factorial de n de manera iterativa
	int res = 1;
	for (int o = 2; o <= n; ++o) res = o*res;
	return res;
} 

float taylor(int n) {
	float sum = 0;
	for (int l = 0; l <= n; ++l) {
		sum += 1/Decimal(factorial(l))/(n+l+1);	//sumatori de la fórmula: E(de 0 fins a n)1/k!*1/(n+k+1)
  	      cout << "Suma de moment: " << sum << endl;
	}
    return sum = exp(-1)*sum;	  //el sumatori finalment es multiplica per 1/e
}

int main() {
    float value_3 = taylor(N_Taylor);
    cout << "Taylor: " << value_3 << endl;
}

