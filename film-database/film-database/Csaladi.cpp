#include<iostream>
#include <fstream>
#include <stdexcept>
#include "Csaladi.h"
#include "memtrace.h"

//Felvesz fv: nem kap inputot, standard bemenetrol olvassa be az adatokat, ellenoriz, majd visszaadja a letrehozott Film pointert
Film* CsalFelvesz() {
	String cim;
	int korh;
	int ev;
	int hossz;

	std::cout << "Kerem a cimet" << std::endl;
	std::cin >> cim;

	std::cout << "Kerem az evet" << std::endl;
	std::cin >> ev;
	if (std::cin.bad() || ev <= 0 || ev > 2023) throw std::out_of_range("Nem megfelelo evszam\n");

	std::cout << "Kerem a hosszat" << std::endl;
	std::cin >> hossz;
	if (std::cin.bad() || hossz <= 0) throw std::out_of_range("Nem megfelelo hossz\n");

	std::cout << "Kerem a korhatart" << std::endl;
	std::cin >> korh;
	if (std::cin.bad() || korh <= 0) throw std::out_of_range("Nem megfelelo Korhatar\n");

	return(new Csaladi(cim, ev, hossz, korh));
}

//Kiir fv: parameterkent a kiiras celjat kapja, kiirja minden adatat az adott objektumnak, nem ad vissza semmit
void Csaladi::kiir(std::ostream& os) const {
	os << this->getCim() << "(" << this->getEv() << "): " << this->getHossz() << "(perc) " << korhatar << "+" << std::endl;

}
//Mentes fv: parameterkent megkapja a falt, amibe irni akarunk, beleirja minden adatat az adott objektumnak, nem ad vissza semmit
void Csaladi::mentes(std::ofstream& ofs)const {
	ofs << "2;\n" << this->getCim() << ";\n" << this->getEv() << ";\n" << this->getHossz() << ";\n" << this->getKorhatar() << ";\n";
}

//Modosit fv: nem ka parametert, lekerdezi, hogy mit modositson es mi legyen az uj adat, setterekkel beallitja, nem ad vissza semmit
//(Ellenorzi az adatokat)
void Csaladi::modosit() {
	kiir(std::cout);
	String string;

	std::cout << "Mit szeretne modositani?\n\nCim(1)\nEv(2)\nHossz(3)\nKorhatar(4)" << std::endl;
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
		std::cout << "Kerem az uj korhatart" << std::endl;
		int korh;
		std::cin >> korh;
		if (std::cin.bad() || korh <= 0) throw std::out_of_range("Nem megfelelo korhatar\n");

		setKorhatar(korh);

		break;

	default:
		std::cout << "Hibas input" << std::endl; //formasag, nem jut el ide a kod

	}
}
//destruktor
Csaladi::~Csaladi() {};

/*Csaladi::Csaladi(Csaladi& cs) {
	korhatar = cs.getKorhatar();
	setEv(cs.getEv());
	String temp = cs.getCim();
	setCim(temp);
	setHossz(getHossz());
	setKov(getKov());
}*/