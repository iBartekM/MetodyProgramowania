/**
 * @file LibGraphMatrix.cpp
 * @brief Implementacja macierzy incydencji grafu skierowanego.
 */

#include "LibGraphMatrix.h"
#include <cstdio>

Edge f_parseEdge(const std::string& line)
{
    // Linia w formacie "src-dst", np. "1-2"
    Edge e;
    sscanf(line.c_str(), "%d-%d", &e.src, &e.dst);
    return e;
}

int f_findMaxVertex(Edge* edges, int k)
{
    int maxV = 0;
    for (int i = 0; i < k; i++) {
        if (edges[i].src > maxV) maxV = edges[i].src;
        if (edges[i].dst > maxV) maxV = edges[i].dst;
    }
    return maxV;
}

int** f_createMatrix(Edge* edges, int k, int n)
{
    // Alokacja: n wierszy (wierzchołki), k kolumn (krawędzie)
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[k];
        for (int j = 0; j < k; j++)
            matrix[i][j] = 0;
    }
    // Wypełnianie: dla każdej krawędzi zaznaczamy źródło (+1) i cel (-1)
    for (int j = 0; j < k; j++) {
        matrix[edges[j].src - 1][j] = 1;
        matrix[edges[j].dst - 1][j] = -1;
    }
    return matrix;
}

void f_deleteMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void f_printMatrix(std::ofstream& out, int** matrix, int n, int k)
{
    // Nagłówek z numerami krawędzi
    out << "       ";
    for (int j = 0; j < k; j++)
        out << "e" << (j + 1) << "\t";
    out << std::endl;

    // Każdy wiersz = jeden wierzchołek
    for (int i = 0; i < n; i++) {
        out << "v" << (i + 1) << ":   ";
        for (int j = 0; j < k; j++)
            out << matrix[i][j] << "\t";
        out << std::endl;
    }
}

void f_printNeighbors(std::ofstream& out, Edge* edges, int k, int n)
{
    // Dla każdego wierzchołka wypisujemy te wierzchołki,
    // do których prowadzi krawędź WYCHODZĄCA z tego wierzchołka
    for (int v = 1; v <= n; v++) {
        out << "v" << v << ": ";
        bool any = false;
        for (int j = 0; j < k; j++) {
            if (edges[j].src == v) {
                out << edges[j].dst << " ";
                any = true;
            }
        }
        if (!any) out << "(brak)";
        out << std::endl;
    }
}
