// Mróz Bartłomiej

/**
 * @file LibLCG.h
 * @brief Liniowa metoda kongruencyjna (LCG):
 *        X_{n+1} = (a * X_n + c) mod m
 *
 * Współczynniki a, c, m są wyliczane automatycznie na podstawie X_max
 * (maksymalna pseudolosowa wartość). Algorytm preferuje wartości
 * spełniające twierdzenie Hull-Dobella (gwarantuje pełny okres = m).
 * Gdy nie istnieją (np. dla m liczby pierwszej), używa wartości
 * dających pseudolosową sekwencję, choć z możliwie krótszym okresem.
 */

#ifndef LIBLCG_H
#define LIBLCG_H

// Wyliczone współczynniki LCG
struct LCGParams {
    long long m; // moduł (zakres)
    long long a; // mnożnik
    long long c; // przyrost
};

// Wylicza współczynniki m, a, c na podstawie maksymalnej wartości X_max.
// m = X_max + 1, a i c dobrane tak by spełnić warunki Hull-Dobella.
LCGParams f_calculateParams(long long xMax);

// Generuje n liczb pseudolosowych do tablicy output (alokowanej przez wywołującego).
// x0 - ziarno (pierwsza wartość X_0, użyta tylko jako stan wejściowy).
void f_generateLCG(long long* output, int n, long long x0, LCGParams params);

#endif
