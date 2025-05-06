#ifndef FILM_H
#define FILM_H
#include "String.h"
#include <iostream>
#include <fstream>

#include "memtrace.h"

class Film {
	String cim;
	int  ev;
	int hossz;
	Film* kov; //a lista miatt, a beallitasa filmtar dolga lesz hozzaadaskor, letrehozaskor mindig NULL (igy ha utolso elem, nem kell modositani) 
public:

	Film(String cim = "", int ev = 0, int hossz = 0) :cim(cim), ev(ev), hossz(hossz), kov(NULL) {} //az adatokat ellenorizve kapja, elvileg nem johet letre hibas

	String getCim() const { return cim; } //cim lekerese
	void setCim(String& ujcim) { cim = ujcim; } //cim beallitasa
	int getEv()const { return ev; } //ev lekeredezese
	void setEv(int ujev) { ev = ujev; } //ev beallitasa
	int getHossz()const { return hossz; } //hossz lekerese
	void setHossz(int ujhossz) { hossz = ujhossz; } //hossz beallitasa
	Film* getKov()const { return kov; } //kovetkezo lekerdezese
	void setKov(Film* fp = NULL) { kov = fp; } //kovetkezo beallitasa

	virtual void modosit() = 0; //tiszta virtualis modositas
	virtual void kiir(std::ostream&)const = 0; //tiszta virtualis kiiras
	virtual void mentes(std::ofstream& file)const = 0;  //tiszta virtualis mentes
	virtual ~Film() {}; //virtualis destruktor
};


//nem tagfv, de tartalmilag ide tartozik
Film* Letrehoz(int tipus, String cim, int ev, int hossz, String& adat); //beolvasasnal letrehozza a hozzafuzendo elemet

#endif // !FILM_H
