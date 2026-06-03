// Mróz Bartłomiej

/**
 * @file Mróz_Bartłomiej_Program_01.cpp
 * @brief Problem plecakowy OGÓLNY (nieograniczony) — programowanie dynamiczne.
 *
 * Wejście (standardowe wejście, cin) — format zgodny z zadaniem:
 *   Linia 1:     M_max  (pojemność plecaka)
 *   Linie 2..:   P_i m_i c_i  (id, waga, cena) — czytane DO KOŃCA PLIKU
 *
 * Wyjście (plik "output1.txt"):
 *   Tablica P[i][j] — najlepsze wartości
 *   Tablica Q[i][j] — przedmiot pakowany w ostatnim ruchu
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "LibKnapsackDP.h"

using namespace std;

const string OUTPUT_FILE = "output1.txt";

int main()
{
    try {
        int mMax;
        if (!(cin >> mMax)) throw runtime_error("Brak danych wejsciowych");
        if (mMax <= 0) throw invalid_argument("Pojemnosc M_max musi byc dodatnia");

        // Dynamiczne wczytywanie przedmiotów AŻ DO EOF (zgodnie z zadaniem).
        // Startujemy z buforem o pojemności 16, podwajamy gdy się skończy.
        int capacity = 16;
        Item* items = new Item[capacity];
        int n = 0;
        Item tmp;
        while (cin >> tmp.id >> tmp.weight >> tmp.price) {
            if (tmp.weight <= 0 || tmp.price < 0)
                throw invalid_argument("Waga musi byc dodatnia, cena nieujemna");

            if (n >= capacity) {
                // Realokacja: podwajamy pojemność tablicy
                int newCap = capacity * 2;
                Item* newItems = new Item[newCap];
                for (int i = 0; i < n; i++) newItems[i] = items[i];
                delete[] items;
                items = newItems;
                capacity = newCap;
            }
            items[n++] = tmp;
        }

        if (n == 0) throw invalid_argument("Brak przedmiotow w pliku wejsciowym");

        // Dynamiczna alokacja tablic 2D: (n+1) wierszy x (mMax+1) kolumn
        int** P = new int*[n + 1];
        int** Q = new int*[n + 1];
        for (int i = 0; i <= n; i++) {
            P[i] = new int[mMax + 1];
            Q[i] = new int[mMax + 1];
        }

        // Rozwiązanie problemu plecakowego
        f_solveDP(items, n, mMax, P, Q);

        // Zapis wyniku do pliku
        ofstream out(OUTPUT_FILE);
        if (!out.is_open()) throw runtime_error("Nie mozna otworzyc pliku wyjsciowego");

        f_printTable(out, P, n, mMax, "Tablica P (najlepsze wartosci upakowan)");
        out << endl;
        f_printTable(out, Q, n, mMax, "Tablica Q (przedmiot pakowany w ostatnim ruchu)");

        out.close();

        // Zwolnienie pamięci
        for (int i = 0; i <= n; i++) {
            delete[] P[i];
            delete[] Q[i];
        }
        delete[] P;
        delete[] Q;
        delete[] items;
    }
    catch (const exception& e) {
        cerr << "Blad: " << e.what() << endl;
        return 1;
    }

    return 0;
}
