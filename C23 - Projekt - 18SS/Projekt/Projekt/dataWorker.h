#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <map>
#include "Graph_process.h"
#include "process.h"

struct values {
	int option;
	long pieces;
	int time;
	double cost;
};

//const string& filename

using namespace std;

class DataException {
public:
	DataException(string what) : m_what(what) {}
	DataException(string what, string filename) : m_what(what) {}
	string what() const { return m_what; }
	string filename() const { return m_filename; }

	
private:
	string m_what;
	string m_filename;
};

class DataWorker
{
	// Diese Klasse dient zum Einlesen, verarbeiten und abspeichern der Daten
public:
	DataWorker();
	virtual ~DataWorker();
	void writeProdProcessToFile(); // Erstellter Fertigungsablauf kann gespeichert werden
	void readDealsFromFile(); // Die Fertigungsangebote werden aus einer Datei eingelesen
	void convertDealsToVec(); // Die eingelesenen Angebote werden verarbeitet und in Vektoren gespeichert
	void buildDealsHeader();  //Es wird der TabellenKopf der Angebote erstellt
	void buildProdProcessHeader(); //es wird der Tabellenkopf des erstellten Fertigungsablaufs erstellt
	bool convertDealsVecToString(); // Die verarbeiteten Angebotsdaten werden aus dem 2D Vektor gelesen und für Ausgaben(Bildschirm/ Datei) verarbeitet
	bool yesNoCall(); // mehrfach genutzte reine Ja/Nein Abfrage 
	void convertProdProcessVecToString(); // Der Fertigungsablauf wird aus dem 2D Vektor gelesen und für Ausgaben(Bildschirm/ Datei) verarbeitet
	void sortProdProcessName(); // Die Angebote im 2D Vektor werden nach Firmen Namen sortiert
	void sortProdProcessService(); // Die Angebote im 2D Vektor werden nach Fertigungsschritt sortiert
	void buildGraphStructure(); //Hier wird die Struktur des Graphen abgebildet, gespeichert und überall gebraucht
	void comparePathDeals(int ropt); // aus Dijkstra-Edges und Angebots-Daten wird ID verglichen und Fertigungsablauf erstellt (2D Vektor).
	void addCost(int rOpt, int rNumber); // Kosten aus dem Fertigungsablauf 2D Vektor werden addiert
	string & getProdProcessString();  // Getter für erstellten Ausgabe String vom Fertigungsablauf
	string & getDealsString(); // Getter für erstellten Ausgabe String von den Angeboten
	void addTime(); // Die Dauer der parallel Ablaufenden Fertigungsprozesse wird addiert
	void buildNodes(); //Die benötigten Knoten werden erstellen und mit dem Graphen verknüpfen
	void buildEdges(); //Die benötigten Kanten werden erstellen und mit den Knoten und dem Graphen verknüpfen
	vector<vector<string>>& getOptWay(); // Getter für den Fertigungsablauf 2Vektor
	void runDijkstra(int rOpt); // Dijkstra Algorithmus der durch die Graphenteilabschnitte läuft

private:
	string m_fileName; // Name der Angebotsdatei
	string m_prodProcessString; //String für die Ausgabe/Speicherung des Fertigungsablaufs
	string m_dealsString = ""; //String für die Ausgabe/Speicherung der eingelesenen Angebote
	stringstream m_dealsHeader; //String für den Tabellenkopf: Angebote
	stringstream m_prodProcessHeader; //String für den Tabellenkopf: Fertigungsablauf
	vector< vector<string>> m_dealsVec; //2D Angebotsvektor
	vector< vector<string>> m_prodProcessVec; //2D Fertigungsablaufvektor
	map<string,pair<int,pair<int, int>>> m_graphStructure; //Hier ist die Graphenstruktur gespeichert
	Graph_process m_graph;	// m_graph aus einer Klasse die von der static Library geerbt hat (von der Klasse Graph)
	deque<Edge*> m_path; // hier wird er Pfad gespeichert aus dem Dijkstra
	values m_prodProcessValues; // Hier werden die Daten: Gesamkosten, Dauer, Optimierungsmodus (1'-3' Loßgroeße 4' Zeit), Stückzahl gespeichert 
};

