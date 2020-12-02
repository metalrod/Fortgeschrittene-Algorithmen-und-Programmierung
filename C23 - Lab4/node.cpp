//
//  Node.cpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include "node.hpp"
#include <sstream>
#include <iomanip> //für Stringstream Manipulation

int Node::s_numInstances = 0;


Node::Node(string id):m_id(id){
    s_numInstances ++;
    
    for(unsigned int i=0; i < id.length(); i++){
        if (!isalnum(id[i])){
            //string error("Id enthaelt nicht-alphanumerische Zeichen");

            NodeIdException error("Id enthaelt nicht-alphanumerische Zeichen", id, i+1);
            throw error;
        }
    }
  
}
Node::Node(){
    s_numInstances ++;
    
    stringstream ss;
    ss << "Node" << setw(4) << setfill('0') << s_numInstances;
    m_id = ss.str();
}

string Node::getId()const{
    return m_id;
}


NodeIdException::NodeIdException(string error, string id, unsigned int loc): m_error(error), m_id(id),m_loc(loc){
    
}

string NodeIdException::getError() const {
    stringstream ss;
    ss << m_error << " im Id= " << m_id << " an Position " << m_loc;
    return ss.str();
}
