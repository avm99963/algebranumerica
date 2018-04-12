#include <iostream>
#include <cmath>
#define N 12
using namespace std;

float integral_2(int n) { //calcula el valor de la integral int(0_1)[x^n * e^(x-1) dx]
    float I2_N;
    for (int j = 20; j >= n; --j) {
        if (j == 20) I2_N = 0;
        else I2_N += (1 - I2_N)/j;
        cout << "Integral 2: " << I2_N << endl;
	}
    return I2_N;
}

int main() {
	float value_2 = integral_2(N);
	cout << "Valor aproximat de I_12 emprant I_20 = 0: \t" << value_2 << endl;
}

