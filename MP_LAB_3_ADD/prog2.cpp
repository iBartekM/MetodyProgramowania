/**
 * @file prog2.cpp
 * @brief Generuje wszystkie k-elementowe podzbiory {1,...,n} w porządku leksykograficznym.
 */

#include <iostream>
#include <fstream>
#include "LibGen.h"
using namespace std;

int main()
{
    int n, k;
    string outputFile;
    cin >> n >> k >> outputFile;

    ofstream out(outputFile);
    f_kSubsets(n, k, out);
    out.close();

    return 0;
}
