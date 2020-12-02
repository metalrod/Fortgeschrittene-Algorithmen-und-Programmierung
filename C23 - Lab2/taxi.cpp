//
//  taxi.cpp
//  Labor 2
//
//  Created by Fabian @ Rod on 08.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include "taxi.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
    
Taxi::Taxi(double verbrauch, double fahrpreis, double maxTankInhalt)
     :m_maxTankInhalt(maxTankInhalt), m_verbrauchProKm(verbrauch), m_preisProKm(fahrpreis) // Initialisierungsliste
{
    m_geldBilanz = 0;
    m_tagesKm = 0;
    m_tankInhalt = m_maxTankInhalt;
}

/*
void Taxi::init(double verbrauch, double fahrpreis, double maxTankInhalt) { 
    m_geldBilanz = 0;
    m_tagesKm = 0;
    m_verbrauchProKm = verbrauch;
    m_maxTankInhalt = maxTankInhalt;
    m_preisProKm = fahrpreis;
    m_tankInhalt = m_maxTankInhalt;
}
*/

void Taxi::fahrtVerbuchen(double entfernung, bool fahrgaeste) { 
    double benoetigterTreibstof = entfernung * m_verbrauchProKm;
    if ( benoetigterTreibstof <= m_tankInhalt) // Treibstoff reicht
    {
        m_tankInhalt -= benoetigterTreibstof;
        m_tagesKm += entfernung;
        
        if (fahrgaeste) {
            m_geldBilanz += entfernung * m_preisProKm;
        }
        
    } else { cout << "Fehler: Tankinhalt nicht ausreichend" << endl; }
}

void Taxi::tanken(double aktBenzinPreis) { 
    double tankdifferenz =  m_maxTankInhalt - m_tankInhalt;
    if (tankdifferenz >0){ // Laufzeit Optimierung --> wenn häufig tanken aufgerudfen wird
        if (m_geldBilanz <= tankdifferenz*aktBenzinPreis){ // ich habe zuwenig Geld
            tankdifferenz = m_geldBilanz/ aktBenzinPreis; // ich tanke soviel Geld ich habe
        }
        m_tankInhalt += tankdifferenz;
        m_geldBilanz -= tankdifferenz * aktBenzinPreis;
    }
    
}
//Ausgabe der aktuellen Werte für Tageskilometerstands,Tankinhalt und Geldbilanz
void Taxi::print()const {
    cout << "Tageskilometerstand:" << m_tagesKm << endl;
    cout << "Tankinhalt:" << m_tankInhalt << endl;
    cout << "Geldbilanz:" << fixed << setprecision(2) << m_geldBilanz<< "€" << endl; //Zur Rundung auf 2 Nachkommastallen
}




