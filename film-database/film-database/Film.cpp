#include "Film.h"
#include "Csaladi.h"
#include "Dokumentum.h"

#include "memtrace.h"

//Letrehoz fv: tipus, cim, ev, hossz, adatot kapja meg es ezekbol hozza letre a filmet tipusnak megfeleloen
//Visszateresi ertek a letrehozott Film pointer
Film* Letrehoz(int tipus, String cim, int ev, int hossz, String& adat) {
	if (tipus == 1) { //dokumentum
		Film* uj = new Dokumentum(cim, ev, hossz, adat);
		return uj;
	}
	else if (tipus == 2) { //csaladi
		int korh = atoi(adat.c_str());
		Film* uj = new Csaladi(cim, ev, hossz, korh);
		return uj;
	}

	return NULL; //biztonsag kedveert, de nem jut el ide a kod

}