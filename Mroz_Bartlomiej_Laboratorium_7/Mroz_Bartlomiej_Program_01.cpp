// Mróz Bartłomiej

/**
 * @file Mroz_Bartlomiej_Program_01.cpp
 * @brief Generator liczb pseudolosowych — dwie metody:
 *        1) Liniowa metoda kongruencyjna (LCG)
 *        2) Addytywna metoda kongruencyjna (lagged Fibonacci)
 *
 *        Program wczytuje dane z klawiatury (cin) i zapisuje wygenerowany
 *        ciąg liczb do pliku tekstowego w postaci kolumny.
 *
 * Format wejścia:
 *   1) Wybór metody:           liczba 1 (LCG)  lub  2 (Addytywna)
 *   2) Nazwa pliku wyjściowego: napis (np. output.txt)
 *
 *   Dla metody 1 (LCG):
 *     X_max   - maksymalna wartość pseudolosowa
 *     X_0     - ziarno (z zakresu [0, X_max])
 *     n       - liczba wartości do wygenerowania
 *
 *   Dla metody 2 (Addytywna):
 *     m       - moduł
 *     l k     - para opóźnień z tabeli (np. "1 2" lub "5 17")
 *     n       - liczba wartości do wygenerowania
 *     k ziaren X_0, X_1, ..., X_{k-1}  (każde z [0, m-1])
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "LibLCG.h"
#include "LibAddCong.h"

using namespace std;

// Zapisuje tablicę liczb do pliku w formacie kolumny (jedna liczba na linię)
void f_saveToFile(const string& filename, long long* data, int n)
{
    ofstream out(filename);
    if (!out.is_open()) throw runtime_error("Nie mozna otworzyc pliku do zapisu");

    for (int i = 0; i < n; i++) {
        out << data[i] << "\n";
    }
    out.close();
}

int main()
{
    try {
        // 1) Wybór metody (1 = LCG, 2 = Addytywna)
        int choice;
        cin >> choice;
        if (choice != 1 && choice != 2)
            throw invalid_argument("Niepoprawny wybor metody (oczekiwano 1 lub 2)");

        // 2) Nazwa pliku wyjściowego
        string outFile;
        cin >> outFile;

        // ===== Metoda 1: LCG =====
        if (choice == 1) {
            long long xMax, x0;
            int n;
            cin >> xMax >> x0 >> n;

            if (xMax <= 0) throw invalid_argument("X_max musi byc dodatnie");
            if (x0 < 0 || x0 > xMax) throw invalid_argument("Ziarno poza zakresem");
            if (n <= 0) throw invalid_argument("n musi byc dodatnie");

            // Wyliczenie wspolczynnikow m, a, c
            LCGParams params = f_calculateParams(xMax);

            // Dynamiczna alokacja tablicy wynikow
            long long* output = new long long[n];
            f_generateLCG(output, n, x0, params);

            f_saveToFile(outFile, output, n);

            delete[] output;
        }
        // ===== Metoda 2: Addytywna =====
        else {
            long long m;
            int l, k, n;
            cin >> m >> l >> k >> n;

            if (m <= 0) throw invalid_argument("m musi byc dodatnie");
            if (l <= 0 || k <= 0 || l >= k) throw invalid_argument("Wymagane: 0 < l < k");
            if (n <= 0) throw invalid_argument("n musi byc dodatnie");

            // Dynamiczna alokacja tablicy ziaren — k wartosci poczatkowych
            long long* seed = new long long[k];
            for (int i = 0; i < k; i++) {
                cin >> seed[i];
                if (seed[i] < 0 || seed[i] >= m)
                    throw invalid_argument("Ziarno poza zakresem [0, m-1]");
            }

            // Dynamiczna alokacja tablicy wynikow
            long long* output = new long long[n];
            f_generateAddCong(output, n, m, l, k, seed);

            f_saveToFile(outFile, output, n);

            delete[] output;
            delete[] seed;
        }
    }
    catch (const exception& e) {
        cerr << "Blad: " << e.what() << endl;
        return 1;
    }

    return 0;
}
