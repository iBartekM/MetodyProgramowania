// Mróz Bartłomiej

/**
 * @file LibKnapsackDP.cpp
 * @brief Implementacja programu dynamicznego dla problemu plecakowego ogólnego.
 */

#include "LibKnapsackDP.h"
#include <iomanip>

void f_solveDP(const Item* items, int n, int mMax, int** P, int** Q)
{
    // Wiersz zerowy: brak przedmiotów -> wartość 0 dla każdej pojemności
    for (int j = 0; j <= mMax; j++) {
        P[0][j] = 0;
        Q[0][j] = 0;
    }

    // Dla każdego rodzaju przedmiotu i = 1..n
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= mMax; j++) {
            // Wariant A: nie bierzemy przedmiotu i
            P[i][j] = P[i - 1][j];
            Q[i][j] = 0;

            // Wariant B: bierzemy przedmiot i (jeśli się mieści)
            // — uwaga: P[i][j-m] (nie P[i-1][j-m]) bo nieograniczony
            if (items[i - 1].weight <= j) {
                int alt = P[i][j - items[i - 1].weight] + items[i - 1].price;
                if (alt > P[i][j]) {
                    P[i][j] = alt;
                    Q[i][j] = items[i - 1].id;
                }
            }
        }
    }
}

void f_printTable(std::ofstream& out, int** table, int n, int mMax,
                  const std::string& title)
{
    out << title << ":" << std::endl;

    // Nagłówek kolumn: j = 0..mMax
    out << "      ";
    for (int j = 0; j <= mMax; j++) {
        out << std::setw(5) << ("j=" + std::to_string(j));
    }
    out << std::endl;

    // Każdy wiersz: i = 0..n + wartości
    for (int i = 0; i <= n; i++) {
        out << "i=" << i << ":  ";
        if (i < 10) out << " ";
        for (int j = 0; j <= mMax; j++) {
            out << std::setw(5) << table[i][j];
        }
        out << std::endl;
    }
}
