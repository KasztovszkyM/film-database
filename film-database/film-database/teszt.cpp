#include "Filmtar.h"
#include "Film.h"
#include "Csaladi.h"
#include "Dokumentum.h"
#include<iostream>
#include<stdexcept>

#include "memtrace.h"



int main(void) {

    Filmtar filmtar;



    int sel;

    printf("FILMTAROLO\n\n");
    do {
        printf("-------------------------\n"
            "[1] Film hozzadasa \n"
            "[2] Film modositasa\n"
            "[3] Film torlese\n"
            "[4] Filmek listazasa\n"
            "[5] Filmek mentese\n"
            "\n"
            "[9] Kilepes\n"
            "-------------------------\n"
        );

        try {
            std::cin >> sel;
            if (std::cin.fail()) throw(std::invalid_argument("Kerem csak szamot irjon be\n"));



            switch (sel) {
            case 1: //uj film

                filmtar.Felvesz();

                break;

            case 2: //modositas

                filmtar.Modosit();

                break;

            case 3: // torlese

                filmtar.Torol();

                break;

            case 4: //listazas

                filmtar.Kiir();

                break;

            case 5: //kereses

                filmtar.Ment();

                break;

            case 9:
                std::cout << "Kilepes...\n" << std::endl;
                break;

            default:
                std::cout << "Kerem megfelelo szamot valasszon!\n";
                break;
            }
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (sel != 9);


    return 0;
}