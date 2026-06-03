/**
 * @file prog3.cpp
 * @brief Generuje wszystkie podziały liczby n w odwrotnym porządku leksykograficznym.
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
    f_partitions(n, out);
    out.close();

    return 0;
}
