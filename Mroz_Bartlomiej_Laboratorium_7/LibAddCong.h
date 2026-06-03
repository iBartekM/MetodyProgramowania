// Mróz Bartłomiej

/**
 * @file LibAddCong.h
 * @brief Addytywna metoda kongruencyjna (opóźniony Fibonacci):
 *        X_n = (X_{n-l} + X_{n-k}) mod m,  dla n >= k
 *
 * Wymaga k początkowych wartości (ziarna) podanych przez użytkownika.
 * Pary (l, k) wybierane są z tablicy zalecanych par (rys. z zadania) —
 * np. (1,2), (5,17), (7,31) zapewniają długi okres.
 */

#ifndef LIBADDCONG_H
#define LIBADDCONG_H

// Generuje n liczb pseudolosowych metodą addytywną.
//   output  - tablica o rozmiarze n (alokowana przez wywołującego)
//   n       - liczba wartości do wygenerowania
//   m       - moduł
//   l, k    - para z tabeli zalecanych par (l < k)
//   seed    - tablica k początkowych wartości (X_0, X_1, ..., X_{k-1})
void f_generateAddCong(long long* output, int n, long long m,
                       int l, int k, const long long* seed);

#endif
