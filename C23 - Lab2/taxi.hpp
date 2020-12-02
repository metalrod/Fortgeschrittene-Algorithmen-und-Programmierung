//
//  taxi.hpp
//  Labor 2
//
//  Created by Fabian @ Rod on 08.05.18.
//  Copyright © 2018 Fabian @ Rod. All rights reserved.
//

#pragma once

class   Taxi {

public:
    
    //void init (double verbrauch, double fahrpreis , double maxTankInhalt );
    Taxi(double verbrauch, double fahrpreis , double maxTankInhalt);
    void tanken(double aktBenzinPreis);
    void fahrtVerbuchen (double entfernung, bool fahrgaeste);
    void print()const;
    
private:
    double m_tagesKm;
    double m_tankInhalt;
    const double m_maxTankInhalt;
    const double m_verbrauchProKm;
    const double m_preisProKm;
    double m_geldBilanz;
};

