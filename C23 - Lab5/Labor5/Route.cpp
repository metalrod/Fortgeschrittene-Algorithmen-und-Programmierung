#include "Route.h"

Route::Route(Node & rSrc, Node & rDst, double dist) : Edge(rSrc, rDst), m_dist(dist)
{
}

Route::~Route()
{
}
