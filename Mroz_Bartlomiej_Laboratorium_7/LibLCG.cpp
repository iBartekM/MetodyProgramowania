// Mróz Bartłomiej

/**
 * @file LibLCG.cpp
 * @brief Implementacja generatora LCG.
 */

#include "LibLCG.h"

// ===== Funkcje pomocnicze =====

// Największy wspólny dzielnik (algorytm Euklidesa)
static long long f_gcd(long long a, long long b)
{
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Sprawdza czy a spełnia twierdzenie Hull-Dobella dla danego m:
//  1) (a-1) jest podzielne przez wszystkie czynniki pierwsze m
//  2) (a-1) jest podzielne przez 4 jeśli 4 dzieli m
static bool f_satisfiesHullDobell(long long a, long long m)
{
    long long am1 = a - 1;
    long long temp = m;

    // Iterujemy po możliwych czynnikach pierwszych
    for (long long p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            if (am1 % p != 0) return false;
            while (temp % p == 0) temp /= p;
        }
    }
    // Jeśli zostało coś > 1, to ostatni czynnik pierwszy
    if (temp > 1 && am1 % temp != 0) return false;

    // Warunek dla 4
    if (m % 4 == 0 && am1 % 4 != 0) return false;

    return true;
}

// ===== Funkcje publiczne =====

LCGParams f_calculateParams(long long xMax)
{
    LCGParams params;
    params.m = xMax + 1; // wartości będą w [0, X_max]

    // Próba 1: znajdź a spełniające Hull-Dobella (pełny okres = m)
    params.a = 0;
    for (long long a = 2; a < params.m; a++) {
        if (f_satisfiesHullDobell(a, params.m)) {
            params.a = a;
            break;
        }
    }

    // Próba 2: gdy nie ma takiego a (typowo dla m liczb pierwszych),
    // wybierz najmniejsze a > 1 względnie pierwsze z m.
    // Daje pseudolosową sekwencję, choć okres może być krótszy niż m.
    if (params.a == 0) {
        for (long long a = 2; a < params.m; a++) {
            if (f_gcd(a, params.m) == 1) {
                params.a = a;
                break;
            }
        }
    }

    // Awaryjnie (np. m=2)
    if (params.a == 0) params.a = 1;

    // c musi być względnie pierwsze z m i niezerowe
    params.c = 1;
    for (long long c = 1; c < params.m; c++) {
        if (f_gcd(c, params.m) == 1) {
            params.c = c;
            break;
        }
    }

    return params;
}

void f_generateLCG(long long* output, int n, long long x0, LCGParams params)
{
    long long current = x0;
    for (int i = 0; i < n; i++) {
        // Główna formuła LCG
        current = (params.a * current + params.c) % params.m;
        output[i] = current;
    }
}
