#include <ctime>
#include <string>
#include <iostream>
#ifdef Dev
#include "Naloga1.h"
#endif

using namespace std;

int poisci(int el, int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == el)
            return i;
    }

    return -1;
}

int binarySearch(const int* arr, int low, int high, int el, int n)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        // Check if the mid element is the first occurrence of x
        if ((mid == 0 || el < arr[mid - 1]) && arr[mid] == el)
            return mid;
        else if (el < arr[mid])
            // Go right since the right side contains the smaller elements
            return binarySearch(arr, (mid + 1), high, el, n);
        else
            // Go left since the left side contains the larger elements
            return binarySearch(arr, low, (mid - 1), el, n);
    }
    return -1;
}

int poisciZBisekcijo(int el, int* a, int n)
{
    if (n > 0)
    {
        return binarySearch(a, 0, n - 1, el, n);
    }

    return -1;
}

int* merge(int* a, int sizeA, int* b, int sizeB)
{
    int* result = new int[sizeA + sizeB];
    int indexA = 0, indexB = 0, indexResult = 0;

    while (indexA < sizeA && indexB < sizeB)
    {
        if (a[indexA] > b[indexB])
        {
            result[indexResult++] = a[indexA++];
        }
        else
        {
            result[indexResult++] = b[indexB++];
        }
    }

    // Copy any remaining elements
    while (indexA < sizeA)
    {
        result[indexResult++] = a[indexA++];
    }
    while (indexB < sizeB)
    {
        result[indexResult++] = b[indexB++];
    }

    return result;
}

void reverseArray(int* arr, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        swap(arr[i], arr[size - 1 - i]);
    }
}

int* urediSPrameni(int* a, int n)
{
    if (n <= 0)
    {
        return NULL;
    }

    int* sorted = new int[n];
    int sortedSize = 0;

    while (n > 0)
    {
        int* strand = new int[n];
        int strandSize = 1;
        strand[0] = a[0];

        int last = a[0];
        int index = 1;

        for (int i = 1; i < n; i++)
        {
            if (a[i] >= last)
            {
                strand[strandSize++] = a[i];
                last = a[i];
            }
            else
            {
                a[index++] = a[i];
            }
        }
        int* newSorted = merge(sorted, sortedSize, strand, strandSize);
        delete[] sorted;
        sorted = newSorted;
        sortedSize += strandSize;
        n = index - 1;

        delete[] strand;
    }
    reverseArray(sorted, sortedSize);
    return sorted;
}

#ifndef DTTESTING
int main()
{
    // Priprava vhodnih podatkov
    int vhod[] = {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
    const int dolzina = sizeof(vhod) / sizeof(int);

    // Priprava izhodnih podatkov
    int pricakovan_izhod[] = {10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10};

    // Klic testirane metode
    int* dobljen_izhod = urediSPrameni(vhod, dolzina);

    // Preverjanje dobljenega izhoda
    if (dobljen_izhod != NULL)
    {
        for (int i = 0; i < dolzina; i++)
        {
            if (pricakovan_izhod[i] != dobljen_izhod[i])
            {
                cout << "Metoda urediSPrameni() ni vrnila pravilno urejenega polja." << endl;
                break;
            }
        }
        // Ko je dobljen_izhod == NULL
    }
    else
        cout << "Metoda urediSPrameni() ni vrnila polja, pac pa NULL." << endl;

    // Ciscenje spomina
    if (dobljen_izhod != NULL)
        delete[] dobljen_izhod;

    return 0;
}
#endif