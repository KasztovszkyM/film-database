#include <iostream>
#include <stdexcept>
#include "Dokumentum.h"

#include "memtrace.h"

//Dokumentum felvesz fv: Beolvassa az adatokat standard inputrol, ha hibas akkor throw-ol, egyebkent letrehoz egy Film pointert az adatokbol
Film* DokFelvesz() {
	String cim;
	int hossz;
	int ev;
	String leiras;

	std::cout << "Kerem a cimet" << std::endl;
	std::cin >> cim;

	std::cout << "Kerem az evet" << std::endl;
	std::cin >> ev;
	if (std::cin.fail() || ev <= 0 || ev > 2023) throw(std::out_of_range("Nem megfelelo evszam\n"));

	std::cout << "Kerem a hosszat" << std::endl;
	std::cin >> hossz;
	if (std::cin.fail() || hossz <= 0) throw(std::out_of_range("Nem megfelelo hossz\n"));

	std::cout << "Kerem a leirast" << std::endl;
	std::cin >> leiras;

	return(new Dokumentum(cim, ev, hossz, leiras));
}

//Kiir fv: prameterkent a kiiras celjat kapja meg, kiirja az adott objektum adatait, nem ad vissza semmit
void Dokumentum::kiir(std::ostream& os) const {
	os << this->getCim() << "(" << this->getEv() << "): " << this->getHossz() << "(perc) " << "Leiras: " << *(this->getLeiras()) << std::endl;
}

//Mentes fv: parameterkent megkapja a cel fajlt, belirja az adott objektum adatait, nem ad vissza semmit
void Dokumentum::mentes(std::ofstream& ofs)const {
	ofs << "1;\n" << this->getCim() << ";\n" << this->getEv() << ";\n" << this->getHossz() << ";\n" << *(this->getLeiras()) << ";\n";
}

//Modosit fv: nem kap parametert, a felhasznalo valaszthatja ki mit szeretne modositani, ezt standard inputon bekeri a fv, majd setterekkel beallitja
//(Vegez adatellenorzest)
void Dokumentum::modosit() {
	kiir(std::cout);
	String string;

	std::cout << "Mit szeretne modositani?\n\nCim(1)\nEv(2)\nHossz(3)\nLeiras(4)" << std::endl;
	int sel;
	std::cin >> sel;
	if (std::cin.fail()) throw std::invalid_argument("Kerem csak szamot irjon be\n");

	switch (sel) {
	case 1:
		std::cout << "Kerem az uj cimet" << std::endl;
		std::cin >> string;
		setCim(string);
		break;

	case 2:
		std::cout << "Kerem az uj evet" << std::endl;
		int ev;
		std::cin >> ev;
		if (std::cin.bad() || ev <= 0 || ev > 2023) throw std::out_of_range("Nem megfelelo evszam\n");

		setEv(ev);
		break;

	case 3:
		std::cout << "Kerem az uj hosszt" << std::endl;
		int hossz;
		std::cin >> hossz;
		if (std::cin.bad() || hossz <= 0) throw std::out_of_range("Nem megfelelo hossz\n");

		setHossz(hossz);
		break;

	case 4:
		std::cout << "Kerem az uj leirast" << std::endl;
		std::cin >> string;
		setLeiras(string);

		break;

	default:
		std::cout << "Hibas input" << std::endl; //csak formasag, nem jut ide el a kod
	}
}

/*Dokumentum::Dokumentum(Dokumentum& d) {
	String temp = *d.getLeiras();
	setLeiras(temp);
	setEv(d.getEv());
	temp = d.getCim();
	setCim(temp);
	setHossz(getHossz());
	setKov(getKov());
}*/