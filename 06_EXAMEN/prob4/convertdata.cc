#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n = 37;
  
  vector<string> x(n);
  vector<string> y(n);

  for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

  cout << "x = [" << x[0];
  for (int i = 1; i < n; ++i) cout << ", " << x[i];
  cout << "];\n";

  cout << "y = [" << y[0];
  for (int i = 1; i < n; ++i) cout << ", " << y[i];
  cout << "];\n";
}
