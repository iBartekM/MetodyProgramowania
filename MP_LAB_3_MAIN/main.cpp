/**
 * @file main.cpp
 * @brief Program realizujący wyszukiwanie binarne, interpolacyjne
 *        oraz usuwanie duplikatów na posortowanej tablicy.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LibSearch.h"
#include "LibFiles.h"
using namespace std;

int main()
{
    string inputFile, outputFile;
    cin >> inputFile >> outputFile;

    int numSets;
    int** data;
    int* sizes;
    int** queries;
    int* querySizes;
    f_readInput(inputFile, numSets, data, sizes, queries, querySizes);
    if (numSets == 0) return 1;

    ofstream out(outputFile);

    for (int s = 0; s < numSets; s++) {
        int n = sizes[s];
        int* T = data[s];

        // Dla każdego zapytania wypisz parę (i j)
        for (int k = 0; k < querySizes[s]; k++) {
            int val = queries[s][k];
            int count = f_countEqual(T, n, val);
            int idx = f_interpolationSearch(T, n, val, count);
            out << "(" << count << " " << idx << ")";
        }
        out << "\n";

        // Unikalne elementy — max 200, po 50 na linię
        int uSize;
        int* unique = f_removeDuplicates(T, n, uSize);
        int limit = (uSize < 200) ? uSize : 200;
        for (int k = 0; k < limit; k++) {
            out << unique[k];
            if ((k + 1) % 50 == 0 || k == limit - 1) out << "\n";
            else out << " ";
        }
        delete[] unique;
    }
    out.close();

    for (int s = 0; s < numSets; s++) {
        delete[] data[s];
        delete[] queries[s];
    }
    delete[] data;
    delete[] sizes;
    delete[] queries;
    delete[] querySizes;

    return 0;
}
