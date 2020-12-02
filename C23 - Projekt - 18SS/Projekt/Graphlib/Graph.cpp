#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <string>
#include <map>

using namespace std;

//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	// - soll einen Node mit der gegebenen id in m_nodes suchen
	// - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
	// - gibt NULL zurück, falls kein Node mit der id gefunden wurde.

	for (Node* it : m_nodes)
		if (it->getId() == id)
			return it;
	return NULL;

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
	// und anschließend ein paar Nodes im Graph suchen.
	// Prüfen Sie, ob der Node gefunden wurden und geben Sie die ID auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	// Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
	if (findNode(pNewNode->getId()))
	{
		// Falls ja: Exception werfen
		string error = "Node " + pNewNode->getId() + " existiert schon in Graph.";
		GraphException e(error);
		throw e;
	}
	else
	{	// Falls nein:
		//  - den neuen Node 'pNewNode' in m_nodes einfügen
		//  - Referenz auf den neuen Node zurück geben 
		m_nodes.push_back(pNewNode);
		return *pNewNode;
	}

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
	// Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	// - die neue Edge 'pNewEdge' in m_edges einfügen
	// - Referenz auf die neue Edge zurück geben
	m_edges.push_back(pNewEdge);
	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)
	if (!findNode(pNewEdge->getSrcNode().getId()))
		addNode(&(pNewEdge->getSrcNode()));
	if (!findNode(pNewEdge->getDstNode().getId()))
		addNode(&(pNewEdge->getDstNode()));

	return *pNewEdge;
	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
	// Testen Sie mit der Funktion 'findEdges', ob die hinzugefügten Edges im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	// - soll alle Edges im Graph löschen (delete)
	for (auto i : m_edges)
		delete i;
	// - soll alle Nodes im Graph löschen (delete)
	for (auto i : m_nodes)
		delete i;
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
	Node *pN = &rNode;

	// - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!

	// !!! Dieser Bereich war auskommentiert, jetzt in neuer Form wieder drin

	for (auto it = m_edges.begin(); it != m_edges.end(); /* hier nichts! */)
	{
		Edge *pE = *it;
		// der Node ist Source-Node der aktuellen Kante
		if (&(pE->getSrcNode()) == pN)
		{
			it = m_edges.erase(it); // löschen und Iterator berichtigen
			delete pE;
		}
		// der Node ist Destination-Node der aktuellen Kante
		else if (&(pE->getDstNode()) == pN)
		{
			pE->getSrcNode().getOutEdges().remove(pE);
			it = m_edges.erase(it);  // löschen und Iterator berichtigen
			delete pE;
		}
		else
			// nichts tun außer Iterator einen Schritt vorstellen
			++it;
	}

	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
	// 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
	// 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!
	m_nodes.remove(pN);
	delete pN;

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
	// und anschließend einzelne Nodes wieder löschen.
	// Testen Sie mit der Funktion 'findNode', ob die gelöschten Nodes noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{

	// - der Pointer auf rEdge muss aus m_edges entfernt werden!
	m_edges.remove(&rEdge);
	// - der Pointer auf rEdge muss mit 'delete' freigegeben werden!
	delete &rEdge; // Note: Im Destruktor löscht Edge sich selbst aus den InEdges/OutEdges des SrcNode und DstNode!
				   // TEST:
				   // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
				   // und anschließend einzelne Edges wieder löschen.
				   // Testen Sie mit der Funktion 'findEdges', ob die gelöschten Edges noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
	std::vector<Edge*> ret;

	// - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
	// - füge die Zeiger der Edges in den vector 'ret' ein.
	for (auto e : m_edges)
		if ((&(e->getSrcNode()) == &rSrc) && (&(e->getDstNode()) == &rDst))
			ret.push_back(e);
	return ret;

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
	// und anschließend ein paar Edges im Graph suchen.
	// Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	
	//Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin,
	//den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
	//Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
	//Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
	//>>>
	//function Dijkstra(Graph, source):

	//create vertex set Q (Vertex ist der Knoten)

	list<Node*> Q; // Warteschlange
	struct tDijkstraNodeEntry {
		double m_distance;
		Node *m_prevNode;
		Edge *m_prevEdge;
	};

	map<Node*, tDijkstraNodeEntry > nodeEntry;

	for (list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		Q.push_back(*it); // aktuellen Knoten der Warteschlange zufügen
		nodeEntry[*it] = { std::numeric_limits<double>::max(), NULL, NULL }; // assoziierte Werte in der Map initialisiseren
	}

	

	//for each vertex v in Graph:         // Initialization
	//dist[v] ← INFINITY                  // Unknown distance from source to v
	//prev[v] ← UNDEFINED                 // Previous node in optimal path from source
	//add v to Q                          // All nodes initially in Q (unvisited nodes)

	//dist[source] ← 0                        // Distance from source to source

	Node* pN = const_cast<Node*>(&rSrcNode);
	nodeEntry[pN].m_distance = 0;

	//while Q is not empty:
	//u ← vertex in Q with min dist[u]    // Source node will be selected first
	//remove u from Q

	while (!Q.empty())
	{
		Node *u = Q.front();
		for (auto n : Q) // Liste durchgehen um den Knoten mit der kleinsten Distanz zu finden
		{
			if (nodeEntry[n].m_distance < nodeEntry[u].m_distance) {
				u = n;
			}
		}
		Q.remove(u); // Entferne den Knoten mit der kleinsten Distanz aus der Warteschlange
					 //for each neighbor v of u:           // where v is still in Q.
					 //alt ← dist[u] + length(u, v)
					 //if alt < dist[v]:               // A shorter path to v has been found
					 //dist[v] ← alt
					 //prev[v] ← u


		for (auto n : u->getOutEdges())
		{
			Node* v = &(n->getDstNode());
			double alt = nodeEntry[u].m_distance + n->getWeight(1);
			if (alt < nodeEntry[v].m_distance) {
				nodeEntry[v].m_distance = alt;
				nodeEntry[v].m_prevNode = u;
				nodeEntry[v].m_prevEdge = n;
			}
		}
	}

	

	//return dist[], prev[]

	Node *currentNode = const_cast<Node*>(&rDstNode);
	while (nodeEntry[currentNode].m_prevNode != NULL)
	{
		rPath.push_front(nodeEntry[currentNode].m_prevEdge);
		currentNode = nodeEntry[currentNode].m_prevNode;
	}
	//<<<

	//Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
	//Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um
	//und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

	//TEST:
	//Testen Sie diese Funktion, indem Sie einen Graph in main.cpp erstellen
	//und sich die kürzesteste Route zwischen 2 Nodes zurückgeben lassen.
	//

}


//---------------------------------------------------------------------------------------------------------------------

