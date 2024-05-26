// privzete vkljucitve
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <ctime>

// uporabljeni imenski prostori
using namespace std;

// pomozni metodi
template <typename T>
int izbrisiVrsto(queue<T>& vrsta)
{
    int st_odstranjenih = 0;
    while (!vrsta.empty())
    {
        vrsta.pop();
        st_odstranjenih++;
    }
    return st_odstranjenih;
}

template <typename T>
int izbrisiSklad(stack<T>& sklad)
{
    int st_odstranjenih = 0;
    while (!sklad.empty())
    {
        sklad.pop();
        st_odstranjenih++;
    }
    return st_odstranjenih;
}

// uporabnisko definirani podatkovni tipi
class Potnik
{
private:
    string ime;
    string priimek;
    int starost;
    string emso;  // se uporabi kot ID

public:
    // konstruktor
    Potnik(const string& ime, const string& priimek, int starost, const string& emso)
        : ime(ime)
        , priimek(priimek)
        , starost(starost)
        , emso(emso)
    {
    }
    ~Potnik()
    {
    }

    // get/set metode
    string getIme() const
    {
        return ime;
    }
    void setIme(const string& ime)
    {
        this->ime = ime;
    }
    string getPriimek() const
    {
        return priimek;
    }
    void setPriimek(const string& priimek)
    {
        this->priimek = priimek;
    }
    int getStarost() const
    {
        return starost;
    }
    void setStarost(int starost)
    {
        this->starost = starost;
    }
    string getEmso() const
    {
        return emso;
    }
    void setEmso(const string& emso)
    {
        this->emso = emso;
    }
};

enum PotniskiRazred
{
    EKONOMSKI,
    POSLOVNI
};

class Kovcek
{
private:
    int idKovcek;

public:
    // konstruktor
    Kovcek(int id)
        : idKovcek(id)
    {
    }
    ~Kovcek()
    {
    }

    // get/set metoda
    int getIDKovcek() const
    {
        return idKovcek;
    }
    void setIDKovcek(int id)
    {
        this->idKovcek = id;
    }
};

class KartaZaVkrcavanje
{
private:
    Potnik potnik;
    PotniskiRazred razredSedeza;
    Kovcek kovcek;

public:
    // konstruktor
    KartaZaVkrcavanje(const Potnik& potnik, const PotniskiRazred& pr, const Kovcek& kovcek)
        : potnik(potnik)
        , razredSedeza(pr)
        , kovcek(kovcek)
    {
    }
    ~KartaZaVkrcavanje()
    {
    }

    // get/set metode
    Potnik getPotnik() const
    {
        return potnik;
    }
    void setPotnik(const Potnik& potnik)
    {
        this->potnik = potnik;
    }
    PotniskiRazred getRazredSedeza() const
    {
        return razredSedeza;
    }
    void setRazredSedeza(PotniskiRazred razredSedeza)
    {
        this->razredSedeza = razredSedeza;
    }
    Kovcek getKovcek() const
    {
        return kovcek;
    }
    void setKovcek(const Kovcek& kovcek)
    {
        this->kovcek = kovcek;
    }
};

class Letalo
{
private:
    int id;  // identifikacijska stevilka letala
public:
    stack<stack<Kovcek> > prtljaznik;  // sklad skladov kovckov na letalu = prtljaga vseh potnikov
private:
    unsigned int maxSteviloKovckovNaKupu;  // maksimalno stevilo kovckov na enem kupu v prtljazniku

public:
    // konstruktor
    Letalo(int id, unsigned int maxSteviloKovckovNaKupu)
        : id(id)
        , maxSteviloKovckovNaKupu(maxSteviloKovckovNaKupu)
    {
    }
    ~Letalo()
    {
    }

    // get/set metode
    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    unsigned int getMaxSteviloKovckovNaKupu() const
    {
        return maxSteviloKovckovNaKupu;
    }
    void setMaxSteviloKovckovNaKupu(unsigned int maxSteviloKovckovNaKupu)
    {
        this->maxSteviloKovckovNaKupu = maxSteviloKovckovNaKupu;
    }

    // ostale metode
    void naloziKovcke(queue<Kovcek>& kovcki)
    {
        stack<Kovcek> paleta;
        while (!kovcki.empty())
        {
            paleta.push(kovcki.front());
            kovcki.pop();
            if (paleta.size() == maxSteviloKovckovNaKupu)
            {
                prtljaznik.push(paleta);
                paleta = stack<Kovcek>();
            }
        }
        if (!paleta.empty())
        {
            prtljaznik.push(paleta);
        }
    }

    queue<Kovcek> razloziKovcke()
    {
        queue<Kovcek> result;
        while (!prtljaznik.empty())
        {
            auto paleta = prtljaznik.top();
            prtljaznik.pop();
            while (!paleta.empty())
            {
                result.push(paleta.top());
                paleta.pop();
            }
        }
        return result;
    }
};

class LetalskaDruzba
{
public:
    queue<KartaZaVkrcavanje> cakajociNaVkrcanje;  // vrsta prijavljenih potnikov, ki cakajo na vkrcanje
    queue<Kovcek> razlozeniKovcki;                // vrsta kovckov

    // konstruktor
    LetalskaDruzba()
    {
    }
    ~LetalskaDruzba()
    {
    }

    // ostale metode
    void razdeli(queue<KartaZaVkrcavanje>& potniki, queue<KartaZaVkrcavanje>& sedeci_poslovni, queue<KartaZaVkrcavanje>& sedeci_ekonomski)
    {
        while (!potniki.empty())
        {
            KartaZaVkrcavanje temp = potniki.front();
            potniki.pop();
            switch (temp.getRazredSedeza())
            {
                case EKONOMSKI:
                    sedeci_ekonomski.push(temp);
                    break;
                case POSLOVNI:
                    sedeci_poslovni.push(temp);
                    break;
            }
        }
    }

    queue<KartaZaVkrcavanje> zdruzi(queue<KartaZaVkrcavanje>& sedeci_poslovni, queue<KartaZaVkrcavanje>& sedeci_ekonomski)
    {
        queue<KartaZaVkrcavanje> q;
        while (!sedeci_ekonomski.empty())
        {
            q.push(sedeci_ekonomski.front());
            sedeci_ekonomski.pop();
        }
        while (!sedeci_poslovni.empty())
        {
            q.push(sedeci_poslovni.front());
            sedeci_poslovni.pop();
        }
        return q;
    }

    queue<KartaZaVkrcavanje> uredi(queue<KartaZaVkrcavanje>& cakalnaVrsta)
    {
        queue<KartaZaVkrcavanje> sedeci_poslovni;
        queue<KartaZaVkrcavanje> sedeci_ekonomski;

        razdeli(cakalnaVrsta, sedeci_poslovni, sedeci_ekonomski);

        return zdruzi(sedeci_poslovni, sedeci_ekonomski);
    }

    void opravilaPriLetu(queue<KartaZaVkrcavanje> prijavljeniPotniki, queue<Kovcek> prijavljeniKovcki, Letalo lt)
    {
        if (cakajociNaVkrcanje.size() != 0)
            izbrisiVrsto(cakajociNaVkrcanje);
        if (razlozeniKovcki.size() != 0)
            izbrisiVrsto(razlozeniKovcki);

        cakajociNaVkrcanje = uredi(prijavljeniPotniki);

        lt.naloziKovcke(prijavljeniKovcki);

        // letimo na cilj

        razlozeniKovcki = lt.razloziKovcke();
    }
};

// proste metode v imenskem prostoru
// prostor za lastno implementirane metode

bool test_zdruzi_izkljucno_v_poslovnem_razredu()
{
    queue<KartaZaVkrcavanje> poslovni;
    int kovcek_id = 0;
    Potnik pt1("Janez", "Kranjski", 25, "1111111111111");
    PotniskiRazred pr1 = POSLOVNI;
    Kovcek k1(kovcek_id++);
    KartaZaVkrcavanje kzv1(pt1, pr1, k1);
    poslovni.push(kzv1);

    Potnik pt2("Janez", "Novak", 17, "1111111111112");
    PotniskiRazred pr2 = POSLOVNI;
    Kovcek k2(kovcek_id++);
    KartaZaVkrcavanje kzv2(pt2, pr2, k2);
    poslovni.push(kzv2);

    Potnik pt3("Marija", "Testna", 18, "1111111111113");
    PotniskiRazred pr3 = POSLOVNI;
    Kovcek k3(kovcek_id++);
    KartaZaVkrcavanje kzv3(pt3, pr3, k3);
    poslovni.push(kzv3);

    Potnik pt4("Marija", "Fran", 45, "1111111111114");
    PotniskiRazred pr4 = POSLOVNI;
    Kovcek k4(kovcek_id++);
    KartaZaVkrcavanje kzv4(pt4, pr4, k4);
    poslovni.push(kzv4);

    queue<KartaZaVkrcavanje> ekonomski;
    queue<KartaZaVkrcavanje> pricakovanoZdruzeni = poslovni;

    LetalskaDruzba ld;
    queue<KartaZaVkrcavanje> dejanskoZdruzeni = ld.zdruzi(poslovni, ekonomski);

    if (pricakovanoZdruzeni.size() != dejanskoZdruzeni.size())
    {
        cout << "Metoda zdruzi() ni napolnila izhodne vrste zdruzenih potnikov s pricakovanim stevilom potnikov ("
             << (int) pricakovanoZdruzeni.size() << "), pac pa jo je napolnila s/z " << (int) dejanskoZdruzeni.size() << " potniki."
             << endl;
        return false;
    }

    while (!pricakovanoZdruzeni.empty() && !dejanskoZdruzeni.empty())
    {
        KartaZaVkrcavanje dejanska = dejanskoZdruzeni.front();
        dejanskoZdruzeni.pop();

        KartaZaVkrcavanje pricakovana = pricakovanoZdruzeni.front();
        pricakovanoZdruzeni.pop();

        Potnik pricakovanP = pricakovana.getPotnik();
        Potnik dejanskiP = dejanska.getPotnik();

        PotniskiRazred pricakovanPR = pricakovana.getRazredSedeza();
        PotniskiRazred dejanskiPR = dejanska.getRazredSedeza();

        Kovcek pricakovanK = pricakovana.getKovcek();
        Kovcek dejanskiK = dejanska.getKovcek();

        if (pricakovanP.getEmso() != dejanskiP.getEmso() || pricakovanP.getStarost() != dejanskiP.getStarost() ||
            pricakovanP.getPriimek() != dejanskiP.getPriimek() || pricakovanP.getIme() != dejanskiP.getIme() ||
            pricakovanPR != dejanskiPR || pricakovanK.getIDKovcek() != dejanskiK.getIDKovcek())
        {
            cout << "Metoda zdruzi() ni napolnila izhodne vrste zdruzenih potnikov z enakimi potniki, kot so bili podani." << endl;
            return false;
        }
    }

    return true;
}

// glavna metoda - globalna
int main(int argn, char** args)
{
    // Primer testnega scenarija
    if (test_zdruzi_izkljucno_v_poslovnem_razredu())
        cout << "Metoda zdruzi() je uspesno prestala test." << endl;
    else
        cout << "Metoda zdruzi() ni uspesno prestala testa." << endl;

    return 0;
}