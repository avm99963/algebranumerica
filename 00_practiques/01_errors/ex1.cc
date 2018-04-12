#include <iostream>
using namespace std;

int main() {
    double u = 1, epsilon = 1;
    while (u + epsilon != u) {
        epsilon /= 2;
    }
    cout << "Min epsilon for double: " << epsilon << "\n";

    float uf = 1, epsilonf = 1;
    while (uf + epsilonf != uf) {
        epsilonf /= 2;
    }
    cout << "Min epsilon for float: " << epsilonf << "\n";

}
