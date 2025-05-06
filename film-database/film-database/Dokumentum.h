#ifndef DOKUMENTUM_H
#define DOKUMENTUM_H

#include "String.h"
#include "Film.h"
#include <fstream>

#include "memtrace.h"

class Dokumentum :public Film {
	String* leiras;
public:
	Dokumentum(String cim, int ev, int hossz, String& leiras) :Film(cim, ev, hossz), leiras(new String(leiras)) {} //minden adatot ellenorizve kap
	//Dokumentum(Dokumentum&);

	String* getLeiras()const { return leiras; } //leiras lekerdezese
	void setLeiras(String& ujleiras) { //leiras beallitasa
		delete leiras;
		leiras = new String(ujleiras);
	}
	void kiir(std::ostream&) const; //kiiras, nem modosit
	void mentes(std::ofstream& file) const; //ment, nem modosit
	void modosit(); //modositas, 

	~Dokumentum() { //fel kell szabaditani a dinamikusan foglalt leirast
		delete leiras;
	}


};

Film* DokFelvesz(); //dokumentumot letrehoz bevitt adatok alapjan

#endif // !DOKUMENTUM_H
