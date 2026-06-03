// Mróz Bartłomiej

/**
 * @file Nazwisko_Imie_Program_01.cpp
 * @brief Wyszukiwanie elementu w tablicy 2D za pomocą 4 funkcji
 *        (rekurencyjna pierwsze/ostatnie + iteracyjna pierwsze/ostatnie).
 *        Tablica posortowana niemalejąco w wierszach i kolumnach.
 *        Złożoność wyszukiwania: O(n+m) — algorytm Saddleback.
 *
 * Wejście: standardowe (klawiatura) — zgodnie ze specyfikacją zadania.
 * Wyjście: plik tekstowy "output.txt" w katalogu programu.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "matrix.h"

using namespace std;

// Stała nazwa pliku wyjściowego
const string OUTPUT_FILE = "output.txt";

/**
 * Wypisuje wynik w formacie wymaganym przez zadanie:
 *   "Etykieta: X w (i,j)"   gdy znaleziono
 *   "Etykieta: nie ma X"    gdy nie znaleziono
 */
void f_printResult(ofstream& out, const string& label, const Result& r)
{
    if (r.found)
        out << label << r.value << " w (" << r.row << "," << r.col << ")" << endl;
    else
        out << label << "nie ma " << r.value << endl;
}

int main()
{
    try {
        // Otwarcie pliku wyjściowego
        ofstream out(OUTPUT_FILE);
        if (!out.is_open()) throw runtime_error("Nie mozna otworzyc pliku wyjsciowego");

        int t;
        cin >> t;
        if (t <= 0) throw invalid_argument("Liczba zestawow musi byc dodatnia");

        while (t--) {
            int n, m;
            cin >> n >> m;
            if (n <= 0 || m <= 0)
                throw invalid_argument("Wymiary musza byc dodatnie");

            // Dynamiczna alokacja tablicy 2D
            int** matrix = new int*[n];
            for (int i = 0; i < n; i++)
                matrix[i] = new int[m];

            // Wczytanie danych tablicy z klawiatury
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    cin >> matrix[i][j];

            int target;
            cin >> target;

            // Cztery wyszukiwania
            Result rekFirst  = f_recFirstOccurrence(matrix, n, m, target);
            Result rekLast   = f_recLastOccurrence(matrix, n, m, target);
            Result iterFirst = f_iterFirstOccurrence(matrix, n, m, target);
            Result iterLast  = f_iterLastOccurrence(matrix, n, m, target);

            // Zapis do pliku wyjściowego
            f_printResult(out, "RekPier: ",  rekFirst);
            f_printResult(out, "RekOst: ",   rekLast);
            f_printResult(out, "IterPier: ", iterFirst);
            f_printResult(out, "IterOst: ",  iterLast);
            out << "---" << endl;

            // Zwolnienie pamięci
            for (int i = 0; i < n; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        out.close();
    }
    catch (const exception& e) {
        cerr << "Blad: " << e.what() << endl;
        return 1;
    }

    return 0;
}
