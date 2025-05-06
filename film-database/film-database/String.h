#ifndef STRING_H
#define	STRING_H

#include <iostream>
/**
 * A String oszt�ly.
 * A 'data'-ban vannak a karakterek (a lez�r� null�val egy�tt), 'len' a hossza.
 * A hosszba nem sz�m�t bele a lez�r� nulla.
 *
 * Kor�bban a len adattag unsigned int t�pus� volt. Most helyette a size_t t�pust haszn�ljuk.
 * Ezzel a t�pussal t�r vissza a sizeof operator is, k�s�bb t�bb helyen ezt haszn�ljuk
 * m�rett�pusk�nt.

 */
class String {
    char* data;        ///< pointer az adatra
    int len;         ///< hossz lez�r� nulla n�lk�l
public:
    /// Ki�runk egy Stringet (debug c�lokra)
    /// Ezt a tagf�ggv�nyt elk�sz�tett�k, hogy haszn�lja a hib�k felder�t�s�hez.
    /// Ig�ny szerint m�dos�that�
    /// @param txt - null�val lez�rt sz�vegre mutat� pointer.
    ///              Ezt a sz�veget �rjuk ki a debug inform�ci� el�tt.
    void printDbg(const char* txt = "") const {
        std::cout << txt << "[" << len << "], "
            << (data ? data : "(NULL)") << '|' << std::endl;
    }

    /// Az els� k�t feladatot el�re megoldottuk, de lehet, hogy nem j�l.
    /// Az �res sztring reprezent�ci�ja nem szerencs�s, mert �gy NULL pointerr�
    /// konvert�l a c_str(), ami k�l�n kezel�st ig�nyel a k�s�bbiekben.
    /// Ezt a teszt program sem fogadja el.
    /// Gondolja v�gig, �s v�ltoztassa meg!
    /// K�t lehet�s�g van:
    ///     a) nem NULL pointert t�rol, hanem t�nylegesen �res sztringet.
    ///     b) NULL-t t�rol, de a c_str() �res sztringet ad vissza helyette
    ///        Ebben az esetben �gyelnie kell a m�sol�sokra (m�sol� kostruktor op=) is,
    ///        nehogy NULL pointert kapjon az strcpy!
    /// B�rmelyik megold�s j�, mert ez az oszt�ly bel�gye.


        /// Param�ter n�lk�li konstruktor:
    String() : len(0) {
        data = new char[1];
        *data = '\0';
    }

    String(const String&);

    //destruktor
    ~String() {
        delete[] data;
    }


    /// Sztring hossz�t adja vissza.
    /// @return sztring t�nyleges hossza (lez�r� nulla n�lk�l).
    int size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a t�rolt, vagy azzal azonos tartalm� null�val lez�rt sztring-re.
    const char* c_str() const { return data; }

    /// Itt folytassa a tagf�ggv�nyek deklar�ci�it a feladatoknak megfelel�en.
    /// ...
    String(const char);

    String(const char*);

    String& operator=(const String&);

    String operator+(const char) const;

    String operator+(const String&) const;

    String operator+(String&) const;

    char& operator[](const int) const;
    char& operator[](const int);






}; /// Itt az oszt�ly deklar�ci�j�nak v�ge

/// Ide ker�lnek a glob�lis oper�torok deklar�ci�i.
/// ...

String operator+(const char, const String);

std::ostream& operator<<(std::ostream&, const String&);

// Beolvas az istreamrol, elso param: istream (bemenet), masodik param: string amibe olvas 
std::istream& operator>>(std::istream& is, String& s0);

std::ifstream& operator>>(std::ifstream& ifs, String& s0);

bool operator==(const String& s0, const String& s1);

#endif // !STRING_H
