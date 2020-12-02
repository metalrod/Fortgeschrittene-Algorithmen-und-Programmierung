//
//  taxi.cpp
//  Labor 3
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#include "taxi.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int Taxi::s_count =0;
int Taxi::s_index =0;

Taxi::Taxi(double verbrauch, double fahrpreis, double maxTankInhalt, string name, double geldBilanz)
     :m_maxTankInhalt(maxTankInhalt), m_verbrauchProKm(verbrauch), m_preisProKm(fahrpreis), m_geldBilanz(geldBilanz) // Initialisierungsliste
{
    m_tagesKm = 0;
    m_tankInhalt = m_maxTankInhalt;
    
    setName(name);
    s_count ++; //static Counter beim Konstruieren
    s_index ++;
}

Taxi::Taxi():m_maxTankInhalt(80.0), m_verbrauchProKm(5.5/100.0), m_preisProKm(0.0), m_geldBilanz(0.15),m_tagesKm(0) // Initialisierungsliste
{
    m_tankInhalt = m_maxTankInhalt;
    setName("");
    s_count ++; //static Counter beim Konstruieren
    s_index ++;
}

Taxi::Taxi(const Taxi &copy): m_name(copy.m_name),m_tagesKm(copy.m_tagesKm),m_tankInhalt(copy.m_tankInhalt),m_geldBilanz(copy.m_geldBilanz),m_maxTankInhalt(copy.m_maxTankInhalt),m_verbrauchProKm(copy.m_verbrauchProKm),m_preisProKm(copy.m_preisProKm)
{
    s_count ++;
    s_index ++;
    
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

string Taxi::getState() const { 
    stringstream ss;
    
    ss << left << setw(8) << m_name << " >> ";
    ss << right << fixed << setprecision(2)  << setw(7) << m_tagesKm << " km, ";
    ss << setw(7)<<  m_tankInhalt << " I, ";
    ss << setw(7)<< m_geldBilanz << " Euro";
    
    return ss.str();
}





