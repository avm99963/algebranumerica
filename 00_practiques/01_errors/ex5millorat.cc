#include <iostream>
#include <cmath>
using namespace std;

typedef float Decimal;

const int N = 20;
const int x = 2;

Decimal e_mclaurin(Decimal x, int N) {
    Decimal sum = 1;
    for (int i = N; i > 0; --i) {
        sum *= x/i;
        sum += 1;
    }

    return sum;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(10);

    Decimal expr = exp(x);
    Decimal p10 = e_mclaurin(x, N);
    Decimal q10 = 1/e_mclaurin(-x, N);

    cout << "built-in exp(" << x << "): " << expr << "\n";
    cout << "p_" << N << "(" << x << "): " << p10 << "\n";
    cout << "1/p_" << N <<"(" << -x << "): " << q10 << "\n\n";

    cout << "e_a(p_" << N << "(" << x << "), exp(" << x << ")): " << p10 - expr << "\n";
    cout << "e_r(p_" << N << "(" << x << "), exp(" << x << ")): " << (p10 - expr)/expr << "\n";
    cout << "e_a(q_" << N << "(" << x << "), exp(" << x << ")): " << q10 - expr << "\n";
    cout << "e_r(q_" << N << "(" << x << "), exp(" << x << ")): " << (q10 - expr)/expr << "\n";
}
