/**
 * @file LibSearch.cpp
 * @brief Definicje funkcji do wyszukiwania i usuwania duplikatów.
 */

#include "LibSearch.h"

// Zlicza elementy równe val — O(log n)
// Szukamy lewego i prawego krańca binarnie
int f_countEqual(int* T, int n, int val)
{
    // Lewy kraniec — pierwszy indeks >= val
    int lo = 0, hi = n - 1, first = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (T[mid] < val) lo = mid + 1;
        else { first = mid; hi = mid - 1; }
    }

    // Prawy kraniec — ostatni indeks <= val
    lo = 0; hi = n - 1;
    int last = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (T[mid] > val) hi = mid - 1;
        else { last = mid; lo = mid + 1; }
    }

    if (first > last) return 0;
    return last - first + 1;
}

// Wyszukiwanie interpolacyjne
// Zwraca: indeks elementu, -1 jeśli brak, 0 jeśli wszystkie równe val
int f_interpolationSearch(int* T, int n, int val, int count)
{
    if (count == n) return 0;
    if (count == 0) return -1;

    int lo = 0, hi = n - 1;
    while (lo <= hi && val >= T[lo] && val <= T[hi]) {
        if (lo == hi) return (T[lo] == val) ? lo : -1;

        // Pozycja szacowana proporcjonalnie do wartości
        long long pos = lo + ((long long)(val - T[lo]) * (hi - lo)) / (T[hi] - T[lo]);
        if (T[pos] == val) return pos;
        if (T[pos] < val) lo = pos + 1;
        else hi = pos - 1;
    }
    return -1;
}

// Usuwa duplikaty — O(n)
int* f_removeDuplicates(int* T, int n, int& uniqueSize)
{
    uniqueSize = 1;
    for (int i = 1; i < n; i++)
        if (T[i] != T[i - 1]) uniqueSize++;

    int* result = new int[uniqueSize];
    result[0] = T[0];
    int idx = 1;
    for (int i = 1; i < n; i++)
        if (T[i] != T[i - 1]) result[idx++] = T[i];

    return result;
}
