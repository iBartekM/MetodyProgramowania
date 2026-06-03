// Mróz Bartłomiej

/**
 * @file matrix.h
 * @brief Deklaracje funkcji wyszukujących element w tablicy 2D
 *        posortowanej niemalejąco w wierszach i kolumnach.
 *        Wszystkie funkcje wykorzystują algorytm Saddleback (O(n+m))
 *        — silnie mniejsza złożoność niż O(max(n,m)^2).
 */

#ifndef MATRIX_H
#define MATRIX_H

// Wynik wyszukiwania — indeksy i wartość
struct Result {
    int value;
    int row;
    int col;
    bool found;
};

// Rekurencyjne — pierwsze wystąpienie (leksykograficznie najmniejsze)
Result f_recFirstOccurrence(int** matrix, int rows, int cols, int target);

// Rekurencyjne — ostatnie wystąpienie (leksykograficznie największe)
Result f_recLastOccurrence(int** matrix, int rows, int cols, int target);

// Iteracyjne — pierwsze wystąpienie
Result f_iterFirstOccurrence(int** matrix, int rows, int cols, int target);

// Iteracyjne — ostatnie wystąpienie
Result f_iterLastOccurrence(int** matrix, int rows, int cols, int target);

#endif
