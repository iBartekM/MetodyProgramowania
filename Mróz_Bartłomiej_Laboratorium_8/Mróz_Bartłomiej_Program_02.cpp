// Mróz Bartłomiej

/**
 * @file Mróz_Bartłomiej_Program_02.cpp
 * @brief Problem plecakowy z dokładnym wypełnieniem — rekurencja.
 *
 * Dla każdego zestawu znajdujemy ciąg wag, którego suma równa się dokładnie
 * pojemności plecaka. Jeśli brak rozwiązania — wypisujemy "BRAK".
 *
 * Wejście (standardowe wejście, cin):
 *   Linia 1:     z          (liczba zestawów danych)
 *   Dla każdego zestawu:
 *     n         (pojemność plecaka)
 *     k         (liczba wag)
 *     k liczb   (a_1 ... a_k, niepowtarzające się)
 *
 * Wyjście (plik "output2.txt"):
 *   Dla każdego zestawu jedna linia:
 *     "n = a_i1 a_i2 ... a_ip"    (z zachowaniem kolejności wejściowej)
 *     lub
 *     "BRAK"
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "LibSubsetSum.h"

using namespace std;

const string OUTPUT_FILE = "output2.txt";

int main()
{
    try {
        int z;
        cin >> z;
        if (z <= 0) throw invalid_argument("Liczba zestawow z musi byc dodatnia");

        ofstream out(OUTPUT_FILE);
        if (!out.is_open()) throw runtime_error("Nie mozna otworzyc pliku wyjsciowego");

        for (int t = 0; t < z; t++) {
            int n, k;
            cin >> n >> k;
            if (n <= 0 || k <= 0)
                throw invalid_argument("n i k musza byc dodatnie");

            // Dynamiczna alokacja tablic
            int* weights = new int[k];
            int* chosen  = new int[k];

            // Wczytanie wag
            for (int i = 0; i < k; i++) {
                cin >> weights[i];
                if (weights[i] <= 0)
                    throw invalid_argument("Wagi musza byc dodatnie");
            }

            int chosenCount = 0;
            bool found = f_findSubset(weights, k, n, 0, chosen, chosenCount);

            // Zapis do pliku w wymaganym formacie
            if (found) {
                out << n << " =";
                for (int i = 0; i < chosenCount; i++) {
                    out << " " << weights[chosen[i]];
                }
                out << "\n";
            } else {
                out << "BRAK\n";
            }

            delete[] weights;
            delete[] chosen;
        }

        out.close();
    }
    catch (const exception& e) {
        cerr << "Blad: " << e.what() << endl;
        return 1;
    }

    return 0;
}
