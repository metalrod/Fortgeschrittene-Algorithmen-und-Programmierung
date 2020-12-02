
#include "menue.hpp"
#include "Graph.h"
#include <iostream>
#include <locale>



class MenueException {
public:
	MenueException(string what) : m_what(what) {}
	string what() const {
		return m_what;
	}
private:
	string m_what;
};

using namespace std;

Menue::Menue () {
	// 2 Adressen der Klassenmethoden ins Menue laden
	m_menueAdresses.push_back(make_pair("Einlesen der Dienstleistungsangebote", &Menue::readDeals));
	m_menueAdresses.push_back(make_pair("Das Programm beenden", &Menue::closeProgram));
}

void Menue::mainMenue() // Das Main-Menue - zeigt die Auswahlmöglichkeiten an und stellt Abfrage
{
	while (!m_quit) {
		int j = 1;
		cout << endl;
		cout << "Was moechten Sie tun?" << endl << endl;
		// Menue-deque ausgeben
		for (const auto i : m_menueAdresses)
		{
			cout << j << ": " << i.first << endl;
			j++;
		}
		// m_menueAdresses ist eine map und mit der Auswal des Benutzer (KEY) ruft es sofort die KlassenMethode auf im Pair
		(this->*m_menueAdresses[userSelection() - 1].second)();

	}
}

void Menue::readDeals() // Ruft den Konstruktor für Datenverarbeitung auf (der erstellt beim Aufbau die Dateiabfrage) & speichert neue Memberfunktionen im Menue
{
	try
	{
	
	DataWorker *pDaten = new DataWorker;
	m_pDataWorker = NULL;
	m_pDataWorker = pDaten;
	}
	catch (const GraphException& e)
	{
		cerr << endl << e.what() << endl;
	}
	catch (const DataException& e)
	{
		cerr << endl << e.what() << endl;
	}
	if (!(m_pDataWorker == NULL)){	// Wenn bei den Daten in der Datei Fehler entstehen, soll nicht weitergearbeitet werden
		// die Adresse der Klassenmethode zum Daten Einlesen wird entfernt und steht dem Benutzer nicht mehr zur Verfügung
		m_menueAdresses.pop_front();
		// Adressen der Klassenmethoden werden eingereiht
		m_menueAdresses.push_front(make_pair("Optimierten Fertigungsablauf erstellen", &Menue::createProdProcess));
		m_menueAdresses.push_front(make_pair("Dienstleistungsangebote ausgeben", &Menue::printDealsString));
		m_menueAdresses.push_front(make_pair("Sortieren der Dienstleistungsangebote", &Menue::sortDeals)); 
	}
}

void Menue::sortDeals() //Ruft die Sortierung ab
{
	bool input = true;
	string response;
	cout << "Wonach moechten Sie die eingelesenen Daten sortieren? ";
	cout << "Nach Firmen[n]ame oder [F]ertigungsschritt: ";
	do
	{
		cin >> response;
		if ((response == "n") || (response == "N"))
		{ 
		input = false; 
		m_pDataWorker->sortProdProcessName();
		}
		else if ((response == "F") || (response == "f"))
		{
		input = false;
		m_pDataWorker->sortProdProcessService();
		}
		// Lesespeicher leeren
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (input);

}

void Menue::printDealsString() // gibt den String von den Angebiten auf dem Bildschirm aus
{
	cout << m_pDataWorker->getDealsString();
}

void Menue::createProdProcess() // Ließt benötigte Daten vom benutzer ein und ruft Prozeduren zum Fertigungsablauf Erstellen auf
{
	int pieces = 0;
	int opt = 1;
	bool input = true;
	string response;
	cout << "Wieviel Stueck wollen Sie herstellen?: ";
	while (!(cin >> pieces)) {
		// Lesespeicher leeren
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Leider keine Zahl" << endl;
		cout << "Wieviel Stueck wollen Sie herstellen?: ";
	}
	cout << endl;
	cout << "Wonach wollen Sie optimieren?: ";
	cout << "Nach [K]osten oder nach [Z]eit?: ";
	// opt beinhaltet die Kategorie wonach sortiert wird in Abhängigkeit der Stückzahl 1-3
	if (pieces >= 10) opt++;
	if (pieces >= 100) opt++;
	try
	{
		do
		{
			cin >> response;
			if ((response == "K") || (response == "k"))
			{
				input = false;
				//Dijkstra nach Kosten optimieren
				m_pDataWorker->runDijkstra(opt);
			}
			else if ((response == "Z") || (response == "z"))
			{
				input = false;
				// Dijkstra nach Zeit optimieren
				m_pDataWorker->runDijkstra(4);
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (input);

	}
	catch (const GraphException& e)
	{	
		cerr << e.what() << endl;
		system("stop");
	}

	if (m_pDataWorker->getOptWay().empty()) {
		// wenn ein Fertigungsablauf 2D Vektor erstellt wurde kann man nun auch Speichern und Ausgeben
		m_menueAdresses.push_back(make_pair("Fertigungsablauf speichern", &Menue::saveProdProcess));
		m_menueAdresses.push_back(make_pair("Fertigungsablauf ausgeben", &Menue::printProdProcess));
		swap(m_menueAdresses[3], m_menueAdresses[5]);
	}
	// Hier werden die Methoden der DatenVerarbeitungsklasse aufgerufen
	// Zu erst 2D vektor für Fertigungsablauf erstellen
	m_pDataWorker->comparePathDeals(opt);
	// Dann Kosten berechnen
	m_pDataWorker->addCost(opt, pieces);
	// Dann den Tabellenkopf erstellen (wieder neu erstellen)
	m_pDataWorker->buildProdProcessHeader();
	// Zeitkosten berechnen
	m_pDataWorker->addTime();
	// Fertigungsablauf für Ausgabe/ Speichern in String speichern
	m_pDataWorker->convertProdProcessVecToString();
}

void Menue::printProdProcess() // gibt den String von dem Fertigungsablauf auf dem Bildschirm aus
{

	cout << m_pDataWorker->getProdProcessString();

}

void Menue::saveProdProcess() //Ruft Speicherfunktion auf für Fertigungsablauf
{
	
	//m_pDataWorker->VectorToData();
	try
	{
		m_pDataWorker->writeProdProcessToFile();
		cout << "gespeichert" << endl;
	}
	catch (const DataException& e)
	{
		cerr << e.what() << endl;
		cerr << e.filename() << endl;
	}
	
}

void Menue::closeProgram()// Beendet das Programm (quit = true), bei erstelltem Fertigungsablauf fragt er nach Speicherung
{
	// wenn ein Fertigungsablauf 2D Vektor erstellt wurde kann man auch Speichern
	// sollte es aber noch keine Datenklasse geben zeigt der Pointer ins Nirvana
	// Deswegen 2 Vorraussetzungen benötigt
	if (!(this->m_pDataWorker == NULL) && !(m_pDataWorker->getOptWay().empty()))
	{
		string response;
		bool input = true;
		cout << endl;
		cout << "Das Programm wird geschlossen" << endl;
		cout << "Moechten Sie vorher Ihre Daten speichern? [j]a oder [n]ein : ";
		do
		{
			cin >> response;
			if ((response == "J") || (response == "j"))
			{
				input = false;
				(this->*&Menue::saveProdProcess)();
			}
			else if ((response == "N") || (response == "n"))
			{
				input = false;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			delete m_pDataWorker;
		} while (input);
	}
	m_quit = true;
}

int Menue::userSelection (){ //Ließt die Benutzerauswahl ein
	// Es wird nur eine Zahl zwischen 1 und der Anzahl der Menue Elemente akzeptiert
    int auswahl = 0;
	int auswahlMax = m_menueAdresses.size();
    while (auswahl < 1 || auswahl > auswahlMax){
		cout << "Bitte waehlen Sie einen Menuepunkt aus [1.." << auswahlMax << "]: ";
		while (!(cin >> auswahl)) {
			// Lesespeicher leeren
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Leider keine Zahl" << endl;
		}
        if (auswahl < 1 || auswahl > auswahlMax) {
            cout << "Fehler: Auswahl muss zwischen 1 und " << auswahlMax <<  " liegen." << endl;
        }
    }
    return auswahl;
}