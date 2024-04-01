#include <ctime>
#include <string>
#include <iostream>
#ifdef Dev
#include "Naloga1.h"
#endif

using namespace std;

int poisci(int el, int* a, int n)
{
	for(int i = 0; i<n;i++){
        if(a[i] == el)
            return i;
    }

	return -1;
}

int binarySearch(const int* arr, int low, int high, int el, int n){
    if (high >= low) {
        int mid = low + (high - low) / 2;
        //Smo nasli element na sredini
        if ((mid == 0 || el < arr[mid - 1]) && arr[mid] == el)
            return mid;
        //Element se nahaja na levi strani
        else if (el < arr[mid])
            return binarySearch(arr, (mid + 1), high, el, n);
        //Element se nahaja na desni strani
        else
            return binarySearch(arr, low, (mid - 1), el, n);
    }
    return -1;
}

int poisciZBisekcijo(int el, int* a, int n)
{
    if (n>0){
        return binarySearch(a, 0, n-1, el, n);
    }

	return -1;
}

int* merge(int* sortedArray, int sortedSize, int* strandArray, int strandSize){
    int* result = new int[sortedSize + strandSize];
    int indexSorted = 0, indexStrand = 0, indexResult = 0;

    while (indexSorted < sortedSize && indexStrand < strandSize) {
        if (sortedArray[indexSorted] >= strandArray[indexStrand]) {
            result[indexResult++] = sortedArray[indexSorted++];
        } else {
            result[indexResult++] = strandArray[indexStrand++];
        }
    }

    //Dokler ni sortedArray prazen
    while (indexSorted < sortedSize) {
        result[indexResult++] = sortedArray[indexSorted++];
    }
    //Dokler ni strandArray prazen
    while (indexStrand < strandSize) {
        result[indexResult++] = strandArray[indexStrand++];
    }

    return result;
}

void reverseArray(int* arr, int size){
    for(int i = 0; i<size/2; i++){
        swap(arr[i], arr[size-1-i]);
    }
}

void removeFromArray(int* &arr, int &arrSize, const int* indicesToRemove, int numIndices) {
    if (numIndices <= 0 || arrSize <= 0) return;

    int newSize = arrSize - numIndices;

    int* newArr = new int[newSize];

    for (int i = 0, j = 0, removalIndex = 0; i < arrSize; ++i) {
        if (removalIndex < numIndices && i == indicesToRemove[removalIndex]) {
            ++removalIndex;
        } else {
            newArr[j++] = arr[i];
        }
    }

    delete[] arr;
    arr = newArr;
    arrSize = newSize;
}

int* urediSPrameni(int* a, int n)
{
    if(n <= 0){
        return NULL;
    }

    int* arrCpy = new int[n];
    for(int i = 0; i<n; i++){
        arrCpy[i] = a[i];
    }

    int* sorted = new int[n];
    int sortedSize = 0;

    while (n > 0) {
        int* strand = new int[n];
        int* removeIndex = new int[n];
        int removeIndexSize = 0;
        int strandSize = 1;
        strand[0] = arrCpy[0];
        removeIndex[removeIndexSize++] = 0;
        int last = arrCpy[0];
        int index = 1;

        for (int i = 1; i < n; i++) {
            if (arrCpy[i] <= last) {
                strand[strandSize++] = arrCpy[i];
                last = arrCpy[i];
                removeIndex[removeIndexSize++] = i;
            } else {
                a[index++] = arrCpy[i];
            }
        }
        int* newSorted = merge(sorted, sortedSize, strand, strandSize);
        delete[] sorted;
        sorted = newSorted;
        sortedSize += strandSize;
        removeFromArray(arrCpy, n, removeIndex, removeIndexSize);
        delete[] removeIndex;
        delete[] strand;
    }
    delete[] arrCpy;
    return sorted;
}


#ifndef DTTESTING
int main()
{
    // Priprava vhodnih podatkov
    int vhod[] = { -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10 };
    const int dolzina = sizeof(vhod) / sizeof(int);

    // Priprava izhodnih podatkov
    int pricakovan_izhod[] = { 10, 8, 6, 4,2, 0, -2, -4, -6, -8, -10 };

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