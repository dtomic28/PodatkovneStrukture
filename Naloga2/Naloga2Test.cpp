//
// Created by danijel on 4/13/2024.
//
//
// Created by Danijel Tomić on 28. 03. 24.
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <iostream>
#include "Naloga2.h"
#include <list>
#include <ctime>

using namespace std;

TEST_CASE("Vstavi()")
{
    list<Student> studentList = {{"Janez", "Novak", "12345"},
                                 {"Maja", "Kranjc", "23456"},
                                 {"Marko", "Polo", "34567"},
                                 {"Ana", "Berić", "45678"},
                                 {"Ivan", "Horvat", "56789"}};

    SECTION("Index < 0")
    {
        list<Student> studentListCopy = studentList;
        vstavi(studentListCopy, -1, {"Danijel", "Tomic", "10028"});

        REQUIRE(studentListCopy == studentList);
    }

    SECTION("Index >= seznam.size()")
    {
        list<Student> studentListCopy = studentList;
        vstavi(studentListCopy, studentListCopy.size(), {"Danijel", "Tomic", "10028"});
        REQUIRE(studentListCopy == studentList);

        vstavi(studentListCopy, studentListCopy.size() + 1, {"Danijel", "Tomic", "10028"});
        REQUIRE(studentListCopy == studentList);
    }

    SECTION("seznam.Empty()")
    {
        list<Student> studentsEmpty;
        vstavi(studentsEmpty, 3, {"Danijel", "Tomic", "10028"});
        REQUIRE(studentsEmpty.empty());
    }

    SECTION("Should work")
    {
        auto student = Student({"Danijel", "Tomic", "10028"});
        vstavi(studentList, 3, student);
        auto it = studentList.begin();
        std::advance(it, 3);
        izpisi_seznam(studentList);
        REQUIRE(*it == student);
    }
}

TEST_CASE("Vrini()")
{
    list<Student> studentList = {{"Janez", "Novak", "12345"},
                                 {"Maja", "Kranjc", "23456"},
                                 {"Marko", "Polo", "34567"},
                                 {"Ana", "Berić", "45678"},
                                 {"Ivan", "Horvat", "56789"}};

    SECTION("Index < 0")
    {
        list<Student> studentListCopy = studentList;
        vrini(studentListCopy, -1, {"Danijel", "Tomic", "10028"});

        REQUIRE(studentListCopy == studentList);
    }

    SECTION("Index >= seznam.size()")
    {
        list<Student> studentListCopy = studentList;
        vrini(studentListCopy, studentListCopy.size(), {"Danijel", "Tomic", "10028"});
        REQUIRE(studentListCopy.back() == Student({"Danijel", "Tomic", "10028"}));
    }

    SECTION("seznam.Empty()")
    {
        list<Student> studentsEmpty;
        vrini(studentsEmpty, 3, {"Danijel", "Tomic", "10028"});
        REQUIRE(!studentsEmpty.empty());
        REQUIRE(*studentsEmpty.begin() == Student({"Danijel", "Tomic", "10028"}));
    }

    SECTION("Should work")
    {
        size_t orgSize = studentList.size();
        auto student = Student({"Danijel", "Tomic", "10028"});
        vrini(studentList, 3, student);
        auto it = studentList.begin();
        std::advance(it, 3);
        izpisi_seznam(studentList);
        REQUIRE(*it == student);
        REQUIRE((studentList.size() - orgSize) == 1);
    }
}

TEST_CASE("Vrni()")
{
    list<Student> studentList = {{"Janez", "Novak", "12345"},
                                 {"Maja", "Kranjc", "23456"},
                                 {"Marko", "Polo", "34567"},
                                 {"Ana", "Berić", "45678"},
                                 {"Ivan", "Horvat", "56789"}};

    SECTION("Index < 0")
    {
        REQUIRE(vrni(studentList, -1) == Student());
    }

    SECTION("Index >= seznam.size()")
    {
        REQUIRE(vrni(studentList, studentList.size()) == Student());
        REQUIRE(vrni(studentList, studentList.size() + 1) == Student());
    }

    SECTION("seznam.Empty()")
    {
        list<Student> studentsEmpty;
        REQUIRE(vrni(studentsEmpty, 1) == Student());
    }

    SECTION("Should work")
    {
        REQUIRE(vrni(studentList, 0) == Student({"Janez", "Novak", "12345"}));
    }
}

TEST_CASE("Odstrani()")
{
    list<Student> studentList = {{"Janez", "Novak", "12345"},
                                 {"Maja", "Kranjc", "23456"},
                                 {"Marko", "Polo", "34567"},
                                 {"Ana", "Berić", "45678"},
                                 {"Ivan", "Horvat", "56789"}};

    SECTION("Index < 0")
    {
        REQUIRE(odstrani(studentList, -1) == Student());
    }

    SECTION("Index >= seznam.size()")
    {
        REQUIRE(odstrani(studentList, studentList.size()) == Student());
        REQUIRE(odstrani(studentList, studentList.size() + 1) == Student());
    }

    SECTION("seznam.Empty()")
    {
        list<Student> studentsEmpty;
        REQUIRE(odstrani(studentsEmpty, 1) == Student());
    }

    SECTION("Should work")
    {
        size_t orgSize = studentList.size();
        REQUIRE(odstrani(studentList, 0) == Student({"Janez", "Novak", "12345"}));
        INFO(orgSize);
        INFO(studentList.size());
        REQUIRE((orgSize - studentList.size()) == 1);
    }
}
