#ifndef STRING_H
#define	STRING_H

#include <iostream>
/**
 * A String osztály.
 * A 'data'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 *
 * Korábban a len adattag unsigned int típusú volt. Most helyette a size_t típust használjuk.
 * Ezzel a típussal tér vissza a sizeof operator is, késõbb több helyen ezt használjuk
 * mérettípusként.

 */
class String {
    char* data;        ///< pointer az adatra
    int len;         ///< hossz lezáró nulla nélkül
public:
    /// Kiírunk egy Stringet (debug célokra)
    /// Ezt a tagfüggvényt elkészítettük, hogy használja a hibák felderítéséhez.
    /// Igény szerint módosítható
    /// @param txt - nullával lezárt szövegre mutató pointer.
    ///              Ezt a szöveget írjuk ki a debug információ elõtt.
    void printDbg(const char* txt = "") const {
        std::cout << txt << "[" << len << "], "
            << (data ? data : "(NULL)") << '|' << std::endl;
    }

    /// Az elsõ két feladatot elõre megoldottuk, de lehet, hogy nem jól.
    /// Az üres sztring reprezentációja nem szerencsés, mert így NULL pointerré
    /// konvertál a c_str(), ami külön kezelést igényel a késõbbiekben.
    /// Ezt a teszt program sem fogadja el.
    /// Gondolja végig, és változtassa meg!
    /// Két lehetõség van:
    ///     a) nem NULL pointert tárol, hanem ténylegesen üres sztringet.
    ///     b) NULL-t tárol, de a c_str() üres sztringet ad vissza helyette
    ///        Ebben az esetben ügyelnie kell a másolásokra (másoló kostruktor op=) is,
    ///        nehogy NULL pointert kapjon az strcpy!
    /// Bármelyik megoldás jó, mert ez az osztály belügye.


        /// Paraméter nélküli konstruktor:
    String() : len(0) {
        data = new char[1];
        *data = '\0';
    }

    String(const String&);

    //destruktor
    ~String() {
        delete[] data;
    }


    /// Sztring hosszát adja vissza.
    /// @return sztring tényleges hossza (lezáró nulla nélkül).
    int size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re.
    const char* c_str() const { return data; }

    /// Itt folytassa a tagfüggvények deklarációit a feladatoknak megfelelõen.
    /// ...
    String(const char);

    String(const char*);

    String& operator=(const String&);

    String operator+(const char) const;

    String operator+(const String&) const;

    String operator+(String&) const;

    char& operator[](const int) const;
    char& operator[](const int);






}; /// Itt az osztály deklarációjának vége

/// Ide kerülnek a globális operátorok deklarációi.
/// ...

String operator+(const char, const String);

std::ostream& operator<<(std::ostream&, const String&);

// Beolvas az istreamrol, elso param: istream (bemenet), masodik param: string amibe olvas 
std::istream& operator>>(std::istream& is, String& s0);

std::ifstream& operator>>(std::ifstream& ifs, String& s0);

bool operator==(const String& s0, const String& s1);

#endif // !STRING_H
