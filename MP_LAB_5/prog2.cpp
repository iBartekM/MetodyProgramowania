/**
 * @file prog2.cpp
 * @brief Program 2 - Graf NIESKIEROWANY: lista incydencji + stopnie wierzchołków.
 *        Wczytuje krawędzie z pliku, buduje listy incydencji
 *        (lista jednokierunkowa - własna struktura), wypisuje listy
 *        oraz stopnie wszystkich wierzchołków do pliku wyjściowego.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LibGraphList.h"
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
    out << "=== Graf nieskierowany ===" << endl;
    out << "Liczba wierzcholkow: " << n << endl;
    out << "Liczba krawedzi:     " << k << endl << endl;

    IncList* lists = f_createLists(n);
    f_buildIncidence(lists, edges, k);

    out << "Lista incydencji:" << endl;
    f_printLists(out, lists, n);

    out << endl << "Stopnie wierzcholkow:" << endl;
    f_printDegrees(out, lists, n);

    f_deleteLists(lists, n);
    delete[] edges;
    out.close();
    return 0;
}
