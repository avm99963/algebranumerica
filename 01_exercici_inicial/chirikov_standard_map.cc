#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

// Paràmetres que podem variar: N (nombre de subdivisions)
//                              M (nombre d'iteracions)
//                              k (paràmetre de la fòrmula iterativa)
//                              h (altura de la gràfica)
// Li preguntem a l'usuari quins paràmetres vol configurar:
double M = 500,
       N = 5000,
       k = 1.2,
       h = 3.14;

string FILENAME = "plot.dat";

void mod2pi(double &o) {
    int n = o / (2*M_PI);
    o -= n*2*M_PI;
    if (o < 0) o += 2*M_PI;
}

// Iterem i actualitzem les variables "p" i "o" amb el següent element
// de les dues successions, en funció d'una constant k.
void iterate(double &p, double &o, const double &k) {
    p += k * sin(o);
    o += p;
    mod2pi(o);
}

int main() {
    fstream file(FILENAME, fstream::out | ios::trunc);

    cout << "Welcome to the Chirikov Standard Map plotter!\n\nPlease, enter the data for the simulation:\nk: ";
    double tmp_k;
    cin >> tmp_k;
    if (k > 0) k = tmp_k;

    cout << "Starting to plot...\n";

    double s = 2*h/M;

    for (int i = 0; i <= M; ++i) { // Per cada subdivisió
        double p = -h + i*s, o = 0;
        for (int j = 0; j < N; ++j) { // Calculem cada iteració
            if (p >= -h && p <= h) file << p << " " << o << "\n";
            iterate(p, o, k);
        }
        file << "\n\n";
        p = -h + i*s;
        o = M_PI;
        for (int j = 0; j < N; ++j) { // Calculem cada iteració
            if (p >= -h && p <= h) file << p << " " << o << "\n";
            iterate(p, o, k);
        }
        file << "\n\n";
    }
}
