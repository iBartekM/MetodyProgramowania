/**
 * @file LibGen.h
 * @brief Deklaracje funkcji generujących podzbiory i podziały liczb.
 */

#ifndef LIBGEN_H
#define LIBGEN_H

#include <fstream>

// Generuje wszystkie podzbiory zbioru n-elementowego (ciąg Graya)
void f_allSubsets(int n, std::ofstream& out);

// Generuje wszystkie k-elementowe podzbiory {1,...,n} w porządku leksykograficznym
void f_kSubsets(int n, int k, std::ofstream& out);

// Generuje wszystkie podziały liczby n w odwrotnym porządku leksykograficznym
void f_partitions(int n, std::ofstream& out);

#endif
