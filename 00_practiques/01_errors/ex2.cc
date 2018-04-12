#include <iostream>
using namespace std;

const int N = 5000000;

int main() {
    cout.setf(ios::fixed);
    cout.precision(10);

    float suma;

    for (int i = 1; i <= N; ++i) {
        suma += 1/(float)i;
        if (i == 10 || i == 100 || i == 1000 || i == 10000 || i == 100000 || i % 1000000 == 0) cout << "i=" << i << " --> " << suma << "\n";
    }
}
