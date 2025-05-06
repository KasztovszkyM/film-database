#ifndef CSALADI_H
#define CSALADI_H

#include "Film.h"
#include <fstream>

#include"memtrace.h"
class Csaladi : public Film {
	int korhatar;
public:
	Csaladi(String cim, int ev = 0, int hossz = 0, int korhatar = 0) : Film(cim, ev, hossz), korhatar(korhatar) {} //adatokat ellenorizve kapja
	//Csaladi(Csaladi&f);
	int getKorhatar()const { return korhatar; } //korhatar lekerdezes
	void setKorhatar(int korh) { korhatar = korh; } //korhatar beallitasa
	void kiir(std::ostream&) const; //kiiras, nem valtoztat
	void mentes(std::ofstream&) const; //mentes, nem valtoztat
	void modosit(); //modositas, az adatokat standard inputon

	~Csaladi();
};

Film* CsalFelvesz();  //beveszi az inputokat, visszaadja a pointert

#endif // !CSALADI_H
