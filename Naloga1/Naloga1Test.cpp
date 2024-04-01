//
// Created by Danijel Tomić on 28. 03. 24.
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <iostream>
#include "Naloga1.h"
#include <array>
#include <ctime>

using namespace std;

TEST_CASE("Poisci()") {
    array<int, 6> arr = {10, 5 ,18, 5,3, 5};

    SECTION("Returns first occurance in array"){
        auto indexOf = find(arr.begin(), arr.end(),5);
        auto indexOfTest = poisci(5, &arr[0], arr.size());
        REQUIRE(indexOf-&arr[0] == indexOfTest);
    }

    SECTION("Doesent throw at n=0"){
        REQUIRE_NOTHROW(poisci(5, &arr[0], 0));
    }

    SECTION("Doesent alter input array"){
        array<int, 6> arrCpy;
        std::copy(arr.begin(), arr.end(), &arrCpy[0]);
        REQUIRE(arrCpy.size() == 6);
        poisci(5, &arr[0], arr.size());
        REQUIRE(arrCpy == arr);
    }

    SECTION("Works with 10,000,000 elements"){
        const int arraySize = 10000000;
        std::vector<int> numbers(arraySize);

        // Fill the array with numbers from 1 to arraySize
        for (int i = 0; i < arraySize; ++i) {
            numbers[i] = i + 1;
        }

        REQUIRE(poisci(999999, &numbers[0], numbers.size()) == 999998);
    }

    SECTION("Returns -1 on not found"){
        REQUIRE(poisci(123, &arr[0], arr.size()) == -1);
    }
}

TEST_CASE("poisciZBisekcijo functionality") {
    array<int, 6> arr = {3,5,5,5,10,18};
    reverse(arr.begin(), arr.end());

    SECTION("Returns first occurance in array"){
        auto indexOf = find(arr.begin(), arr.end(),5);
        auto indexOfTest = poisciZBisekcijo(5, &arr[0], arr.size());
        REQUIRE(indexOf-&arr[0] == indexOfTest);
    }

    SECTION("Doesent throw at n=0"){
        REQUIRE_NOTHROW(poisciZBisekcijo(5, &arr[0], 0));
    }

    SECTION("Doesent alter input array"){
        array<int, 6> arrCpy;
        std::copy(arr.begin(), arr.end(), &arrCpy[0]);
        REQUIRE(arrCpy.size() == 6);
        poisci(5, &arr[0], arr.size());
        REQUIRE(arrCpy == arr);
    }

    SECTION("Works with 10,000,000 elements"){
        const int arraySize = 10000000;
        std::vector<int> numbers(arraySize);

        // Fill the array with numbers from 1 to arraySize
        for (int i = 0; i < arraySize; ++i) {
            numbers[i] = i + 1;
        }
        reverse(numbers.begin(), numbers.end());

        REQUIRE(poisciZBisekcijo(999999, &numbers[0], numbers.size()) == arraySize-999999);
    }

    SECTION("Returns -1 on not found"){
        REQUIRE(poisciZBisekcijo(123, &arr[0], arr.size()) == -1);
    }

    SECTION("Faster than poisci()"){
        const int arraySize = 10000000;
        std::vector<int> numbers(arraySize);

        // Fill the array with numbers from 1 to arraySize
        for (int i = 0; i < arraySize; ++i) {
            numbers[i] = i + 1;
        }
        reverse(numbers.begin(), numbers.end());

        auto start1 = clock();
        poisciZBisekcijo(999999, &numbers[0], numbers.size());
        auto stop1 = clock();

        double duration1 = (double)(stop1-start1)/CLOCKS_PER_SEC;

        auto start2 = clock();
        poisci(999999, &numbers[0], numbers.size());
        auto stop2 = clock();

        double duration2 = (double)(stop2-start2)/CLOCKS_PER_SEC;
        REQUIRE(duration1<duration2);
    }
}

TEST_CASE("urediSPrameni functionality tests", "[urediSPrameni]") {
    int arr[] = {10, 5 ,18, 5,3, 5};

    array<int, 6> sortedReverse = {3,5,5,5,10,18};
    reverse(sortedReverse.begin(), sortedReverse.end());

    SECTION("Sorted set is descending"){
        int* sorted = urediSPrameni(arr, 6);
        for(int i = 0; i<6; i++){
            INFO(sorted);
            CHECK(sortedReverse[i] == sorted[i]);
            sorted++;
        }
    }

}

