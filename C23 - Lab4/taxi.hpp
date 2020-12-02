//
//  taxi.hpp
//  Labor 4
//
//  Created by Fabian @ Rod on 22.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class   Taxi {

public:
    
    //void init (double verbrauch, double fahrpreis , double maxTankInhalt );
    Taxi(double verbrauch, double fahrpreis , double maxTankInhalt, string name ="", double geldBilanz = 0 );
    Taxi();
    Taxi(const Taxi &copy);
    ~Taxi() {s_count--;};
    void tanken(double aktBenzinPreis);
    void fahrtVerbuchen (double entfernung, bool fahrgaeste);
    inline void setName(string name);
    inline string getName()const;
    //inline void print()const; NUN verwenden wir getstate
    string getState ()const;
    
    
private:
    
    string m_name;
    double m_tagesKm;
    double m_tankInhalt;
    const double m_maxTankInhalt;
    const double m_verbrauchProKm;
    const double m_preisProKm;
    double m_geldBilanz;
    
    static int s_count;
    static int s_index; // Number of ever instantiated instances
   // static int s_index; // Number of ever instantiated instances
};


//Ausgabe der aktuellen Werte für Tageskilometerstands,Tankinhalt und Geldbilanz
//NUN verwenden wir getState()
/*void Taxi::print()const {
    cout << "Name: " << m_name << endl;
    cout << "Tageskilometerstand:" << m_tagesKm << endl;
    cout << "Tankinhalt:" << m_tankInhalt << endl;
    cout << "Geldbilanz:" << fixed << setprecision(2) << m_geldBilanz<< "€" << endl; //Zur Rundung auf 2 Nachkommastallen
}*/

string Taxi::getName() const{
    return m_name;
}

class TaxiException {
    public:
    TaxiException(string what) : m_what (what) {}
    string what() const {
        return m_what;
    }
    private:
        string m_what;
};

void Taxi::setName(string name){
    if (name.length() <= 8){
        if (name.length() == 0){
            stringstream ss;
            ss << "Taxi_";
            ss << setw(3) << setfill('0') << s_index;
            name = ss.str();
        } else {
            m_name = name;
        }
        m_name = name;
    } else {
        // Fehler behandeln -> Exception werfen
        TaxiException e("Name string too long");
        throw e;
    }
}

