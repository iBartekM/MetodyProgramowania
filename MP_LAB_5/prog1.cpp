/**
 * @file prog1.cpp
 * @brief Program 1 - Graf SKIEROWANY: macierz incydencji + sąsiedzi.
 *        Wczytuje krawędzie z pliku, tworzy macierz incydencji jako
 *        tablicę dynamiczną 2D, wypisuje macierz oraz sąsiadów (out-neighbors)
 *        każdego wierzchołka do pliku wyjściowego.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LibGraphMatrix.h"
using namespace std;

int main()
{
    string inputFile, outputFile;
    cin >> inputFile >> outputFile;

    ifstream in(inputFile);
    if (!in.is_open()) return 1;

    int k;
    in >> k;
    if (k <= 0) return 1;

    Edge* edges = new Edge[k];
    for (int i = 0; i < k; i++) {
        string line;
        in >> line;
        edges[i] = f_parseEdge(line);
    }
    in.close();

    int n = f_findMaxVertex(edges, k);

    ofstream out(outputFile);
    out << "=== Graf skierowany ===" << endl;
    out << "Liczba wierzcholkow: " << n << endl;
    out << "Liczba krawedzi:     " << k << endl << endl;

    out << "Macierz incydencji:" << endl;
    int** matrix = f_createMatrix(edges, k, n);
    f_printMatrix(out, matrix, n, k);
    f_deleteMatrix(matrix, n);

    out << endl << "Sasiedzi (krawedzie wychodzace):" << endl;
    f_printNeighbors(out, edges, k, n);

    out.close();
    delete[] edges;
    return 0;
}
