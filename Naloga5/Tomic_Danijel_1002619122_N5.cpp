

#include <iostream>
#include <string>
#include <map>
#include <assert.h> /* assert */

using namespace std;

struct Oseba
{
    string Ime;
    string Priimek;
    int IDUM;  // 9-mestna unikatna številka
};

// prototipi
void DobiPrvoCrko(Oseba, char&);
void DobiSlovarSCrko(map<char, map<int, Oseba>>, char, map<int, Oseba>&);
void VstaviOseboVSlovarOseb(map<int, Oseba>&, Oseba);
void posodobi_slovar_oseb_v_slovarju(map<char, map<int, Oseba>>&, char, map<int, Oseba>);
void napolni_slovar(Oseba[], int, map<char, map<int, Oseba>>&);

void DobiPrvoCrko(Oseba oseba, char& prva_crka)
{
    prva_crka = oseba.Priimek[0];
}

void DobiSlovarSCrko(map<char, map<int, Oseba>> slovar, char prva_crka, map<int, Oseba>& slovar_oseb)
{
    slovar_oseb = slovar[prva_crka];
}

void VstaviOseboVSlovarOseb(map<int, Oseba>& slovar_oseb, Oseba os)
{
    slovar_oseb.insert(pair<int, Oseba>(os.IDUM, os));
}

void PosodobiSlovarOsebVSlovarju(map<char, map<int, Oseba>>& slovar, char prva_crka, map<int, Oseba> slovar_oseb)
{
    slovar[prva_crka] = slovar_oseb;
}

void napolni_slovar(Oseba seznam[], int N, map<char, map<int, Oseba>>& slovar)
{
    for (int i = 0; i < N; i++)
    {
        // pridobimo prvo črko
        char prva_crka;
        DobiPrvoCrko(seznam[i], prva_crka);

        // pridobimo slovar oseb s prvo črko
        map<int, Oseba> slovar_oseb;
        DobiSlovarSCrko(slovar, prva_crka, slovar_oseb);

        // vstavimo osebo v slovar
        VstaviOseboVSlovarOseb(slovar_oseb, seznam[i]);

        // posodobi slovar
        PosodobiSlovarOsebVSlovarju(slovar, prva_crka, slovar_oseb);
    }
}

bool test1()
{
    // dodaj poljubno število oseb
    Oseba seznam[] = {Oseba{"Damijan", "Novak", 123456789}};

    int N = sizeof(seznam) / sizeof(Oseba);

    map<char, map<int, Oseba>> slovar;

    napolni_slovar(seznam, N, slovar);

    // dodaj poljubne teste
    if (slovar.size() != 1)
        return false;

    return true;
}

int main()
{
    assert(test1() == true);

    return 0;
}
