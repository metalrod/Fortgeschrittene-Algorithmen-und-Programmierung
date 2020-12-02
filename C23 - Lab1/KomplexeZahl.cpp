#include "komplexeZahl.h"

void komplexeZahl::setKartesian(double real, double imag) {

	m_real = real;
	m_imag = imag;
}

double komplexeZahl::abs() {
	double a;
	a = sqrt(m_real * m_real + m_imag * m_imag);
	return a;

}

double komplexeZahl::phi()
{
	return atan2(m_imag, m_real);
}

void komplexeZahl::print() {
	std::cout << "x = " << m_real << " + " << m_imag << "i" << std::endl;
}

double komplexeZahl::getImag()
{
	return m_imag;
}
double komplexeZahl::getReal()
{
	return m_real;
}

void komplexeZahl::setPolar(double abs, double phi)
{
	m_real = abs * cos(phi);
	m_imag = abs * sin(phi);
}

void komplexeZahl::printPolar()
{
	
std::cout << "Die Polarkoordinaten sind: r = " << abs() << " und phi = " << phi() << std::endl;
}

void komplexeZahl::setReal(double real) {
	m_real = real;
}
void komplexeZahl::setImag(double imag) {
	m_imag = imag;
}
