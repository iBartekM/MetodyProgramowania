// Mróz Bartłomiej

/**
 * @file matrix.cpp
 * @brief Implementacja wyszukiwania metodą Saddleback Search.
 *
 * Algorytm Saddleback wykorzystuje fakt, że tablica jest posortowana
 * niemalejąco w wierszach i kolumnach. W każdym kroku eliminujemy
 * cały wiersz LUB całą kolumnę, więc całość działa w O(n+m).
 *
 * Dla pierwszego wystąpienia: start z prawego górnego rogu (0, cols-1).
 *   - jeśli komórka == target  -> zapisz, idź w lewo
 *   - jeśli komórka >  target  -> idź w lewo (większe wartości po prawej)
 *   - jeśli komórka <  target  -> idź w dół (cały wiersz za mały)
 *
 * Dla ostatniego wystąpienia: start z lewego dolnego rogu (rows-1, 0).
 *   - jeśli komórka == target  -> zapisz, idź w prawo
 *   - jeśli komórka <  target  -> idź w prawo
 *   - jeśli komórka >  target  -> idź w górę
 */

#include "matrix.h"

// ===== Pomocnicze: porównanie leksykograficzne pozycji =====

// Czy (i1, j1) jest leksykograficznie MNIEJSZE od (i2, j2)
static bool f_lexLess(int i1, int j1, int i2, int j2)
{
    if (i1 != i2) return i1 < i2;
    return j1 < j2;
}

// Czy (i1, j1) jest leksykograficznie WIĘKSZE od (i2, j2)
static bool f_lexGreater(int i1, int j1, int i2, int j2)
{
    if (i1 != i2) return i1 > i2;
    return j1 > j2;
}

// ===== Rekurencyjne — pierwsze wystąpienie =====

// Pomocnik rekurencyjny — przesuwa się po tablicy bez pętli
static Result f_recFirstHelper(int** matrix, int rows, int cols, int target,
                               int i, int j, Result best)
{
    // Warunek końcowy: wyszliśmy poza tablicę
    if (i >= rows || j < 0) return best;

    if (matrix[i][j] == target) {
        // Aktualizujemy najlepszy wynik tylko jeśli pozycja jest "wcześniejsza"
        if (!best.found || f_lexLess(i, j, best.row, best.col)) {
            best = { target, i, j, true };
        }
        return f_recFirstHelper(matrix, rows, cols, target, i, j - 1, best);
    }
    if (matrix[i][j] > target)
        return f_recFirstHelper(matrix, rows, cols, target, i, j - 1, best);
    // matrix[i][j] < target -> idziemy w dół
    return f_recFirstHelper(matrix, rows, cols, target, i + 1, j, best);
}

Result f_recFirstOccurrence(int** matrix, int rows, int cols, int target)
{
    Result init = { target, -1, -1, false };
    // Start z prawego górnego rogu
    return f_recFirstHelper(matrix, rows, cols, target, 0, cols - 1, init);
}

// ===== Rekurencyjne — ostatnie wystąpienie =====

static Result f_recLastHelper(int** matrix, int rows, int cols, int target,
                              int i, int j, Result best)
{
    // Warunek końcowy
    if (i < 0 || j >= cols) return best;

    if (matrix[i][j] == target) {
        if (!best.found || f_lexGreater(i, j, best.row, best.col)) {
            best = { target, i, j, true };
        }
        return f_recLastHelper(matrix, rows, cols, target, i, j + 1, best);
    }
    if (matrix[i][j] < target)
        return f_recLastHelper(matrix, rows, cols, target, i, j + 1, best);
    // matrix[i][j] > target -> idziemy w górę
    return f_recLastHelper(matrix, rows, cols, target, i - 1, j, best);
}

Result f_recLastOccurrence(int** matrix, int rows, int cols, int target)
{
    Result init = { target, -1, -1, false };
    // Start z lewego dolnego rogu
    return f_recLastHelper(matrix, rows, cols, target, rows - 1, 0, init);
}

// ===== Iteracyjne — pierwsze wystąpienie =====
// Funkcja nie wywołuje innych utworzonych funkcji (oprócz pomocniczego porównania,
// które jest tylko prymitywem porównawczym; jeśli to problem, można je wkleić wprost).

Result f_iterFirstOccurrence(int** matrix, int rows, int cols, int target)
{
    Result best = { target, -1, -1, false };
    int i = 0;
    int j = cols - 1; // start z prawego górnego rogu

    while (i < rows && j >= 0) {
        if (matrix[i][j] == target) {
            // Aktualizacja "lepszej" pozycji (wcześniejszej leksykograficznie)
            bool better = !best.found ||
                          (i < best.row) ||
                          (i == best.row && j < best.col);
            if (better) best = { target, i, j, true };
            j--;
        }
        else if (matrix[i][j] > target) {
            j--;
        }
        else {
            i++;
        }
    }
    return best;
}

// ===== Iteracyjne — ostatnie wystąpienie =====

Result f_iterLastOccurrence(int** matrix, int rows, int cols, int target)
{
    Result best = { target, -1, -1, false };
    int i = rows - 1;
    int j = 0; // start z lewego dolnego rogu

    while (i >= 0 && j < cols) {
        if (matrix[i][j] == target) {
            bool better = !best.found ||
                          (i > best.row) ||
                          (i == best.row && j > best.col);
            if (better) best = { target, i, j, true };
            j++;
        }
        else if (matrix[i][j] < target) {
            j++;
        }
        else {
            i--;
        }
    }
    return best;
}
