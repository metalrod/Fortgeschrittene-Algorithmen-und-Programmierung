//
//  main.cpp
//  Labor 2
//
//  Created by Fabian @ Rod on 08.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include <iostream>
#include "taxi.hpp"
#include "menue.hpp"

using namespace std;

int main(void)
{
    int auswahl = 0;
    int taxi = 0;
    double entfernung;
    double preis;
    Taxi* pTaxi =0;
    
    Taxi t1(7.2/100, 0.7, 75.0);
    Taxi t2(7.2/100, 0.7, 75.0);
    //Taxi t1;
    //Taxi t2;
    //t1.init(12.5/100, 0.95, 90.0);
    //t1.init(7.2/100, 0.7, 75.0);
    t1.fahrtVerbuchen(100, true);
    t1.tanken(1.5);
    
    t1.print();
    
    t1.fahrtVerbuchen(800, false);
    t1.tanken(1.5);

    t1.print();
  
    while (auswahl !=5 )
    {
        showMenue();
        auswahl = benutzerAuswahl();
        if (auswahl !=5){
            taxi = nutzerTaxiAuswahl();
            pTaxi = (taxi == 1 ? &t1 : &t2);
        }
        
        switch (auswahl)
        {
            case 1:
                cout << "Bitte geben Sie die Entfernung an: ";
                cin >> entfernung;
                pTaxi->fahrtVerbuchen(entfernung, true);
                break;
            case 2:
                cout << "Bitte geben Sie die Entfernung an: ";
                cin >> entfernung;
                pTaxi->fahrtVerbuchen(entfernung, false);
                break;
            case 3:
                cout << "Bitte geben Sie den aktuellen Benzinpreis ein: ";
                cin >> preis;
                pTaxi->tanken(preis);
                break;
            case 4:
                pTaxi->print();
            case 5:
                //Aufruf;
                break;
        }
    }
    
    cout << "Press enter to continue ...";
    cin.get();
    
    return 0;
    
}
