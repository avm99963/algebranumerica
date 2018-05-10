#include <iostream>
using namespace std;

double retorna(int a, int b, int c, int d, int x) {
  double random = (double)(rand() % 100)/10000;
  return x*x*x*a + x*x*b + x*c + d + random;
}

int main() {
  // Genera punts d'una corva de grau 3 i s'alteren una mica
  int a = 1;
  int b = 2;
  int c = 4;
  int d = 5;
  
  for (int i = 0; i < 25; ++i) {
    cout << retorna(a, b, c, d, i) << ", ";
  }

  cout << "\n";
  
  for (int i = 0; i < 25; ++i) cout << i << ", ";
  cout << "\n";
}
