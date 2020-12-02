#pragma once
#include "Edge.h"
#include <map>
#include "Graph.h"

class Process :public Edge
{
public:
	// Die Klasse erbt von Edge. Sie wurde erweitert um die Speicherung 4 verschiedener Gewichtungen,
	// sowie der Ausgabe von getWeight in Abhängigkeit der Anfrage einer anderen Methode
	Process(int ID, Node& rSrc, Node& rDst, double onePack, double tenPack, double hundredPack, double time);
	~Process();
	virtual double getWeight(int optChoose);
	int getID();
private:
	std::map<int, double> m_weight;
	double m_onePack;
	double m_tenPack;
	double m_hundredPack;
	double m_time;
	Graph * m_myGraph;
	int m_ID;
};

