/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelõ
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetõknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
 // MSC ne adjon figyelmeztetõ üzenetet a C sztringkezelõ függvényeire
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringmûveletekhez
#include "String.h"
#include <fstream>

#include "memtrace.h"           // a standard headerek után kell lennie



/// Konstruktorok: egy char karakterbõl (createString)

/// 
String::String(const char c) : len(1) {
    data = new char[1 + 1];
    data[0] = c;
    data[1] = '\0';
}
/// egy nullával lezárt char sorozatból (createString)
String::String(const char* c) {
    data = new char[strlen(c) + 1];
    len = strlen(c);
    strcpy(data, c);
    data[strlen(c)] = '\0';
}
/// Másoló konstruktor: String-bõl készít (createString)
String::String(const String& s) {
    len = s.len;
    data = new char[len + 1];
    strcpy(data, s.data);
    data[len] = '\0';

}

/// Destruktor (disposeString) 

//-- headerben inline

/// operator=
String& String::operator=(const String& s) {
    if (this != &s) {
        delete[] this->data;
        this->len = s.len;
        this->data = new char[len + 1];
        strcpy(this->data, s.data);
        data[len] = '\0';
    }
    return *this;
}
/// [] operátorok: egy megadott indexû elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
char& String::operator[](const int idx) const {
    if (idx < 0 || idx >= len) throw "QRRHP7";
    return data[idx];
}

char& String::operator[](const int idx) {
    if (idx < 0 || idx >= len) throw "QRRHP7";
    return data[idx];
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)

//chart fuz egy consthoz
String String::operator+(const char c) const {
    String temps;
    delete[] temps.data;

    char* tempp = new char[len + 1 + 1];
    strcpy(tempp, data);
    tempp[len] = c;
    tempp[len + 1] = '\0';

    temps.data = tempp;
    temps.len = len + 1;

    return temps;
}



///                 String-hez String-et ad (addString)
//const stringet fuz egy consthoz
String String::operator+(const String& s) const {
    String temps;
    delete[] temps.data;

    char* tempp = new char[len + s.len + 1];
    strcpy(tempp, data);
    strcat(tempp, s.data);

    temps.data = tempp;

    temps.len = s.len + len;

    return temps;
}

//stringet fuz egy nem consthoz
String String::operator+(String& s) const {
    String temps;
    delete[] temps.data;

    char* tempp = new char[len + s.len + 1];
    strcpy(tempp, data);
    strcat(tempp, s.data);

    temps.data = tempp;

    temps.len = s.len + len;

    return temps;
}

//globalis, charhoz stringet fuz
String operator+(const char c, const String s) {

    char* tempp = new char[s.size() + 1 + 1];
    tempp[0] = c;
    strncpy(tempp + 1, s.c_str(), s.size() + 1);

    String temps(tempp);
    delete[] tempp;

    return temps;
}

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.c_str();
    return os;
}

/// >> operátor, ami beolvas az istream-rõl egy szót
std::istream& operator>>(std::istream& is, String& s0) {
    s0 = String();
    if (std::cin.rdbuf()->in_avail() != 0) std::cin.ignore();
    std::ios_base::fmtflags fl = is.flags();
    char ch;
    while (is.get(ch)) {

        if (ch == '\n')
            break;
        s0 = s0 + ch;
    }
    is.setf(fl);
    return is;
}

//beolvasas fajlbol
std::ifstream& operator>>(std::ifstream& ifs, String& s0) {


    char ch;
    s0 = String("");
    std::ios_base::fmtflags fl = ifs.flags();
    while ((ifs.read(&ch, 1)) && (ch != ';')) {
        s0 = s0 + ch;
    }
    ifs.setf(fl);
#if defined(__linux__)
    ifs.seekg(3, std::ios::cur);
#elif _WIN32
    ifs.seekg(2, std::ios::cur);
#endif
    return ifs;
}


bool operator==(const String& s0, const String& s1) {
    if (s0.size() != s1.size())
        return false;

    for (int i = 0; i < s0.size(); i++) {
        if (s0[i] != s1[i])
            return false;
    }


    return true;
};
