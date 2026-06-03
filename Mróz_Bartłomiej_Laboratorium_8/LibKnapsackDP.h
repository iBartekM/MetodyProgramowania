// Mróz Bartłomiej

/**
 * @file LibKnapsackDP.h
 * @brief Problem plecakowy OGÓLNY (nieograniczony) rozwiązany metodą
 *        programowania dynamicznego.
 *
 * Dla każdego rodzaju przedmiotu i o wadze m_i i cenie c_i, wyznaczamy
 * tablicę P[i][j] = maksymalna wartość plecaka o pojemności j przy użyciu
 * dowolnej liczby przedmiotów rodzajów 1..i.
 *
 * Wzór rekurencyjny (NIEOGRANICZONY — każdego rodzaju można użyć wielokrotnie):
 *   P[i][j] = max( P[i-1][j],                       // nie bierz przedmiotu i
 *                  P[i][j - m_i] + c_i )            // weź przedmiot i (i znowu)
 *
 * Tablica Q[i][j] = identyfikator przedmiotu pakowanego w ostatnim ruchu
 *                   (0 jeśli przedmiotu i nie wzięto).
 */

#ifndef LIBKNAPSACKDP_H
#define LIBKNAPSACKDP_H

#include <fstream>
#include <string>

// Pojedynczy przedmiot — identyfikator, waga, cena
struct Item {
    int id;
    int weight;
    int price;
};

// Wypełnia tablice P[0..n][0..mMax] i Q[0..n][0..mMax]
// (tablice muszą być zaalokowane przez wywołującego)
void f_solveDP(const Item* items, int n, int mMax, int** P, int** Q);

// Wypisuje tablicę do strumienia z nagłówkami wierszy/kolumn
void f_printTable(std::ofstream& out, int** table, int n, int mMax,
                  const std::string& title);

#endif
