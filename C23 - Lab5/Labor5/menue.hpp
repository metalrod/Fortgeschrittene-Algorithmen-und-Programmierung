//
//  menue.hpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#pragma once
#include "Node.h"
#include "Graph.h"
#include <string>

using namespace std;

void showMenue();
int benutzerAuswahl();
int nutzerTaxiAuswahl();

Node* nutzerOrtAuswahl(Graph& g, string ortsArt);

