#include <iostream>
#include <cmath>
using namespace std;

const int UPPER_LIMIT = 15;

double talla(double x) {
    return trunc(x*1000)/1000;
}

int main() {
    double sum = 0;
    cout << "Sumem des de 1/1 fins a 1/15:" << endl;
    for (int i = 1; i <= UPPER_LIMIT; ++i) {
        sum = talla(sum + talla(1/(double)i)*talla(1/(double)i));
        cout << "I=" << i << " --> " << sum << "\n";
    }

    sum = 0;
    cout << "Sumem des de 1/15 fins a 1/1:" << endl;
    for (int i = UPPER_LIMIT; i >= 1; --i) {
        sum = talla(sum + talla(1/(double)(i*i)));
        cout << "I=" << i << " --> " << sum << "\n";
    }
}
