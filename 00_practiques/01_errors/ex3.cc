#include <iostream>
#include <cmath>
using namespace std;

const int UPPER_LIMIT = 16;

double talla(double x) {
    return trunc(x*1000)/1000;
}

int main() {
    double sum = 0;
    cout << "Sumem des de 1/1 fins a 1/" << UPPER_LIMIT <<":" << endl;
    for (int i = 1; i <= UPPER_LIMIT; ++i) {
        sum = talla(sum + talla(1/(double)(i*i)));
        cout << "I=" << i << " --> " << sum << "\n";
    }

    cout << endl;

    sum = 0;
    cout << "Sumem des de 1/" << UPPER_LIMIT << " fins a 1/1:" << endl;
    for (int i = UPPER_LIMIT; i >= 1; --i) {
        sum = talla(sum + talla(1/(double)(i*i)));
        cout << "I=" << i << " --> " << sum << "\n";
    }
}
