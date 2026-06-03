// Mróz Bartłomiej

/**
 * @file Mróz_Bartłomiej_Program_01.cpp
 * @brief Problem plecakowy 0-1 metodą algorytmu z powrotami (backtracking).
 *
 * Wejście:
 *   cin >> inputFile  - nazwa pliku wejściowego
 *   cin >> outputFile - nazwa pliku wyjściowego
 *
 * Format pliku wejściowego:
 *   Linia 1:        n W           (liczba przedmiotów, pojemność plecaka)
 *   Linie 2..n+1:   p_i w_i       (zysk, waga i-tego przedmiotu)
 *
 * Plik wyjściowy zawiera:
 *   - Tabela posortowanych przedmiotów (malejąco wg p/w)
 *   - Śledzenie algorytmu krok po kroku (każdy odwiedzony węzeł)
 *   - Wynik: maksymalny zysk + wybrane przedmioty
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "LibKnapsack01.h"

using namespace std;

int main()
{
    try {
        // Wczytanie nazw plików z konsoli
        string inputFile, outputFile;
        cin >> inputFile >> outputFile;

        // Otwarcie pliku wejściowego
        ifstream in(inputFile);
        if (!in.is_open()) throw runtime_error("Nie mozna otworzyc pliku wejsciowego");

        // Wczytanie danych z pliku
        int n, W;
        if (!(in >> n >> W)) throw runtime_error("Brak danych w pliku wejsciowym");
        if (n <= 0 || W <= 0) throw invalid_argument("n i W musza byc dodatnie");

        // Dynamiczna alokacja tablicy przedmiotów
        Item* items = new Item[n];
        for (int i = 0; i < n; i++) {
            items[i].id = i + 1; // numeracja od 1
            in >> items[i].profit >> items[i].weight;
            if (items[i].profit < 0 || items[i].weight <= 0)
                throw invalid_argument("Niepoprawne dane przedmiotu");
            items[i].ratio = (double)items[i].profit / items[i].weight;
        }
        in.close();

        // Otwarcie pliku wyjściowego
        ofstream out(outputFile);
        if (!out.is_open()) throw runtime_error("Nie mozna otworzyc pliku wyjsciowego");

        out << "=== PROBLEM PLECAKOWY 0-1 (BACKTRACKING) ===" << endl;
        out << "Parametry: n=" << n << ", W=" << W << endl << endl;

        out << "Przedmioty (wejsciowe):" << endl;
        out << "  id | profit | weight | p/w" << endl;
        for (int i = 0; i < n; i++) {
            out << "  " << items[i].id << "  | " << items[i].profit
                << "     | " << items[i].weight
                << "     | " << items[i].ratio << endl;
        }
        out << endl;

        // Rozwiązanie problemu
        f_solveKnapsack(items, n, W, out);

        out.close();
        delete[] items;
    }
    catch (const exception& e) {
        cerr << "Blad: " << e.what() << endl;
        return 1;
    }

    return 0;
}
