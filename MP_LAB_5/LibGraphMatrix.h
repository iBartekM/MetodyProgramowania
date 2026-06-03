/**
 * @file LibGraphMatrix.h
 * @brief Biblioteka dla grafu skierowanego: macierz incydencji
 *        (tablica dynamiczna 2D) + wyznaczanie sąsiadów wierzchołków.
 *
 * Format krawędzi: para (src, dst) — krawędź wychodzi z src i wchodzi do dst.
 * W macierzy: wiersze = wierzchołki, kolumny = krawędzie.
 *   +1 = krawędź wychodzi z tego wierzchołka
 *   -1 = krawędź wchodzi do tego wierzchołka
 *    0 = krawędź nie dotyczy tego wierzchołka
 */

#ifndef LIBGRAPHMATRIX_H
#define LIBGRAPHMATRIX_H

#include <fstream>
#include <string>

// Krawędź skierowana
struct Edge {
    int src; // wierzchołek wyjściowy
    int dst; // wierzchołek docelowy
};

// Parsuje linię w formacie "src-dst" do struktury Edge
Edge f_parseEdge(const std::string& line);

// Znajduje największy numer wierzchołka — daje rozmiar macierzy
int f_findMaxVertex(Edge* edges, int k);

// Tworzy macierz incydencji jako tablicę dynamiczną 2D (n wierszy x k kolumn)
int** f_createMatrix(Edge* edges, int k, int n);

// Zwalnia macierz
void f_deleteMatrix(int** matrix, int n);

// Wypisuje macierz do strumienia wyjściowego
void f_printMatrix(std::ofstream& out, int** matrix, int n, int k);

// Wypisuje sąsiadów (wierzchołki do których prowadzą krawędzie wychodzące)
void f_printNeighbors(std::ofstream& out, Edge* edges, int k, int n);

#endif
