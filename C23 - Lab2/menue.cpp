//
//  menue.cpp
//  Labor 2
//
//  Created by Fabian @ Rod on 08.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include "menue.hpp"
#include <iostream>

using namespace std;

void showMenue () {
    cout << "1: Fahrt verbuchen mit Fahrgast" << endl;
    cout << "2: Fahrt verbuchen ohne Fahrgast (Leerfahrt)" << endl;
    cout << "3: Tanken" << endl;
    cout << "4: Status ausgeben" << endl;
    cout << "5: Programm beenden" << endl;
}

int benutzerAuswahl (){
    int auswahl = 0;
    while (auswahl < 1 || auswahl > 5){
        cout << "Bitte waehlen Sie einen Menuepunkt aus [1..5]: ";
        cin >> auswahl;
        if (auswahl < 1 || auswahl > 5) {
            cout << "Fehler: Auswahl muss zwischen 1 und 5 liegen." << endl;
        }
    }
    return auswahl;
}

int nutzerTaxiAuswahl(){
    int auswahl = 0;
    while (auswahl < 1 || auswahl > 2){
        cout << "Bitte waehlen Sie ein Taxi zwischen [1..2]: ";
        cin >> auswahl;
        if (auswahl < 1 || auswahl > 2) {
            cout << "Fehler: Auswahl muss zwischen 1 und 2 liegen." << endl;
        }
    }
    return auswahl;
}

