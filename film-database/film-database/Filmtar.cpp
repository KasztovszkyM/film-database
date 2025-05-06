#include "Csaladi.h"
#include "Dokumentum.h"
#include "String.h"
#include "Filmtar.h"
#include "Film.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "memtrace.h"

//faljnev 
const char* Filmtar::fajlnev = "film.txt";

//seged fvek
//Hanysor fv: megadja hany sorbol all a fajl, parameterkent megkapja a fajlt, amibol beolvasunk
//visszaadja a fajlban levo sorok szamat
int Filmtar::hanysor(std::ifstream& ifs) {
	char c;
	int db = 0;

	if (ifs.is_open())//kisse felesleges, mert ha nem meg se hivodik
	{
		while (ifs >> c)
		{
			if (c == ';') db++;
		}

		return db;
	}
	return -1;

}

//Beolvasaa fv: parameterkent a fajl kapja, maibol be akar olvasni, beolvas agy filmnyi adatmennyiseget, visszaadja a beloluk letrehozott Film pointert
Film* beolvas(std::ifstream& ifs) {


	String sor("");
	int tipus = -1;//nem lehetseges, igy jo alapertek
	String cim("");
	int ev = -1; //nem lehetseges, igy jo alapertek
	int hossz = -1; //nem lehetseges, igy jo alapertek
	String extra("");
	int i = 0;
	while (i <= 5) {
		ifs >> sor;
		if (sor.size() != 0) {

			if (tipus != -1 && cim.size() != 0 && ev != -1 && hossz != -1 && extra.size() != 0) {
#if defined __linux__
				ifs.seekg(-5, std::ios::cur);
#elif defined _WIN32
				ifs.seekg(-4, std::ios::cur);
#endif				
				return Letrehoz(tipus, cim, ev, hossz, extra);
			}

			else if (tipus == -1) {
				tipus = atoi(sor.c_str());
				if (tipus <= 0 || tipus > 2) throw std::out_of_range("Nem jo tipus a fajlban");
			}

			else if (cim.size() == 0) {
				cim = sor;
			}

			else if (ev == -1) {
				ev = atoi(sor.c_str());
				if (ev <= 0 || ev > 2023) throw std::out_of_range("Nem jo ev a fajlban");
			}

			else if (hossz == -1) {
				hossz = atoi(sor.c_str());
				if (hossz <= 0) throw std::out_of_range("Nem jo hossz a fajlban");


			}

			else if (extra.size() == 0) {

				extra = sor;
			}
		}
		++i;
	}
	return(Letrehoz(tipus, cim, ev, hossz, extra)); //utolso film miatt, mert ilyenkor cim nem tartalmaz uj sort
};

///////////////////////////////////////////////////  KONSTRUKTOR beolvasas es letrehozas kulon, itt csak hozzaadja a filmeket
Filmtar::Filmtar() :elso(NULL) {
	try {
		std::ifstream fajl(getFajlnev());//megnyit
		if (!fajl) {
			throw std::runtime_error("Nem sikerult megnyitni a fajlt\n"); //ha nem tudja megnyitni
		}


		int sorok = hanysor(fajl); //megszamolja a sorokat

		fajl.clear();
		fajl.seekg(0); //alaphelyzetbe

		for (int i = 0; i <= sorok / 5; ++i) {

			Hozzaad(beolvas(fajl)); //hozzaadja a filmeket
		}
		fajl.close();
	}
	catch (std::out_of_range& e) { //ha hibas adatot tarol a fajl
		std::cout << e.what() << "\nEddig beolvasottak:\n";
		this->Kiir();
	}
	catch (std::runtime_error& e) { //ha nem tudja megnyitni
		std::cout << e.what() << std::endl;
	}
}


//////////////////////////////////////////////////  TELJESTOROL

void Filmtar::TeljesTorol() {
	iterator elso = begin();
	iterator utolso = end();
	iterator temp;
	while (elso != utolso) { //vegigfut a listan es minden elemet felszabadit
		temp = elso;
		++elso;
		delete temp.getAkt();

	}
}
//////////////////////////////////////////////////// HOZZAAD

//paarameterkent a hozzaadni kivant pointert kapja
void Filmtar::Hozzaad(Film* p) {
	iterator elso = begin();
	iterator utolso = end();
	if (elso.getAkt() == NULL) { //abban az esetben, nincs elem a listaban
		this->elso = p;
		return;
	}
	iterator temp = elso; //abban az esetben, ha mar van
	while (elso != utolso) {
		temp = elso;
		++elso;
	}
	temp.getAkt()->setKov(p);

}

///////////////////////////////////////////////  KIIR 


void Filmtar::Kiir() {
	iterator elso = begin();
	iterator utolso = end();
	String cim;

	int szaml = 0; // a ciklushoz

	std::cout << "\n\n Cim alapjan (1)\n Ev alapjan (2)\n Mindent (3)\n [Kilepes (9)]\n" << std::endl;

	int sel;

	std::cin >> sel;
	if (std::cin.fail()) throw(std::invalid_argument("Kerem csak szamot irjon be\n")); //ha rossz input

	switch (sel) {
	case 1:
		std::cout << "Kerem a keresett film cimet\n" << std::endl;

		std::cin >> cim;
		while (elso != utolso) {
			if (elso.getAkt()->getCim() == cim) { elso.getAkt()->kiir(std::cout); szaml++; }
			++elso;
		}
		if (szaml == 0)std::cout << "Nincs ilyen cimu film eltarolva\n" << std::endl;//ha rossz input
		break;


	case 2:
		std::cout << "Kerem a keresett evet\n" << std::endl;
		int ev;
		std::cin >> ev;
		if (std::cin.fail()) throw(std::invalid_argument("Kerem csak szamot irjon be\n"));//ha rossz input
		while (elso != utolso) {

			if (elso.getAkt()->getEv() == ev) { elso.getAkt()->kiir(std::cout); szaml++; }
			++elso;
		}
		if (szaml == 0)std::cout << "Ebbol az evbol nincs film\n" << std::endl;
		if (std::cin.fail()) throw(std::invalid_argument("Kerem csak szamot irjon be\n")); //ha rossz input
		break;

	case 3:
		while (elso != utolso) { //vegigfut az inputon es kiir mindent
			elso.getAkt()->kiir(std::cout);
			++elso;
		}
		break;

	case 9:
		return;

	default: return; //formasag, nem jut el ide a kod
	}


}

/////////////////////////////////////////////////////////////////////////////   MODOSIT
//megkerdezi melyik filmet modositanank es meghivja a modosit tagfuggvenyet
void Filmtar::Modosit() {
	iterator elso = begin();
	iterator utolso = end();

	std::cout << "Melyik filmet szeretned modositani?  [Kilepes (9)]\n" << std::endl;
	String string;
	std::cin >> string;

	if (string == '9') return; //kilepes

	while (elso != utolso && !(elso.getAkt()->getCim() == string)) {//megkeresi a filmet
		++elso;
	}

	if (elso == utolso) { //ha nincs ilyen
		std::cout << "Nincs ilyen cimu film eltarolva" << std::endl;
		return;
	}
	elso.getAkt()->modosit();
}


///////////////////////////////////////////////////////////////////////////////////    TOROL

//Egy adott filmet torol, Ha nincs megadva marameter akkor az alapertelmezett "" lesz, ezzel azonositva, hogy a felhasznalotol varjuk az inputot
void Filmtar::Torol(String cim) {
	if (cim == "") { // ha nincs megadva cim
		std::cout << "Kerem adja meg a torolni kivant film cimet  [Kilepes (9)]\n" << std::endl;
		std::cin >> cim;
	}

	if (cim == '9') return;

	Film* temp = NULL;
	Film* elso = this->elso;


	if (elso != NULL && elso->getCim() == cim) { //Ha az elsot toroljuk, de a lista nem ures
		this->elso = elso->getKov();
		delete elso;
		return;
		std::cout << "Film torolve" << std::endl;
	}


	while (elso != NULL && !(elso->getCim() == cim)) { //megkeressuk a filmet, amit torolnenk
		temp = elso;
		elso = elso->getKov();
	}


	if (elso != NULL) { //ha van ilyen toroljuk
		temp->setKov(elso->getKov());
		delete elso;
		std::cout << "Film torolve" << std::endl;
	}
	std::cout << "Nincs ilyen film eltarova" << std::endl;//ha nincs ilyen film

}

////////////////////////////////////////////////////////////////////// MENTES	
//Menti a listat a staticban megadott fajlba
void Filmtar::Ment() {
	iterator elso = begin();
	iterator utolso = end();

	std::ofstream fajl(getFajlnev());//megnyit

	while (elso != utolso) { //vegigmegy, es egyesevel meghivja a mentes fvt
		elso.getAkt()->mentes(fajl);
		++elso;
	}

	fajl.close();//bezar
	std::cout << "Filmek elmentve\n" << std::endl;
}

////////////////////////////////////////////////////////////////////// FELVESZ (user input alapjan)
	//Felvesz fv: felhasznalo kivalaszthatja milyen tipusus filmet akar hozzaadni, a fv meghivja a megfelelo fvt
void Filmtar::Felvesz() {
	int sel;
	std::cout << "Mit szeretne hozzaadni?\n\nDokumentumfilm (1)\nCsaladi film (2)\n [Kilepes (9)]\n" << std::endl;
	try {
		std::cin >> sel;
		if (std::cin.fail()) throw(std::invalid_argument("Kerem csak szamot irjon be\n")); //hibas input kiszurese

		switch (sel) {
		case 1:
			Hozzaad(DokFelvesz()); //ha dokmentumot
			break;
		case 2:
			Hozzaad(CsalFelvesz()); //ha csaladi fillmet
			break;
		case 9:
			return;

		}
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


//////////////////////////////////////////////////////////////////////////////
///iterator:
Filmtar::iterator& Filmtar::iterator::operator++() {
	setAkt(getAkt()->getKov());
	return *this;

};

Filmtar::iterator Filmtar::iterator::operator++(int) {
	iterator temp = *this;
	++(*this);
	return temp;
};
