#ifndef FILMTAR_H
#define FILMTAR_H

#include <iostream>
#include <fstream>
#include "Film.h"

#include "memtrace.h"

class Filmtar {
	static const char* fajlnev;
	Film* elso;
public:
	static const char* getFajlnev() { return fajlnev; }

	Filmtar(); //beolvassa egy fajlbol az adatokat es letrehozza a listat

	int static hanysor(std::ifstream& ifs);
	void Torol(String cim = ""); //cimet inputon  fog kerni, egy elemet szabadit fel
	void TeljesTorol(); //destruktorhoz, felszabadit minden elemet
	void Kiir(); //lehet: cim, ev, osszes alapjan; valasztas inputon
	void Felvesz(); //adatokat ker, letrehoz, hozzaad fvt hiv
	void Hozzaad(Film*); //film pointert kap es ezt hozzafuzi a lista vegehez
	void Modosit(); //csak cim alapjan (input)
	void Ment(); //static fajlba menti, egyesevel hivja meg a mentes fveket minden tagra


	class iterator;

	iterator begin() {
		return iterator(*this);
	}

	iterator end() {
		return iterator();
	}





	class iterator {
		Film* akt;
	public:
		Film* getAkt() const { return akt; }
		void setAkt(Film* p) { akt = p; }
		iterator() : akt(NULL) {}
		iterator(const Filmtar& ft) :akt(ft.elso) {}


		iterator& operator++();
		iterator operator++(int);

		bool operator==(const iterator& rhs) const { return akt == rhs.akt; }
		bool operator!=(const iterator& rhs) const { return !operator==(rhs); }

	};

	~Filmtar() { //mindig ment mielott torol
		Ment();
		TeljesTorol();
	}


};

Film* beolvas(std::ifstream&); //az elore megnyitott faljbol olvassa be az adatokat, ezekbol letrehozott pointert visszaadja

#endif // !FILMTAR_H
