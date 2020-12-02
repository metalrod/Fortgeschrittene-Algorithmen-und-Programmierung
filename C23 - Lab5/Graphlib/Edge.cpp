#include "Edge.h"


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(Node& rSrc, Node& rDst) : m_rSrc(rSrc), m_rDst(rDst)
{
    // fügt die Edge (this) in m_outgoingEdges des Source-Node ein.
    // fügt die Edge (this) in m_incomingEdges des Destination-Node ein.
	rSrc.getOutEdges().push_back(this);
	rDst.getInEdges().push_back(this);

    // Hinweis: die Funktionen Node::getOutEdges() und Node::getInEdges() verwenden!

    // TEST:
    // Erstellen Sie in main.cpp eine Edge und prüfen Sie, ob die Edge
    // korrekt in m_outgoingEdges bzw. m_incomingEdges eingefügt wurde!
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : m_rSrc(rOther.m_rSrc), m_rDst(rOther.m_rDst)
{
    // macht dasselbe wie 'Edge(Node& rSrc, Node& rDst)'
	rOther.m_rSrc.getOutEdges().push_back(this);
	rOther.m_rDst.getInEdges().push_back(this);
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
    // - entfernt die Edge (this) aus m_outgoingEdges im Source-Node
    // - entfernt die Edge (this) aus m_incomingEdges im Destination-Node
	m_rSrc.getOutEdges().remove(this);
	m_rDst.getInEdges().remove(this);

    // TEST:
    // Erstellen Sie in main.cpp drei Edges, die jeweils den selben Source- und Destination-Node haben.
    // Löschen Sie eine Edge wieder!
    // Prüfen Sie, ob die gelöschte Edge aus m_outgoingEdges bzw. m_incomingEdges entfernt wurde!

    // Hinweis: arbeiten Sie mit 'new' und 'delete'!
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
    // - gibt true zurück, wenn rNode entweder m_rSrc oder m_rDst ist.
    // Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
	return (((&rNode == &m_rSrc)) || (&rNode == &m_rDst));
    return false;
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
    std::string result;
    result = m_rSrc.getId() + " -> " + m_rDst.getId();
    return result;
}


//---------------------------------------------------------------------------------------------------------------------
