// Labor2.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <iostream>
#include "komplexeZahl.h"




int main()
{
	komplexeZahl xyz;

	xyz.setKartesian(1.0, 1.5);
	xyz.print();

	system("pause");
	return 0;
}

