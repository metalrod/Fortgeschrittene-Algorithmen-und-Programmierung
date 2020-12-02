
#pragma once
#include "Node.h"
#include "Graph.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "dataWorker.h"


using namespace std;


class Menue
{
// Ist zu Verwaltung der Menuestruktur da
public:
	typedef void(Menue::*MenueFunctions)();
	Menue();
	void mainMenue(); // Das Main-Menue - zeigt die Auswahlmöglichkeiten an und stellt Abfrage
	void readDeals(); // --> Datenverarbeitung erstellt & speichert neue Memberfunktionen im Menue
	void sortDeals(); //Ruft die Sortierung auf
	void printDealsString();// gibt den String von den Angeboten auf dem Bildschirm aus
	void createProdProcess(); // Ließt benötigte Daten vom benutzer ein und ruft Prozeduren zum Fertigungsablauf Erstellen auf
	void printProdProcess(); // gibt den String von den Angeboten auf dem Bildschirm aus
	void saveProdProcess(); //Ruft Speicherfunktion auf für Fertigungsablauf
	void closeProgram(); // Beendet das Programm (quit = true), bei erstelltem Fertigungsablauf fragt er nach Speicherung
	int userSelection(); //Ließt die Benutzerauswahl ein
private:
	deque<pair<string,MenueFunctions>> m_menueAdresses; // enthält die Adressen für die KLassenmethoden des Menues
	DataWorker * m_pDataWorker = NULL; // bekommt die Adresse der erstellten Datenverarbeitungsklasse 
	bool m_quit = false; // wenn true, dann quit
};



