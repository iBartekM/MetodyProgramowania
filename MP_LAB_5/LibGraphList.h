/**
 * @file LibGraphList.h
 * @brief Biblioteka dla grafu NIESKIEROWANEGO: lista incydencji
 *        oparta o listę jednokierunkową (struktura Node).
 *
 * Lista incydencji: dla każdego wierzchołka v trzymamy listę jednokierunkową
 * jego sąsiadów. W grafie nieskierowanym krawędź {u,v} dodajemy do
 * listy u (sąsiad v) ORAZ do listy v (sąsiad u).
 *
 * Stopień wierzchołka = liczba krawędzi przy tym wierzchołku
 *                     = długość jego listy incydencji.
 */

#ifndef LIBGRAPHLIST_H
#define LIBGRAPHLIST_H

#include <fstream>
#include <string>

// Krawędź nieskierowana — para wierzchołków bez kierunku
struct Edge {
    int v1;
    int v2;
};

// Węzeł listy jednokierunkowej (przechowuje numer sąsiada)
struct Node {
    int val;
    Node* next;
};

// Pojedyncza lista incydencji (dla jednego wierzchołka)
struct IncList {
    Node* head; // wskaźnik na pierwszy element
    int size;   // liczba elementów (= stopień wierzchołka)
};

// Parsuje linię "v1-v2" do struktury Edge
Edge f_parseEdge(const std::string& line);

// Znajduje największy numer wierzchołka
int f_findMaxVertex(Edge* edges, int k);

// Tworzy pustą tablicę list incydencji o rozmiarze n
IncList* f_createLists(int n);

// Dodaje element na koniec listy jednokierunkowej
void f_listAppend(IncList& list, int val);

// Zwalnia jedną listę
void f_listDelete(IncList& list);

// Zwalnia tablicę list
void f_deleteLists(IncList* lists, int n);

// Buduje listy incydencji z tablicy krawędzi (graf nieskierowany)
void f_buildIncidence(IncList* lists, Edge* edges, int k);

// Wypisuje listy incydencji do pliku
void f_printLists(std::ofstream& out, IncList* lists, int n);

// Wypisuje stopnie wszystkich wierzchołków
void f_printDegrees(std::ofstream& out, IncList* lists, int n);

#endif
