//
//  edge.hpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#pragma once
#include <string>
#include "node.hpp"
using namespace std;

class Edge {
    
public:
    Edge(Node &scr, Node &dst);
    Edge(string scr, string dst);
    string toString() const;
    Node& getScrNode() const;
    Node& getDstNode() const;
    
private:
    Node & m_scrNode;
    Node & m_dstNode;
    string m_scr, m_dst;
};
