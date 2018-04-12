#include <iostream>
using namespace std;

const int N = 5000000;

int main() {
    float suma;

    for (int i = 1; i <= N; ++i) {
        suma += 1/(float)i;
        cout << "i=" << i << " --> " << suma << "\n";
    }
}
