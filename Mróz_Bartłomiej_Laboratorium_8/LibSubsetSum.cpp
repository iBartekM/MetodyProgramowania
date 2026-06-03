// Mróz Bartłomiej

/**
 * @file LibSubsetSum.cpp
 * @brief Implementacja rekurencyjnego wyszukiwania podzbioru o danej sumie.
 */

#include "LibSubsetSum.h"

bool f_findSubset(const int* weights, int k, int target, int idx,
                  int* chosen, int& chosenCount)
{
    // Warunek końcowy: udało się — suma dokładnie 0 oznacza pełne wypełnienie
    if (target == 0) return true;
    // Warunek końcowy: nie da się — przekroczyliśmy lub skończyły się przedmioty
    if (target < 0 || idx >= k) return false;

    // Wariant A: WEŹ weights[idx]
    chosen[chosenCount] = idx;
    chosenCount++;
    if (f_findSubset(weights, k, target - weights[idx], idx + 1,
                     chosen, chosenCount))
        return true;
    chosenCount--; // backtrack — cofamy wybór

    // Wariant B: POMIŃ weights[idx]
    return f_findSubset(weights, k, target, idx + 1, chosen, chosenCount);
}
