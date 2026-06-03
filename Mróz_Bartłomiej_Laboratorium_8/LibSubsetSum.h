// Mróz Bartłomiej

/**
 * @file LibSubsetSum.h
 * @brief Problem plecakowy z dokładnym wypełnieniem — rozwiązanie rekurencyjne.
 *
 * Szukamy podciągu wag a_1, ..., a_k, którego suma wynosi DOKŁADNIE n
 * (pojemność plecaka). Każdej wagi można użyć co najwyżej raz (decyzja
 * binarna: weź albo pomiń).
 *
 * UWAGA: funkcja rekurencyjna NIE zawiera żadnej pętli.
 */

#ifndef LIBSUBSETSUM_H
#define LIBSUBSETSUM_H

// Rekurencyjnie szuka podzbioru wag sumującego się do "target".
//   weights      - tablica wag (rozmiar k)
//   k            - liczba wag
//   target       - pozostała pojemność do wypełnienia
//   idx          - aktualny indeks (0 na początku)
//   chosen       - tablica indeksów wybranych wag (alokowana przez wywołującego)
//   chosenCount  - liczba aktualnie wybranych (referencja, modyfikowana)
//
// Zwraca true gdy znaleziono dokładne rozwiązanie.
// Indeksy w chosen są w kolejności wejściowej (rosnące indeksy).
bool f_findSubset(const int* weights, int k, int target, int idx,
                  int* chosen, int& chosenCount);

#endif
