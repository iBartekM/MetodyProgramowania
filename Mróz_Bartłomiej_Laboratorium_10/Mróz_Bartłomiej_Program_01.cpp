// Mróz Bartłomiej

/**
 * @file Mróz_Bartłomiej_Program_01.cpp
 * @brief Algorytm Huffmana — generowanie optymalnego binarnego kodu prefixowego.
 *
 * Wejście (cin):
 *   inputFile   — nazwa pliku z danymi
 *   outputFile  — nazwa pliku wynikowego
 *
 * Format pliku wejściowego:
 *   Linia 1:        n              (liczba symboli)
 *   Linie 2..n+1:   symbol waga    (znak + częstotliwość/prawdopodobieństwo)
 *
 * Plik wyjściowy zawiera:
 *   - Tabelę symboli i wag (dane wejściowe)
 *   - Wizualizację drzewa Huffmana
 *   - Tabelę wynikowych kodów
 *   - Statystyki: średnia długość kodu, oszczędność, entropia
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "LibHuffman.h"
#include "HuffmanException.h"

using namespace std;

int main()
{
    try {
        // Wczytanie nazw plików
        string inputFile, outputFile;
        cin >> inputFile >> outputFile;

        // Otwarcie pliku wejściowego
        ifstream in(inputFile);
        if (!in.is_open())
            throw HuffmanException("Nie mozna otworzyc pliku wejsciowego");

        int n;
        if (!(in >> n))
            throw HuffmanException("Brak liczby symboli w pliku");
        if (n <= 0)
            throw HuffmanException("Liczba symboli musi byc dodatnia");

        // Dynamiczna alokacja tablic
        char*   symbols = new char[n];
        double* weights = new double[n];
        double  totalWeight = 0;

        for (int i = 0; i < n; i++) {
            in >> symbols[i] >> weights[i];
            if (in.fail())
                throw HuffmanException("Bledny format pliku wejsciowego");
            if (weights[i] < 0)
                throw HuffmanException("Waga ujemna niedozwolona");
            totalWeight += weights[i];
        }
        in.close();

        // Otwarcie pliku wyjściowego
        ofstream out(outputFile);
        if (!out.is_open())
            throw HuffmanException("Nie mozna otworzyc pliku wyjsciowego");

        out << "=== ALGORYTM HUFFMANA ===" << endl;
        out << "Liczba symboli: " << n << endl;
        out << "Suma wag: " << totalWeight << endl << endl;

        // Wypisanie danych wejściowych
        out << "Dane wejsciowe:" << endl;
        out << "  Symbol | Waga" << endl;
        out << "  -------+----------" << endl;
        for (int i = 0; i < n; i++) {
            out << "    " << symbols[i] << "    | " << weights[i] << endl;
        }
        out << endl;

        // Budowa drzewa Huffmana
        HuffNode* root = f_buildTree(symbols, weights, n);

        // Wizualizacja drzewa (obrócona — korzeń po lewej)
        out << "Drzewo Huffmana (obrocone, korzen po lewej):" << endl;
        f_printTree(out, root, 0);
        out << endl;

        // Generowanie kodów
        HuffCode* codes = new HuffCode[n];
        int codeCount = 0;
        f_generateCodes(root, "", codes, codeCount);

        // Tabela wynikowych kodów
        out << "Wynikowe kody Huffmana:" << endl;
        out << "  Symbol | Waga   | Kod          | Dlugosc" << endl;
        out << "  -------+--------+--------------+--------" << endl;
        for (int i = 0; i < codeCount; i++) {
            out << "    " << codes[i].symbol
                << "    | " << setw(6) << codes[i].weight
                << " | " << setw(12) << codes[i].code
                << " | " << codes[i].code.length() << endl;
        }
        out << endl;

        // Statystyki kompresji
        out << "Statystyki:" << endl;

        // Średnia długość kodu Huffmana = Σ (p_i × dlugosc_i)
        double avgLength = 0;
        for (int i = 0; i < codeCount; i++) {
            double p = codes[i].weight / totalWeight;
            avgLength += p * codes[i].code.length();
        }
        out << "  Srednia dlugosc kodu Huffmana: " << fixed << setprecision(3)
            << avgLength << " bitow/symbol" << endl;

        // Entropia Shannona (teoretyczne minimum)
        double entropy = 0;
        for (int i = 0; i < codeCount; i++) {
            double p = codes[i].weight / totalWeight;
            if (p > 0) entropy -= p * log2(p);
        }
        out << "  Entropia Shannona:             " << fixed << setprecision(3)
            << entropy << " bitow/symbol" << endl;

        // Wydajność: jak blisko entropii jesteśmy
        double efficiency = (entropy / avgLength) * 100;
        out << "  Wydajnosc kodowania:           " << fixed << setprecision(2)
            << efficiency << " %" << endl;

        // Porównanie z kodem stałym (np. 8-bit ASCII)
        double fixedBitsPerSymbol = 8.0;
        double compressionRatio = (avgLength / fixedBitsPerSymbol) * 100;
        out << "  Stopien kompresji (vs 8-bit):  " << fixed << setprecision(2)
            << compressionRatio << " %" << endl;
        out << "  Oszczednosc (vs 8-bit):        " << fixed << setprecision(2)
            << (100 - compressionRatio) << " %" << endl;

        out.close();

        // Zwolnienie pamięci
        f_deleteTree(root);
        delete[] symbols;
        delete[] weights;
        delete[] codes;
    }
    catch (const HuffmanException& e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cerr << "[exception] " << e.what() << endl;
        return 1;
    }

    return 0;
}
