//
// Created by danijel on 4/13/2024.
//

#ifndef PODATKOVNESTRUKTURE_NALOGA2_H
#include <string>
#include <list>
struct Student
{
    std::string Ime;
    std::string Priimek;
    std::string IDUM;

    bool operator==(const Student& other) const
    {
        return (Ime == other.Ime && Priimek == other.Priimek && IDUM == other.IDUM);
    }
};

// prototipi
void izpisi_seznam(std::list<Student>);
void izpisi_studenta(Student);
void vstavi(std::list<Student>&, int, Student);
Student vrni(std::list<Student>, int);
void vrini(std::list<Student>&, int, Student);
Student odstrani(std::list<Student>&, int);

#define PODATKOVNESTRUKTURE_NALOGA2_H

#endif  // PODATKOVNESTRUKTURE_NALOGA2_H
