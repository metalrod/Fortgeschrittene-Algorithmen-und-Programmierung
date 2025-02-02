// Labor1a.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <iostream>
#include "komplexeZahl.h"

double abs( komplexeZahl& rk){

		double a;
		a = sqrt(rk.getReal() * rk.getReal() + rk.getImag() * rk.getImag());
		return a;
}


int main()
{
	komplexeZahl k1;
	double real, imag;
	k1.setKartesian(-5.0, 22.3);
	k1.print();
	std::cout << "Real =" << k1.getReal() << " und Imaginaer = " << k1.getImag() << std::endl;
	std::cout << "Absolutwert = " << abs(k1) << std::endl;
	std::cout << "Absolutwert = " << k1.abs() << std::endl;
	std::cout << "Phi = " << k1.phi() << std::endl;
	k1.printPolar();
	system("pause");
	return 0;

	/*

	Realisiert wurde diese Programm bereits zu großen Teilen im Unterricht.
	5b.) Am sinnvolsten Sind die Erweitungen in der der KomplexeZahl.cpp Datei - damit auch andere 
	c++ Dateien auf diese Funktion in der Classe zugreifen können. Hinzu ist die Programmierung einfacher.
	Desweiteren übersichtlicher und über die Header-Datein einfach einzubinden.

	*/
}


