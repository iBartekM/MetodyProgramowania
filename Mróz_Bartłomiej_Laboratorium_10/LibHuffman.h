// Mróz Bartłomiej

/**
 * @file LibHuffman.h
 * @brief Algorytm Huffmana — konstruowanie optymalnego binarnego kodu prefixowego.
 *
 * IDEA: Symbole rzadko występujące dostają DŁUŻSZE kody, symbole częste —
 * KRÓTSZE. Dzięki temu średnia długość kodu jest minimalna.
 *
 * Algorytm:
 *   1. Dla każdego symbolu utwórz drzewo z jednym węzłem (liściem).
 *   2. Dopóki zostało więcej niż jedno drzewo:
 *        - weź dwa o najmniejszych wagach (kolejka priorytetowa)
 *        - utwórz nowy węzeł, którego dziećmi są te dwa drzewa
 *        - waga = suma wag
 *   3. Z każdą lewą krawędzią skojarz 0, z prawą skojarz 1.
 *   4. Kod symbolu = sekwencja 0/1 od korzenia do liścia.
 *
 * KLUCZOWA WŁAŚCIWOŚĆ: żaden kod nie jest prefiksem innego (kody prefixowe).
 * Dzięki temu dekodowanie jest jednoznaczne.
 */

#ifndef LIBHUFFMAN_H
#define LIBHUFFMAN_H

#include <string>
#include <fstream>

// Węzeł drzewa Huffmana
struct HuffNode {
    char   symbol;   // znak (dla liścia) — '\0' dla węzła wewnętrznego
    double weight;   // częstotliwość lub prawdopodobieństwo
    HuffNode* left;
    HuffNode* right;
    bool   isLeaf;
};

// Para (symbol, kod, waga) — wynik dla każdego symbolu
struct HuffCode {
    char symbol;
    double weight;
    std::string code;
};

// Buduje drzewo Huffmana z tablic symboli i wag.
// Zwraca wskaźnik do korzenia (zwolnij przez f_deleteTree).
HuffNode* f_buildTree(const char* symbols, const double* weights, int n);

// Rekurencyjnie generuje kody i wypełnia tablicę 'out'.
//   prefix    — aktualny ciąg 0/1 (akumulowany w rekurencji)
//   out       — tablica wynikowych kodów (zaalokowana przez wywołującego)
//   count     — bieżąca liczba kodów (referencja, modyfikowana)
void f_generateCodes(HuffNode* node, const std::string& prefix,
                     HuffCode* out, int& count);

// Zwalnia całe drzewo Huffmana
void f_deleteTree(HuffNode* node);

// Wypisuje drzewo wcięciami (do pliku, dla wizualizacji)
void f_printTree(std::ofstream& out, HuffNode* node, int depth);

#endif
