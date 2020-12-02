#include "Graph_process.h"


using namespace std;

Graph_process::~Graph_process()
{
}

void Graph_process::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode, const int choosenWeight)
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
			double alt = nodeEntry[u].m_distance + n->getWeight(choosenWeight);
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
