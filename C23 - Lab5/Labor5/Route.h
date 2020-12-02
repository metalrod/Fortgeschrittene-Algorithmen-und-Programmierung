#pragma once
#include "Edge.h"

class Route : public Edge
{
public:
	Route(Node& rSrc, Node& rDst, double dist);
	~Route();
	virtual double getWeight(){return m_dist;}
private:
	double m_dist;
};

