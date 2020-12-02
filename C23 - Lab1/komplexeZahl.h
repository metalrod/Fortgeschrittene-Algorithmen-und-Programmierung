#pragma once
#include <iostream>

class komplexeZahl {
public:
	void setKartesian(double real, double imag);
	double abs();
	double phi();
	void print();
	double getReal();
	void setPolar(double abs, double phi);
	void printPolar();
	void setImag(double imag);
	void setReal(double real);
	double getImag();


private:

	double m_real, m_imag;
	//double m_abs, m_phi;

};
