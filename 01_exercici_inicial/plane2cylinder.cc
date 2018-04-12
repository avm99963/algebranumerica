#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x, y;
    while (cin >> y >> x) {
        cout << sin(x) << " " << cos(x) << " " << y << "\n";
    }
}
