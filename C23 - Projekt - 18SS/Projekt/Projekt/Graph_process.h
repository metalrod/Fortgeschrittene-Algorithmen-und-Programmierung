#pragma once
#include "Graph.h"
#include "map"
#include "process.h"

class Graph_process : public Graph
{
public:
	virtual ~Graph_process();
	// der Dijkstra bekommt die Information, nach welcher Gewichtung er den Weg suchen soll
	void virtual findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode, const int choosenWeight);
private:

};

