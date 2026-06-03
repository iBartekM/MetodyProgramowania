/**
 * @file LibFiles.cpp
 * @brief Definicje funkcji do obsługi plików.
 */

#include "LibFiles.h"
#include <iostream>
using namespace std;

void f_readInput(const string& filename, int& numSets,
                 int**& data, int*& sizes, int**& queries, int*& querySizes)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad otwarcia: " << filename << endl;
        numSets = 0;
        return;
    }

    file >> numSets;
    data = new int*[numSets];
    sizes = new int[numSets];
    queries = new int*[numSets];
    querySizes = new int[numSets];

    for (int s = 0; s < numSets; s++) {
        file >> sizes[s];
        data[s] = new int[sizes[s]];
        for (int i = 0; i < sizes[s]; i++)
            file >> data[s][i];

        file >> querySizes[s];
        queries[s] = new int[querySizes[s]];
        for (int i = 0; i < querySizes[s]; i++)
            file >> queries[s][i];
    }
    file.close();
}
