#include "process.h"


// wurde erstellt, damit wir mehrere Gewichtungen für die Kanten speichern können
Process::Process(int ID, Node& rSrc, Node& rDst, double onePack, double tenPack, double hundredPack, double time) : Edge(rSrc, rDst),m_ID(ID), m_onePack(onePack), m_tenPack(tenPack), m_hundredPack(hundredPack), m_time(time) {
	m_weight[1] = m_onePack;
	m_weight[2] = m_tenPack;
	m_weight[3] = m_hundredPack;
	m_weight[4] = m_time;
}


Process::~Process()
{
}

double Process::getWeight(int optChoose)
{
	return m_weight[optChoose];
}

int Process::getID()
{
	return m_ID;
}
