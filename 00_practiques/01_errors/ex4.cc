#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef float Decimal;
typedef vector< vector<Decimal> > Matrix;

const int N = 10; // Grau màxim del polinomi de Taylor

Decimal E_rec(int n) {
    if (n == 0) return 1;
    return 1 - n*E_rec(n-1);
}

Decimal E_rec2(int n) {
    if (n == 20) return 0;
    return (1 - E_rec2(n+1))/n;
}

Decimal taylor(int n, int N) {
    Decimal sum = 0;
    int fact = 1;
    for (int l = 0; l <= N; ++l) {
        if (l > 1) fact *= l;
        sum += Decimal(1)/(fact*(n + l + 1));
    }

    return exp(-1)*sum;
}

int main() {
    cout << "E_rec(12) = " << E_rec(12) << "\n";
    cout << "E_rec2(12) = " << E_rec2(12) << "\n";
    cout << "E_mclaurin(10, 12) = " << taylor(12, 10) << "\n";

    vector<Decimal> rec(21, 0);
    Decimal n = 1;
    rec[0] = n;
    for (int i = 1; i <= 20; ++i) {
        n = 1 - i*n;
        rec[i] = n;
    }

    vector<Decimal> etilde(21, 0);
    n = 0;
    etilde[20] = n;
    for (int i = 19; i >= 1; --i) {
        n = (1 - n)/i;
        etilde[i] = n;
    }

    vector<Decimal> mclaurin(21, 0);
    for (int i = 0; i <= 20; ++i) {
        mclaurin[i] = taylor(i, N);
    }

    cout << "\ni: E_rec(i) E_rec2(i) taylor(i)\n";
    for (int i = 0; i <= 20; ++i) {
        cout << i << ":\t" << rec[i] << "\t" << etilde[i] << "\t" << mclaurin[i] << "\n";
    }
}
