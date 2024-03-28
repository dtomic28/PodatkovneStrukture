//
// Created by Danijel Tomić on 28. 03. 24.
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <iostream>
#include "Naloga1.h"

using namespace std;

TEST_CASE("poisci functionality") {
    int testArray[] = {5, 3, 1, 4, 2, 1};
    int n = sizeof(testArray) / sizeof(testArray[0]);
    int largeArraySize = 10000000;
    int *largeArray = new int[largeArraySize];
    std::fill_n(largeArray, largeArraySize
                            - 1, 1);
    largeArray[largeArraySize - 1] = 2; // Ensure the function works with large arrays

    SECTION("returns first occurrence in array") {
        REQUIRE(poisci(1, testArray, n)
                == 2);
    }

    SECTION("does not return error on empty array") {
        REQUIRE(poisci(1, nullptr, 0)
                == -1);
    }

    SECTION("returns correct index of the found element in the array") {
        REQUIRE(poisci(4, testArray, n)
                == 3);
    }

    SECTION("works for 10 million elements") {
        REQUIRE(poisci(2, largeArray, largeArraySize)
                == largeArraySize - 1);
    }

    delete[]
            largeArray; // Clean up
}

TEST_CASE("poisciZBisekcijo functionality") {
    int testArray[] = {1, 2, 3, 4, 5, 3};
    int n = sizeof(testArray) / sizeof(testArray[0]);
    int largeArraySize = 10000000;
    int *largeArray = new int[largeArraySize];
    std::fill_n(largeArray, largeArraySize,
                2);
    largeArray[largeArraySize / 2] = 1; // Ensure a mid-point for binary search

    SECTION("returns correct index of the found element in a sorted array") {
        std::sort(testArray, testArray
                             + n); // Ensure sorted for binary search
        REQUIRE(poisciZBisekcijo(3, testArray, n)
                >= 0); // Specific index might vary based on implementation
    }

    SECTION("does not return error on empty array") {
        REQUIRE(poisciZBisekcijo(3, nullptr, 0)
                == -1);
    }

    SECTION("works for 10 million elements") {
        std::sort(largeArray, largeArray
                              + largeArraySize); // Ensure sorted for binary search
        std::reverse(largeArray, largeArray + largeArraySize);
        REQUIRE(poisciZBisekcijo(1, largeArray, largeArraySize)
                == largeArraySize-1);
    }

    delete[] largeArray; // Clean up
}

bool is_descending(const int* arr, int n) {
    for (int i = 0; i < n-1; ++i) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool same_elements(const int original[], const int sorted[], int n) {
   for(int i = 0; i<n; i++){
       if(original[i] != sorted[i])
           return false;
   }
   return true;
}

TEST_CASE("urediSPrameni functionality tests", "[urediSPrameni]") {
    SECTION("Sorts in descending order") {
        using namespace std;
        int arr[] = {1, 5, 2, 4, 3};
        int n = 5;
        int* sorted = urediSPrameni(arr, n);
        int sortedWorking[n];
        std::copy(arr, arr+n, sortedWorking);
        std::sort(arr, arr+n);
        std::reverse(arr, arr+n);
        REQUIRE(same_elements(sorted, sortedWorking, n));
        delete[] sorted; // Assuming the function allocates new memory
    }

    SECTION("Retains all original elements") {
        int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        int n = sizeof(arr) / sizeof(arr[0]);
        int arrNew[n];
        std::copy(arr, arr+n, arrNew);
        int* sorted = urediSPrameni(arr, n);
        REQUIRE(same_elements(arr, arrNew, n));
        delete[] sorted; // Assuming the function allocates new memory
    }

    SECTION("Handles empty array") {
        int* sorted = urediSPrameni(nullptr, 0);
        REQUIRE(sorted == nullptr); // Assuming the function returns nullptr for n = 0
        // No need to delete[] sorted if nullptr is returned for empty input
    }

    SECTION("Can process large array") {
        int n = 10000;
        int* arr = new int[n];
        // Fill the array with some pattern or random values
        for (int i = 0; i < n; ++i) arr[i] = i % 100; // Example pattern
        int* sorted = urediSPrameni(arr, n);
        REQUIRE(is_descending(sorted, n));
        delete[] arr;
        delete[] sorted;
    }
}

