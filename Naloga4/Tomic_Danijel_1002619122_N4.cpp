
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

// razred IskalnoDrevo
class IskalnoDrevo
{
    // razred Vozlisce
    class Vozlisce
    {
        double podatek;
        Vozlisce* levo;
        Vozlisce* desno;

    public:
        Vozlisce(double podatek)
        {
            this->podatek = podatek;
            this->levo = NULL;
            this->desno = NULL;
        }

        void vstavi(double podatek)
        {
            if (podatek < this->podatek)
            {
                if (levo == NULL)
                    levo = new Vozlisce(podatek);
                else
                    levo->vstavi(podatek);
            }
            else
            {
                if (desno == NULL)
                    desno = new Vozlisce(podatek);
                else
                    desno->vstavi(podatek);
            }
        }

        int stevilo_vozlisc()
        {
            int count = 1;
            if (levo != NULL)
                count += levo->stevilo_vozlisc();

            if (desno != NULL)
                count += desno->stevilo_vozlisc();

            return count;
        }

        int visina_drevesa(int globina)
        {
            int l = 0, d = 0;

            if (levo == NULL && desno == NULL)
                return 1;

            if (levo != NULL)
                l = levo->visina_drevesa(globina);

            if (desno != NULL)
                d = levo->visina_drevesa(globina);

            return (l > d) ? l + 1 : d + 1;
        }

        double najvecji()
        {
            auto* d = this;
            while (d->desno != NULL)
            {
                d = d->desno;
            }
            return d->podatek;
        }

        double najmanjsi()
        {
            auto* l = this;
            while (l->levo != NULL)
            {
                l = l->levo;
            }
            return l->podatek;
        }

        void premi_pregled(queue<double>& vrsta)
        {
            if (levo == NULL && desno == NULL)
            {
                vrsta.push(podatek);
                return;
            }
            vrsta.push(podatek);
            if (levo != NULL)
            {
                levo->premi_pregled(vrsta);
            }
            if (desno != NULL)
            {
                desno->premi_pregled(vrsta);
            }
        }

        void vmesni_pregled(queue<double>& vrsta)
        {
            if (levo == NULL && desno == NULL)
            {
                vrsta.push(podatek);
                return;
            }

            if (levo != NULL)
            {
                levo->vmesni_pregled(vrsta);
            }

            vrsta.push(podatek);

            if (desno != NULL)
            {
                desno->vmesni_pregled(vrsta);
            }
        }

        void obratni_pregled(queue<double>& vrsta)
        {
            if (levo == NULL && desno == NULL)
            {
                vrsta.push(podatek);
                return;
            }
            if (levo != NULL)
            {
                levo->obratni_pregled(vrsta);
            }
            if (desno != NULL)
            {
                desno->obratni_pregled(vrsta);
            }
            vrsta.push(podatek);
        }

        bool iskanje(double stevilo)
        {
            if (stevilo == podatek)
                return true;

            if (levo != NULL && levo->iskanje(stevilo))
                return true;

            if (desno != NULL && desno->iskanje(stevilo))
                return true;

            return false;
        }

        double vsota()
        {
            double sum = podatek;

            if (levo != NULL)
                sum += levo->vsota();

            if (desno != NULL)
                sum += desno->vsota();

            return sum;
        }
    };

    // nadaljevanje razreda IskalnoDrevo
    Vozlisce* koren;

public:
    IskalnoDrevo()
    {
        koren = NULL;
    }

    void vstavi(double podatek)
    {
        if (koren == NULL)
            koren = new Vozlisce(podatek);
        else
            koren->vstavi(podatek);
    }

    int stevilo_vozlisc() const
    {
        if (koren == NULL)
            return 0;
        else
            return koren->stevilo_vozlisc();
    }

    int visina_drevesa() const
    {
        if (koren == NULL)
            return 0;
        else
            return koren->visina_drevesa(1);
    }
    double najvecji() const
    {
        if (koren == NULL)
            return numeric_limits<double>::quiet_NaN();
        return koren->najvecji();
    }

    double najmanjsi() const
    {
        if (koren == NULL)
            return numeric_limits<double>::quiet_NaN();
        return koren->najmanjsi();
    }

    queue<double> premi_pregled() const
    {
        queue<double> prefiks;
        if (koren != NULL)
            koren->premi_pregled(prefiks);
        return prefiks;
    }

    queue<double> vmesni_pregled() const
    {
        queue<double> infiks;
        if (koren != NULL)
            koren->vmesni_pregled(infiks);
        return infiks;
    }

    queue<double> obratni_pregled() const
    {
        queue<double> postfiks;
        if (koren != NULL)
            koren->obratni_pregled(postfiks);
        return postfiks;
    }

    bool iskanje(double stevilo) const
    {
        if (koren != NULL)
            return koren->iskanje(stevilo);

        return false;
    }

    double vsota() const
    {
        if (koren != NULL)
            return koren->vsota();

        return numeric_limits<double>::quiet_NaN();
    }
};

int main(int argn, char** args)
{
    double zaporedje[] = {1.1, -9.9, 16.16, -25.25, 49.49, -1.1, 4.4, 36.36, -16.16, -4.4, 0.0, 9.9, 25.25};
    int dolzina = sizeof(zaporedje) / sizeof(double);

    // ustvarimo nov objekt
    IskalnoDrevo id;

    // napolnimo drevo
    for (int i = 0; i < dolzina; i++)
        id.vstavi((zaporedje[i]));

    // pričakovan izhod
    double pricakovan_izhod = 49.49;

    // dobljen izhod
    double dobljen_izhod = id.najvecji();

    // preverimo, če dobimo pravilen izhod
    if (pricakovan_izhod == dobljen_izhod)
        cout << "OK" << endl;
    else
        cout << "Napaka! Pričakovan izhod: " << pricakovan_izhod << ", dobljen izhod: " << dobljen_izhod << endl;

    return 0;
}
