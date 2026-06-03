/**
 * @file prog1.cpp
 * @brief Generuje wszystkie podzbiory zbioru n-elementowego do pliku tekstowego.
 */

#include <iostream>
#include <fstream>
#include "LibGen.h"
using namespace std;

int main()
{
    int n;
    string outputFile;
    cin >> n >> outputFile;

    ofstream out(outputFile);
    f_allSubsets(n, out);
    out.close();

    return 0;
}
