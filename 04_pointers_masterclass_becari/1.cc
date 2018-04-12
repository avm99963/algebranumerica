#include <iostream>
#include <vector>
using namespace std;

typedef vector<double> VD;

int main() {
	/*double a = 12.5;
	cout << "a = " << a << endl;
	cout << "posició de memòria = " << &a << endl;
	cout << "A la posició " << &a << " hi ha " << a << endl;
	cout << "A la posició " << &a << " hi ha " << *(&a) << endl;
	
	int n = 4;
	VD v = VD(n,0);
	v[0] = 11;
	v[1] = 13;
	v[2] = -4;
	v[3] = -78;
	for (int i = 0; i < n; ++i) {
		cout << "A la posició " << &v[i] << " hi ha " << *(&v[i]) << endl;
	}
	
	
	v[2] = a;
	cout << "A la posició " << &v[2] << " hi ha " << *(&v[2]) << endl;
	*/
	
	
	int firstvalue = 5, secondvalue = 15;
	int * p1, * p2;
	
	p1 = &firstvalue;
	p2 = &secondvalue;
	cout << "firstvalue = " << firstvalue << endl;
	cout << "secondvalue = " << secondvalue << endl;
	cout << "p1 = " << p1 << " and contains " << *p1 << endl;
	cout << "p2 = " << p2 << " and contains " << *p2 << endl;
	*p1=10;
	cout << "firstvalue = " << firstvalue << endl;
	cout << "secondvalue = " << secondvalue << endl;
	cout << "p1 = " << p1 << " and contains " << *p1 << endl;
	cout << "p2 = " << p2 << " and contains " << *p2 << endl;
	*p2=*p1;
	cout << "firstvalue = " << firstvalue << endl;
	cout << "secondvalue = " << secondvalue << endl;
	cout << "p1 = " << p1 << " and contains " << *p1 << endl;
	cout << "p2 = " << p2 << " and contains " << *p2 << endl;
	p1=p2;
	cout << "firstvalue = " << firstvalue << endl;
	cout << "secondvalue = " << secondvalue << endl;
	cout << "p1 = " << p1 << " and contains " << *p1 << endl;
	cout << "p2 = " << p2 << " and contains " << *p2 << endl;
	*p1 = 20;
	
	cout << "firstvalue = " << firstvalue << endl;
	cout << "secondvalue = " << secondvalue << endl;
	cout << "p1 = " << p1 << " and contains " << *p1 << endl;
	cout << "p2 = " << p2 << " and contains " << *p2 << endl;
      
}
