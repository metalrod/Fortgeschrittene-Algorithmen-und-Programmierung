//
//  edge.cpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include "edge.hpp"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;


Edge::Edge(Node &scr, Node &dst):m_scrNode(scr),m_dstNode(dst) {
    ;
}

Edge::Edge(string scr, string dst):m_scrNode(*(new Node(scr))),m_dstNode(*(new Node(dst))) {
    ;
}

string Edge::toString() const{
    stringstream ss;
    ss << m_scrNode.getId() << " -> " << m_dstNode.getId();
    return ss.str();
}
Node& Edge::getScrNode() const{
    return m_scrNode;
}
Node& Edge::getDstNode() const{
    return m_dstNode;
}
