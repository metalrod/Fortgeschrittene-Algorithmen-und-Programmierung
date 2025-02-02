// Labor5.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "Graph.h"
#include "Edge.h"
#include "Node.h"
#include "menue.hpp"
#include "taxi.hpp"
#include "Route.h"



int main()
{

	// test section
	Node *pAlex = new Node("Alexanderplatz");
	Node *pFunkturm = new Node("Funkturm");
	Node *pWannsee = new Node("Strandbad Wannsee");
	Node *pBrndbgTor = new Node("Brandenburg Tor");
	Node *pOstkreuz = new Node("Ostkreuz");
	Node *pRegattastrecke = new Node("Regattastrecke Grünau");
	Node *pGrenzallee = new Node("Grenzallee");
	Node *pZitadelle = new Node("Zitadelle Spandau");


	Route *pR1a = new Route(*pAlex, *pFunkturm, 10.2);
	Route *pR1b = new Route(*pFunkturm, *pAlex, 10.2);

	Route *pR2a = new Route(*pFunkturm, *pWannsee, 11.2);
	Route *pR2b = new Route(*pWannsee, *pFunkturm, 11.2);

	Route *pR3a = new Route(*pWannsee, *pBrndbgTor, 18.0);
	Route *pR3b = new Route(*pBrndbgTor, *pWannsee, 18.0);

	Route *pR4a = new Route(*pBrndbgTor, *pAlex, 2.3);
	Route *pR4b = new Route(*pAlex, *pBrndbgTor, 2.3);

	Route *pR5a = new Route(*pAlex, *pOstkreuz, 6.2);
	Route *pR5b = new Route(*pOstkreuz, *pAlex, 6.2);

	Route *pR6a = new Route(*pOstkreuz, *pRegattastrecke, 14.6);
	Route *pR6b = new Route(*pRegattastrecke, *pOstkreuz, 14.6);

	Route *pR7a = new Route(*pRegattastrecke, *pGrenzallee, 12.8);
	Route *pR7b = new Route(*pGrenzallee, *pRegattastrecke, 12.8);

	Route *pR8a = new Route(*pGrenzallee, *pAlex, 11.2);
	Route *pR8b = new Route(*pAlex, *pGrenzallee, 11.2);
	
	Route *pR9a = new Route(*pGrenzallee, *pFunkturm, 14.9);
	Route *pR9b = new Route(*pFunkturm, *pGrenzallee, 14.9);

	Route *pR10a = new Route(*pFunkturm, *pZitadelle, 8.5);
	Route *pR10b = new Route(*pZitadelle, *pFunkturm, 8.5);



	Graph g;
	try
	{
		g.addNode(pAlex);
		g.addNode(pFunkturm);
		g.addNode(pWannsee);
		g.addNode(pBrndbgTor);
		g.addNode(pOstkreuz);
		g.addNode(pRegattastrecke);
		g.addNode(pGrenzallee);
		g.addNode(pZitadelle);
		g.addEdge(pR1a); g.addEdge(pR1b);
		g.addEdge(pR2a); g.addEdge(pR2b);
		g.addEdge(pR3a); g.addEdge(pR3b);
		g.addEdge(pR4a); g.addEdge(pR4b);
		g.addEdge(pR5a); g.addEdge(pR5b);
		g.addEdge(pR6a); g.addEdge(pR6b);
		g.addEdge(pR7a); g.addEdge(pR7b);
		g.addEdge(pR8a); g.addEdge(pR8b);
		g.addEdge(pR9a); g.addEdge(pR9b);
		g.addEdge(pR10a); g.addEdge(pR10b);

	}
	catch (const GraphException& e) //Konstante Referenze ist besser als ganzes Objekt zu werfen
	{
		cout << e.what() << endl;
	}
	
	deque<Edge*> path;
	g.findShortestPathDijkstra(path, *pAlex, *pFunkturm);
	

	//delete pE2;
	//bool isC = pE1->isConnectedTo(*pN1);
	//isC = pE1->isConnectedTo(*pN3);

	// end of  test section


	int auswahl = 0;
	int taxi = 0;
	double entfernung;
	double preis;
	//Taxi* pTaxi =0;

	try {
		//Taxi t1(7.2/100, 0.7, 75.0, "Mercedes", 200.0);
		//Taxi t2(7.2/100, 0.7, 75.0);
		//Taxi t3;

		Taxi* taxiList[2];
		taxiList[0] = new Taxi(7.2 / 100, 0.7, 75.0, "Mercedes", 200.0);
		taxiList[1] = new Taxi(12.5 / 100, 0.95, 90.0, "Opel");
		taxiList[1]->setName("Opel");


		Taxi t1;
		Taxi t2(t1);




		//Taxi t2;
		//t1.init(12.5/100, 0.95, 90.0);
		//t1.init(7.2/100, 0.7, 75.0);
		//taxiList[0]->fahrtVerbuchen(100, true);
		//taxiList[0]->tanken(1.5);

		////t1.print();
		//cout << taxiList[0]->getState() << endl;


		//taxiList[0]->fahrtVerbuchen(800, false);
		//taxiList[0]->tanken(1.5);

		//(t1.print();
		// cout << taxiList[1]->getState() << endl;

		Node *pStart = NULL, *pZiel = NULL;
		deque<Edge*> path;

		while (auswahl != 5)
		{
			showMenue();
			auswahl = benutzerAuswahl();
			if (auswahl != 5) {
				// getName() für Taxi um Taxis anzuzeigen
				cout << taxiList[0]->getName() << endl;
				cout << taxiList[1]->getName() << endl;
				taxi = nutzerTaxiAuswahl();
				//pTaxi = (taxi == 1 ? &t1 : &t2);

			}

			switch (auswahl)
			{
			case 1:
				pStart = nutzerOrtAuswahl(g, "Startort");
				pZiel = nutzerOrtAuswahl(g, "Zielort");
				g.findShortestPathDijkstra(path, *pStart, *pZiel);
				entfernung = 0.0;
				for (auto e : path) {
					entfernung = entfernung + e->getWeight();
				}
				taxiList[taxi]->fahrtVerbuchen(entfernung, true);
				path.clear();
				break;
			case 2:
				pStart = nutzerOrtAuswahl(g, "Startort");
				pZiel = nutzerOrtAuswahl(g, "Zielort");
				g.findShortestPathDijkstra(path, *pStart, *pZiel);
				entfernung = 0;
				for (auto e : path) {
					entfernung = entfernung + e->getWeight();
				}
				taxiList[taxi]->fahrtVerbuchen(entfernung, false);
				path.clear();
				break;
			case 3:
				cout << "Bitte geben Sie den aktuellen Benzinpreis ein: ";
				cin >> preis;
				taxiList[taxi]->tanken(preis);
				break;
			case 4:
				//ptaxi->print();
				cout << taxiList[taxi]->getState() << endl;
			case 5:
				//Aufruf;
				break;
			}
		}
		delete taxiList[0];
		delete taxiList[1];

		cout << "Press enter to continue ...";
		cin.get();
	}
	catch (const TaxiException& e) {
		cout << "Exception: " << e.what() << endl;
	}
	return 0;

}

