//
//  Node.hpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#pragma once
#include <string>
using namespace std;

class NodeIdException{
    
public:
    NodeIdException(string error, string id, unsigned int loc);
    string getError() const;
private:
    string m_error;
    string m_id;
    unsigned int m_loc;
};

class Node {

public:
    Node();
    Node(string id);
    string getId() const;
    
private:
    string m_id;
    static int s_numInstances;
};

