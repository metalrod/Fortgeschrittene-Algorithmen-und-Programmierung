// Projekt Arbeit

#include "Graph.h"
#include <iostream>
#include "dataWorker.h"
#include "menue.hpp"



using namespace std;


//FileDataToEdgeData(string);



int main()
{	
	cout << "Willkommen, mit diesem Programm koennen Sie Ihren Fertigungsablauf einlesen, ausgeben und optimieren" << endl;
	Menue *newDatenMenue = new Menue;
	newDatenMenue->mainMenue();	
	delete newDatenMenue;
	return 0;
}

