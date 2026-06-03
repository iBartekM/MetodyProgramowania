/**
 * @file LibSearch.h
 * @brief Deklaracje funkcji do wyszukiwania i usuwania duplikatów.
 */

#ifndef LIBSEARCH_H
#define LIBSEARCH_H

int f_countEqual(int* T, int n, int val);
int f_interpolationSearch(int* T, int n, int val, int count);
int* f_removeDuplicates(int* T, int n, int& uniqueSize);

#endif
