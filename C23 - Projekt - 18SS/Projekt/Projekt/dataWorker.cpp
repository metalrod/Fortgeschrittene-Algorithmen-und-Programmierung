#include "dataWorker.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Node.h"
#include <string>


using namespace std;




DataWorker::DataWorker()
{
	/* Da die Klasse Dataworker nur Sinn ergibt, wenn Daten eingelesen und verarbeitet werden,  
	laden die folgenden Klassenmethoden die benötigten Informationen.

	Zu erst wird der Tabellenkopf erstellt, dann die Datei eingelesen, danach in ein normierten 2D Vektoren um-
	gewandelt. Anschließend wird Sie für eine Ausgabe in einen String geschrieben. Die nächsten Methoden erstellen eine
	Referenzdatei in der die Struktur des Graphen gespeicher ist. Diese auslesend werden Knoten und Kanten erstellt
	und in einem Graphen verlinkt
	*/
	buildDealsHeader();
	readDealsFromFile();
	convertDealsToVec();
	if (convertDealsVecToString()) {
		buildGraphStructure();
		buildNodes();
		buildEdges();
	}
	else { 
		DataException e("Leider weißt deine Datei strukturelle Fehler auf. Bitte vorher ändern!");
		throw e;
	}

}

DataWorker::~DataWorker()
{
}

void DataWorker::writeProdProcessToFile(){ // Erstellter Fertigungsablauf kann gespeichert werden
	while (1) {
		bool check = false;
		cout << "Bitte geben Sie den Dateinamen ein: " << endl;
		cin >> m_fileName;
		//Prüft ob die Datei bereits existiert und weist entsprechend darauf hin
		ifstream LogFile(m_fileName.c_str());
		if (LogFile) check = true;
		while (check)
		{
			check = false;
			cout << "Datei existiert schon. Wollen Sie die Datei überschreiben?: " << std::endl;
			if (!yesNoCall()) {
				cout << "Bitte geben Sie einen anderen Dateinamen ein: " << endl;
				cin >> m_fileName;
				ifstream LogFile(m_fileName.c_str());
				if (LogFile) check = true;
			} 
		}
		ofstream quelle(m_fileName.c_str());
		if (quelle.is_open()) {
			if (quelle << m_prodProcessString) {
				quelle.close();
				return;
			}
			else {
				cout << "Es gab ein Schreibfehler." << endl;
				DataException e("Schreibfehler");
				throw e;
			}
		}
		else {
			DataException e("Beim Öffnen im Schreibmodus entstand ein Fehler",m_fileName);
			throw e;
		}
	}
}

void DataWorker::readDealsFromFile() { // Die Fertigungsangebote werden aus einer Datei eingelesen
	while (1) {
		cout << endl;
		cout << "Bitte geben Sie den Dateinamen ein. ";
		cout << "Eine Vorlage zum Ausprobieren liegt unter dem Namen: \"Beispieldaten.txt\"" << endl <<"im selbigen Ordner: ";
		cin >> m_fileName;
		ifstream quelle(m_fileName.c_str());
		if (quelle.is_open()) {
			stringbuf buffer;
			if (quelle >> &buffer) {
				quelle.close();
				m_dealsString = buffer.str();
				cout << "Vielen Dank, die Daten wurden eingelesen!" << endl;
				return;
			}
			else {
				cout << "Es gab ein Lesefehler, überprüfen Sie den Dateinamen." << endl;
				DataException e("Lesefehler", m_fileName);
				throw e;
			}
		}
		else {
			cout << "Datei existiert nicht." << endl;
		}
	}
}

void DataWorker::convertDealsToVec() { // Die eingelesenen Angebote werden verarbeitet und in 2D Vektoren gespeichert
	stringstream ss;
	string line;
	vector<string> rowVec;
	string tmpString;
	int ID = 0;

	ss << m_dealsString;
	m_dealsVec.clear();

	getline(ss, line);	
	while (getline(ss, line) && line != "")		//Daten in Vektor kopieren
	{	
		rowVec.push_back(to_string(ID));
		for (const auto& c : line)
		{
			if (!(c == ';')) tmpString += c;	// Datenpakete werden am Semikolon getrennt
			else {
				rowVec.push_back(tmpString);
				tmpString.clear();
			}
		}
		ID++;
		rowVec.push_back(tmpString);		//Letzter Teil (Tage)
		m_dealsVec.push_back(rowVec);
		tmpString.clear();
		rowVec.clear();
	}
}

void DataWorker::buildDealsHeader(){ //Es wird der TabellenKopf der Angebote erstellt
	m_dealsHeader.str("");
	m_dealsHeader << left << setw(18) << "Firma" << "|";
	m_dealsHeader << setw(25) << "Dienstleistung"<< "|";
	m_dealsHeader << setw(16) << "Los: 1 in Euro"<< "|";
	m_dealsHeader << setw(16) << "Los: 10 in Euro"<< "|";
	m_dealsHeader << setw(16) << "Los: 100 in Euro" << "|";
	m_dealsHeader << setw(4) << "Tage" << "|" << endl;
}

void DataWorker::buildProdProcessHeader() { //es wird der Tabellenkopf des erstellten Fertigungsablaufs erstellt

	m_prodProcessHeader.str("");
	m_prodProcessHeader << left << setw(18) << "Firma" << "|";
	m_prodProcessHeader << setw(25) << "Dienstleistung" << "|";
	m_prodProcessHeader << setw(10-m_prodProcessValues.option) << "Los: 1";
	for (int i = m_prodProcessValues.option; i > 1; i--)
	{
		m_prodProcessHeader << "0";
	}
	m_prodProcessHeader << " in Euro" << "|";
	m_prodProcessHeader << setw(4) << "Tage" << "|" << endl;
}

bool DataWorker::convertDealsVecToString(){ // Die verarbeiteten Angebotsdaten werden aus dem 2D Vektor gelesen und für Ausgaben(Bildschirm/ Datei) verarbeitet

	stringstream ss, ll;
	ll << setfill('-') << setw(102) << " " << endl;
	ss << endl;
	ss << m_dealsHeader.str();
	ss << ll.str() << endl;
	
	try
	{
	for (unsigned int i = 0; i < m_dealsVec.size(); i++)			
	{
		ss << left << setw(18) << m_dealsVec.at(i).at(1) << "|";
		ss << setw(25) << m_dealsVec.at(i).at(2) << "|";
		ss << setw(16) << m_dealsVec.at(i).at(3) << "|";
		ss << setw(16) << m_dealsVec.at(i).at(4) << "|";
		ss << setw(16) << m_dealsVec.at(i).at(5) << "|";
		ss << setw(4) << m_dealsVec.at(i).at(6) << "|" << endl;

		
	}
	}
	catch (const out_of_range&e)
	{
		cerr << e.what() << endl;
		return false;

	}

	m_dealsString = ss.str();
	return true;
}

bool DataWorker::yesNoCall(){ // mehrfach genutzte reine Ja/Nein Abfrage 
	string response;
	cout << " [j]a oder [n]ein : ";
	do
	{
		cin >> response;
		if ((response == "J") || (response == "j"))
		{
			return true;
		}
		else if ((response == "N") || (response == "n"))
		{
			return false;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Eingabe war nicht korrekt, bitte wiederholen Sie Ihre Auswahl.";
		cout << " [j]a oder [n]ein : ";
	} while (1);
}

void DataWorker::convertProdProcessVecToString()  // Der Fertigungsablauf wird aus dem 2D Vektor gelesen und für Ausgaben(Bildschirm/ Datei) verarbeitet
{
	stringstream ss,ll;
	ll << setfill('-') << setw(96) << " ";
	ss << endl;
	ss << m_prodProcessHeader.str();
	ss << ll.str() << endl;
	for (unsigned int i = 0; i < m_prodProcessVec.size(); i++)			
	{
		ss << left << setw(18) << m_prodProcessVec[i][1] << "|";
		ss << setw(25) << m_prodProcessVec[i][2] << "|";
		ss << setw(17) << m_prodProcessVec[i][m_prodProcessValues.option + 2] << "|";
		ss << setw(4) << m_prodProcessVec[i][6] << "|" << endl;
	}
	ss << ll.str() << endl;
	ss << "Es wurden: " << m_prodProcessValues.pieces << " Stueck beauftragt. " << " | ";
	ss << "Gesamtkosten: " << m_prodProcessValues.cost << " Euro " << " | ";
	ss << "Gesamtzeitbedarf: " << m_prodProcessValues.time <<" Tage " << " | " << endl;
	ss << ll.str() << endl;
	m_prodProcessString = ss.str();
}

void DataWorker::sortProdProcessName() // Die Angebote im 2D Vektor werden nach Firmen Namen sortiert
{
	// sort arbeitet mit den Iteralen und der Funktion, welche durch eine Lambda Funktion realisiert wird
	// diese prüft ob größer oder kleiner
	sort(m_dealsVec.begin(), m_dealsVec.end(),
	[](const vector<string>& lhs, const vector<string>& rhs) {return lhs[1] < rhs[1]; });
	convertDealsVecToString();
}

void DataWorker::sortProdProcessService() // Die Angebote im 2D Vektor werden nach Fertigungsschritt sortiert
{
	// sort arbeitet mit den Iteralen und der Funktion, welche durch eine Lambda Funktion realisiert wird
	// diese prüft ob größer oder kleiner
	sort(m_dealsVec.begin(), m_dealsVec.end(),
		[](const vector<string>& lhs, const vector<string>& rhs) {return lhs[2] < rhs[2]; });
	convertDealsVecToString();
}

void DataWorker::comparePathDeals(int rOpt) // aus Dijkstra-Edges und Angebots-Daten wird ID verglichen und Fertigungsablauf erstellt (2D Vektor).
{
	m_prodProcessVec.clear();	
	for (auto e : m_path) {			// Die Dijkstra Kanten abarbeiten
		for (vector<string> & i : m_dealsVec) 
		{
			if (i[0] == to_string(e->getID())) // mit dem Angebotsvektor nach ID vergleichen
			{
				m_prodProcessVec.push_back(i); // entsprechende Zeile speichern
			}	
		}
	}
}

void DataWorker::addCost(int rOpt, int rnumber) // Kosten aus dem Fertigungsablauf 2D Vektor werden addiert
{
	double cost = 0;
	for (auto i : m_prodProcessVec)		// der 2D Vektor wird abgearbeitet und Kosten addiert
	{
		cost = cost + stod(i[rOpt+2]); // Losgröße ist in Abhängigkeit der rOpt Zahl welche sich aus der Stückzahl ergab
	}
	m_prodProcessValues.cost = cost*rnumber; // wichtige Information werden abgespeichert und stehen anderen Funktionen zur Verfügung
	m_prodProcessValues.pieces = rnumber;
	m_prodProcessValues.option = rOpt;

}

string & DataWorker::getProdProcessString() // Getter für erstellten Ausgabe String vom Fertigungsablauf
{
	return m_prodProcessString;
}

string & DataWorker::getDealsString() // Getter für erstellten Ausgabe String von den Angeboten
{
	return(m_dealsString);
}

void DataWorker::addTime() // Die Dauer der parallel Ablaufenden Fertigungsprozesse wird addiert
{
	//ersten Parallelen
	int TL = 0;
	int TR = 0; //TL = Time Leiterplatte
	if (stoi(m_prodProcessVec[0][6]) > stoi(m_prodProcessVec[1][6]))
		TL = TL + stoi(m_prodProcessVec[0][6]);
	else TL = TL + stoi(m_prodProcessVec[1][6]);
	//Zeit addieren bis einschl. Leiterplatten versiegeln
	for (int i = 2; i<=5;i++ )
	{
		TL = TL + stoi(m_prodProcessVec[i][6]);
	}
	//zweiten Parallelen
	if (stoi(m_prodProcessVec[7][6]) > stoi(m_prodProcessVec[8][6]))
		TR = TR + stoi(m_prodProcessVec[0][6]);
	else TR = TR + stoi(m_prodProcessVec[8][6]);
	//Zeit addieren bis einschl. Gehäuse montieren
	for (int i = 5; i <= 6; i++)
	{
		TR = TR + stoi(m_prodProcessVec[i][6]);
	}
	TR = TR + stoi(m_prodProcessVec[9][6]);

	// Parallelel Zyklen werden verglichen und längere Zeit genommen
	if (TR > TL) TL = TR;

	// Restliche Zeit wird addiert
	for (int i = 10; i <= 11; i++)
	{
		TL = TL + stoi(m_prodProcessVec[i][6]);
	}
	m_prodProcessValues.time = TL;
}

void DataWorker::buildGraphStructure() //Hier wird die Struktur des Graphen abgebildet, gespeichert und überall gebraucht
{
	// Aufbau der Informationen: Name = (Fertigungsreihenfolge,(Startknoten, Zielknoten))
	m_graphStructure["Leiterplatte fertigen"] = make_pair(1,make_pair(1, 2));
	m_graphStructure["Leiterplatte bestuecken"] = make_pair(3, make_pair(2, 3));
	m_graphStructure["Leiterplatte pruefen"] = make_pair(4, make_pair(3, 4));
	m_graphStructure["Leiterplatte versiegeln"] = make_pair(5, make_pair(4, 11));
	m_graphStructure["Bauelemente bereitstellen"] = make_pair(2, make_pair(5, 2));
	m_graphStructure["Anbauteile bereitstellen"] = make_pair(8, make_pair(6, 10));
	m_graphStructure["Gehaeuse fraesen"] = make_pair(6, make_pair(7, 8));
	m_graphStructure["Gehaeuse entgraten"] = make_pair(7, make_pair(8, 9));
	m_graphStructure["Gehaeuse lackieren"] = make_pair(9, make_pair(9, 10));
	m_graphStructure["Gehaeuse montieren"] = make_pair(10, make_pair(10, 11));
	m_graphStructure["Leiterplatte einbauen"] = make_pair(11, make_pair(11, 12));
	m_graphStructure["Geraet testen"] = make_pair(12, make_pair(12, 13));
}

void DataWorker::buildNodes() //Die benötigten Knoten werden erstellen und mit dem Graphen verknüpfen
{
	// Damit alle Knoten erstellt werden wird der gleiche Container wie bei den Kanten ausgelesen
	// Dort stehen alle benötigten Knoten in den Pairs(Source,Destination)
	// Es werden alle abgearbeitet und sollten Sie schon vorhanden sein, nicht neu erstellt
	try
	{
		for (const auto & c:m_graphStructure) {
			if (!m_graph.findNode(to_string(c.second.second.first))) {
				Node *pNode = new Node(to_string(c.second.second.first));
				m_graph.addNode(pNode);
			}

			if (!m_graph.findNode(to_string(c.second.second.second))) {
				Node *pNode = new Node(to_string(c.second.second.second));
				m_graph.addNode(pNode);
			}
		}
	}
	catch (const GraphException&e)
	{
		cerr << e.what() << endl;
	}
}

void DataWorker::buildEdges() //Die benötigten Kante erstellen und mit dem Graphen und den Knoten verbinden
{
	try
	{
		for (const auto &c : m_dealsVec) {
			/*recht Komplex aber Sinnvoll: die Kanten werden erstellt mit den Informationen aus der bereits vorher erstellten Map/pair/pair Container
			Dort steht der Name der verbundenen Knoten drin - was bei uns nur Zahlen sind die in Strings umgewandelt werden, sowie alle Kosten(Zeit/Losgrößen)
			*/
			Process *pProcess = new Process(stoi(c[0]),*m_graph.findNode(to_string(m_graphStructure[c[2]].second.first)), *m_graph.findNode(to_string(m_graphStructure[c[2]].second.second)),stod(c[3]), stod(c[4]), stod(c[5]), stod(c[6]));
			m_graph.addEdge(pProcess);
		}

	}
	catch (const GraphException&e)
	{
		cerr << e.what() << endl;
	}
}

vector<vector<string>>& DataWorker::getOptWay() // Getter für den Fertigungsablauf 2Vektor
{
	return m_prodProcessVec;
}

void DataWorker::runDijkstra(int rOpt) // Dijkstra Algorithmus der durch die Graphenteilabschnitte läuft
{
	m_path.clear();
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("11"), *m_graph.findNode("13"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("10"), *m_graph.findNode("11"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("6"), *m_graph.findNode("10"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("7"), *m_graph.findNode("10"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("2"), *m_graph.findNode("11"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("5"), *m_graph.findNode("2"), rOpt);
	m_graph.findShortestPathDijkstra(m_path, *m_graph.findNode("1"), *m_graph.findNode("2"), rOpt);	
}
