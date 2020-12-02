//
//  main.cpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include <iostream>
#include "taxi.hpp"
#include "menue.hpp"
#include "node.hpp"
#include "edge.hpp"

using namespace std;

int main(void)
{
    Node *pN1 = 0, *pN2 = 0;
    
    
    try {
        
        
        Node n1;
        Node n2("Knoten");
        Edge e1(n1,n2);
        Edge e2("Kn3", "Kn4%&"); // Auch hier funktioniert es!
        cout << "n1 = " << n1.getId() << endl;
        cout << "n2 = " << n2.getId() << endl;
        cout << "e1 = " << e1.toString() << endl;
        cout << "e2 = " << e2.toString() << endl;
        
        pN1 = new Node("Kn5");
        pN2 = new Node("Kn6&%§");
    }
    catch(const NodeIdException& e){
        cout << e.getError() << endl;
    }
    /*catch(string e) {
        cout << "Fehler: " << e << endl;
    }*/

    delete pN1;
    delete pN2; //Delete kann mit Null Zeigern arbeiten
    
    int auswahl = 0;
    int taxi = 0;
    double entfernung;
    double preis;
    //Taxi* pTaxi =0;
    
    try {
        //Taxi t1(7.2/100, 0.7, 75.0, "Mercedes", 200.0);
        //Taxi t2(7.2/100, 0.7, 75.0);
        //Taxi t3;
        
        Taxi* taxiList[2];
        taxiList[0] = new Taxi(7.2/100, 0.7, 75.0, "Mercedes", 200.0);
        taxiList[1] = new Taxi(12.5/100, 0.95, 90.0, "Opel");
        taxiList[1]->setName("Opel");
        
        
        Taxi t1;
        Taxi t2(t1);




        //Taxi t2;
        //t1.init(12.5/100, 0.95, 90.0);
        //t1.init(7.2/100, 0.7, 75.0);
        taxiList[0]->fahrtVerbuchen(100, true);
        taxiList[0]->tanken(1.5);
        
        //t1.print();
        cout << taxiList[0]->getState() << endl;
        
        
        taxiList[0]->fahrtVerbuchen(800, false);
        taxiList[0]->tanken(1.5);

        //(t1.print();
        cout << taxiList[1]->getState() << endl;

      
        while (auswahl !=5 )
        {
            showMenue();
            auswahl = benutzerAuswahl();
            if (auswahl !=5){
                // getName() für Taxi um Taxis anzuzeigen
                cout << taxiList[0]->getName() << endl;
                cout << taxiList[1]->getName() << endl;
                taxi = nutzerTaxiAuswahl();
                //pTaxi = (taxi == 1 ? &t1 : &t2);
                
            }
            
            switch (auswahl)
            {
                case 1:
                    cout << "Bitte geben Sie die Entfernung an: ";
                    cin >> entfernung;
                    taxiList[taxi]->fahrtVerbuchen(entfernung, true);
                    break;
                case 2:
                    cout << "Bitte geben Sie die Entfernung an: ";
                    cin >> entfernung;
                    taxiList[taxi]->fahrtVerbuchen(entfernung, false);
                    break;
                case 3:
                    cout << "Bitte geben Sie den aktuellen Benzinpreis ein: ";
                    cin >> preis;
                    taxiList[taxi]->tanken(preis);
                    break;
                case 4:
                    //ptaxi->print();
                    cout << taxiList[taxi]->getState() << endl;
                case 5:
                    //Aufruf;
                    break;
            }
        }
        delete taxiList[0];
        delete taxiList[1];
        
        cout << "Press enter to continue ...";
        cin.get();
        }
        catch(const TaxiException& e){
            cout << "Exception: " << e.what() << endl;
        }
    return 0;
    
}

//Ohne try Catch wandert der Error durch und führt zu einem Fehler
