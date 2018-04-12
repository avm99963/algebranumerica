#include <iostream>
using namespace std;

int main() {
	float e_float = 1;
	double e_double = 1;

	while (1 + e_float != 1) e_float = e_float/10;	//s'atura quan epsilon és 0 per la màquina; mentre és diferent de 0, va dividint entre 10

	while (1 + e_double != 1) e_double = e_double/10;
	
	cout << "\nEpsilon maquina (float): " << 10*e_float << endl;	 //l'epsilon màquina és el penúltim epsilon calculat, quan encara donava 1+e != 1
	cout << "Epsilon maquina (double): " << 10*e_double << endl;
}

