// Mróz Bartłomiej

/**
 * @file LibKnapsack01.h
 * @brief Problem plecakowy 0-1 rozwiązany algorytmem z powrotami (backtracking).
 *
 * Każdy przedmiot można wziąć CO NAJWYŻEJ RAZ (binarna decyzja: weź / pomiń),
 * w odróżnieniu od wariantu ogólnego (nieograniczonego).
 *
 * Algorytm: drzewo decyzyjne przeszukiwane DFS. Każdy węzeł reprezentuje
 * stan po pewnej liczbie decyzji. Dla każdego węzła liczymy "bound" —
 * teoretyczne maksimum zysku osiągalne z dalszej rozbudowy (relaksacja
 * problemu plecakowego ułamkowego). Gdy bound <= aktualne najlepsze,
 * obcinamy poddrzewo (BRANCH & BOUND).
 *
 * UWAGA: Przedmioty muszą być posortowane MALEJĄCO wg stosunku p/w.
 *        Wtedy "bound" daje wiarygodne oszacowanie górne.
 */

#ifndef LIBKNAPSACK01_H
#define LIBKNAPSACK01_H

#include <fstream>

// Pojedynczy przedmiot
struct Item {
    int id;         // numer oryginalny (przed sortowaniem)
    int profit;     // p_i — wartość/zysk
    int weight;     // w_i — waga
    double ratio;   // p_i / w_i (do sortowania i obliczania bound)
};

// Stan rozwiązania — przekazywany przez referencję przez całą rekurencję
struct SolverState {
    int n;              // liczba przedmiotów
    int W;              // pojemność plecaka
    int maxProfit;      // aktualny najlepszy zysk
    bool* bestSet;      // które przedmioty są w najlepszym rozwiązaniu
    bool* include;      // które są wzięte w aktualnej ścieżce
    int stepCounter;    // licznik kroków (dla logowania)
    Item* items;        // przedmioty (posortowane)
    std::ofstream* out; // strumień do zapisu kroków
};

// Sortuje przedmioty malejąco wg p/w (sortowanie bąbelkowe — proste, n małe)
void f_sortByRatio(Item* items, int n);

// Oblicza "bound" — górne oszacowanie zysku osiągalne z dalszej rozbudowy.
// Używa relaksacji ułamkowej (możemy brać kawałek przedmiotu).
double f_bound(int level, int weight, int profit, const SolverState& state);

// Rekurencyjne odwiedzenie węzła w drzewie decyzyjnym
void f_checknode(int level, int weight, int profit, SolverState& state);

// Główna funkcja — uruchamia algorytm i zapisuje wynik
void f_solveKnapsack(Item* items, int n, int W, std::ofstream& out);

#endif
