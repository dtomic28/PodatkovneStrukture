#include <iostream>
#include <string>
#include <list>

#ifdef Dev
#include "Naloga2.h"
#endif

using namespace std;

#ifndef Dev

struct Student
{
    string Ime;
    string Priimek;
    string IDUM;
};

// prototipi
void izpisi_seznam(list<Student>);
void izpisi_studenta(Student);
void vstavi(list<Student>&, int, Student);
Student vrni(list<Student>, int);
void vrini(list<Student>&, int, Student);
Student odstrani(list<Student>&, int);

#endif

void izpisi_seznam(list<Student> seznam)
{
    for (list<Student>::iterator it = seznam.begin(); it != seznam.end(); ++it)
    {
        Student st = *it;
        izpisi_studenta(st);
    }
}

void izpisi_studenta(Student st)
{
    cout << "Ime: " << st.Ime << endl << "Priimek: " << st.Priimek << endl << "IDUM: " << st.IDUM << endl << endl;
}

void vstavi(list<Student>& seznam, int indeks, Student podatek)
{
    if (indeks < 0 || indeks >= seznam.size() || seznam.empty())
    {
        return;
    }

    auto it = seznam.begin();
    std::advance(it, indeks);
    *it = podatek;
}

Student vrni(const list<Student> seznam, int indeks)
{
    if (indeks < 0 || indeks >= seznam.size() || seznam.empty())
    {
        return Student();
    }

    auto it = seznam.begin();
    std::advance(it, indeks);
    return *it;
}

void vrini(list<Student>& seznam, int indeks, Student podatek)
{
    if (indeks < 0)
    {
        return;
    }
    else if (seznam.empty())
    {
        seznam.push_front(podatek);
        return;
    }
    else if (indeks >= seznam.size())
    {
        seznam.push_back(podatek);
        return;
    }

    auto it = seznam.begin();
    std::advance(it, indeks);
    seznam.insert(it, podatek);
}

Student odstrani(list<Student>& seznam, int indeks)
{
    if (indeks < 0 || indeks >= seznam.size() || seznam.empty())
    {
        return Student();
    }
    auto it = seznam.begin();
    std::advance(it, indeks);
    Student result = *it;
    seznam.erase(it);
    return result;
}

#ifndef DTTESTING
int main()
{
    return 0;
}
#endif
