#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int el_rand() {
  return rand() % 2000 - 1000;
}

int main() {
  int n;
  cin >> n;

  cout << n << "\n";
  
  for (int i = 0; i <= n-1; ++i) cout << el_rand() << " ";
  cout << "\n";
  for (int k = 0; k < 2; ++k) {
    for (int i = 0; i <= n-2; ++i) cout << el_rand() << " ";
    cout << "\n";
  }
}
