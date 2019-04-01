/**
Descriere : -> Acest program este un AFN(automat finit nedeterminist) si verifica daca un cuvant este valid sau nu.
            Vom citi cuvantul de la tastatura. In fisierul "AFN.txt" vom gasi informatii ce ne ajuta sa construim automatul(pe foaie).
            In acest fisier vom gasi in urmatoarea ordine :
            Q - care reprezinta numarul total de stari;
            F - nr de stari finale urmand apoi sa fie scrise acestea ( 0 <= qi <= N-1);
            T - nr de transpozitii urmand apoi sa fie scrise fiecare pe cate un rand;
            Starile in general sunt notate cu q0, q1, q2 ... q0 fiind stare de start.
            Pe aceeasi linie cu fiecare transpozitie vom gasi si numarul de litere care se pot elimina prin acea transpozitie(nr_litere) fiind urmat de litera corespunzatoare (litera_alfabet).
            In continuare am creat o matrice tridimensionala cu Q linii (starile de plecare) si Q coloane (starile in care intra).
            La intersectie am o alta dimensiune (adancime), in care voi avea fiecare litera prin care se poate face tranzitia sau numai 0 in caz contrar.

            -> Functia de testare(testeaza_cuvant) e una recursiva si ia ca parametri starea curenta(stare_c), numarul total de stari/Q (nr_stari), matricea tridimensionala (matrice_[10][10][20]), vectorul cu stari finale (*finale) si cuvantul in sine(*cuvant).
            La fiecare apel voi merge in urmatoarea stare posibila si voi verifica urmatoarea litera din cuvant.
            Aceasta trece prin fiecare transozitie posibila si verifica la final daca starea in care a ajuns este una finala.
            Voi cauta in a treia dimeniune daca pot continua in urmatoarea stare, folosind strchr.
            Folosesc o variabila statica pentru a nota daca intr-una dintre recursiile cuvantului a fost validata.
 */


#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

ifstream f("AFN.txt");

int testeazaCuvantul(int stare_c, int nr_stari, char matrice_[10][10][20], int *finale, char *cuvant)
{
    static int k = 0;

    ///Daca ajunge la finalul cuvantului si suntem intr-o stare finala.
    if(strlen(cuvant) == 0 && finale[stare_c] == 1) {
        k = 1;
    } else {
        ///Cautam pentru stare_c o alta in care se se duca pe baza literei la care ne aflam.
        for(int i = 0; i < nr_stari; i++) {
            if(strlen(cuvant) != 0 && strchr(matrice_[stare_c][i], cuvant[0]))
                testeazaCuvantul(i, nr_stari, matrice_, finale, cuvant + 1);
            }
    }
        ///Daca s-a terminat cuvantul si strarea in care ai ajuns nu este finala atunci nu este acceptat.
        ///Daca s-a terminat cuvantul si starea ta este finala atunci cuvantul este acceptat.
        ///Daca in cursul acestor pasi, ajungi intr-un nod din care nu mai ai unde sa te duci atunci trebuie sa te intorci.

        ///Ca sa vedem daca ne putem duce in alta stare, cautam daca litera cuvantului se gaseste in cea de-a treia dimensiune.
        ///Daca nu am ajuns la finalul cuvantului si ne putem duce in alta stare, ne ducem in starea respectiva si "taiem" litera curenta a cuvantului.
        ///Daca se termina for-ul fara a se face vreo operatie, inseamna ca am terminat cuvantul, dar nu intr-o stare finala sau ne-am blocat intr-o stare.

    return k;
}

int main()
{
    int numarStari, numarFinale, numarTranzitii;
    ///Un vector in care 1 pentru stari finale si 0 pentru restul.
    int finale[10] = {0};

    char matriceAFN[10][10][20] = {0};

    f>>numarStari>>numarFinale;

    /// Citesc starile finale si setez pozitia cu 1.
    for(int i = 0; i < numarFinale; i++) {
        int stare;
        f>>stare;
        finale[stare] = 1;
    }

    f>>numarTranzitii;

    /// Tranzitiile sunt de tipul stare din care pleaca, in care pleaca si prin ce litera.
    for (int i = 0; i < numarTranzitii; i++) {
        int din_stare, in_stare, nr_litere;
        f>>din_stare>>in_stare>>nr_litere;

        for (int j = 0; j < nr_litere; j++) {
            char litera_alfabet;
            f>>litera_alfabet;
            matriceAFN[din_stare][in_stare][j] = litera_alfabet;
        }
    }

    char *cuvant = NULL;
    cuvant = new char [100];
    cout<<"BAGA CUVANTUL AICI : ";

    cin.get(cuvant, 100);
    cin.get();

    /// Testez daca cuvantul citit de la tastatura este vid.
    if(strlen(cuvant) == 0) {
        /// Verific daca pozitia de start este finala.
        if(finale[0] == 1) {
            cout<<"E VID SI E OK!";
        } else {
            cout<<"E SE VID SI NICI NU E OK!";
        }
        return 0;
    }

    if(testeazaCuvantul(0, numarStari, matriceAFN, finale, cuvant)) {
        cout<<"ESTE OK!";
    } else {
        cout<<"NU ESTE OK!";
    }

    delete [] cuvant;

    return 0;
}
