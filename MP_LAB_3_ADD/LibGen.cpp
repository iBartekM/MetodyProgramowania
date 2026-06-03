/**
 * @file LibGen.cpp
 * @brief Definicje funkcji generujących podzbiory i podziały liczb.
 */

#include "LibGen.h"

// Wypisuje tablicę B[1..n] do pliku
static void f_writeB(int* B, int n, std::ofstream& out)
{
    for (int i = 1; i <= n; i++) {
        out << B[i];
        if (i < n) out << " ";
    }
    out << "\n";
}

// Wypisuje tablicę A[1..k] do pliku
static void f_writeA(int* A, int k, std::ofstream& out)
{
    for (int i = 1; i <= k; i++) {
        out << A[i];
        if (i < k) out << " ";
    }
    out << "\n";
}

// Program 01 — wszystkie podzbiory zbioru n-elementowego
// Algorytm generuje kolejne podzbiory zmieniając jedną pozycję na raz (kod Graya)
void f_allSubsets(int n, std::ofstream& out)
{
    int* B = new int[n + 1];
    for (int i = 1; i <= n; i++)
        B[i] = 0;

    int i = 0, p, j;
    do {
        f_writeB(B, n, out);
        i++;
        p = 1;
        j = i;
        // Szukamy pozycji do zmiany — dzielimy j przez 2 aż będzie nieparzyste
        while (j % 2 == 0) {
            j = j / 2;
            p++;
        }
        // Zmieniamy bit na pozycji p (0→1 lub 1→0)
        if (p <= n)
            B[p] = 1 - B[p];
    } while (p <= n);

    delete[] B;
}

// Program 02 — k-elementowe podzbiory {1,...,n} w porządku leksykograficznym
void f_kSubsets(int n, int k, std::ofstream& out)
{
    int* A = new int[k + 1];
    // Pierwszy podzbiór: {1, 2, ..., k}
    for (int i = 1; i <= k; i++)
        A[i] = i;

    int p = k;
    while (p >= 1) {
        f_writeA(A, k, out);
        if (A[k] == n)
            p--;
        else
            p = k;
        // Uzupełnij podzbiór od pozycji p kolejnymi liczbami
        if (p >= 1)
            for (int i = k; i >= p; i--)
                A[i] = A[p] + i - p + 1;
    }

    delete[] A;
}

// Program 03 — podziały liczby n w odwrotnym porządku leksykograficznym
// S[i] = wartość składnika, R[i] = ile razy występuje, d = liczba różnych składników
void f_partitions(int n, std::ofstream& out)
{
    int* S = new int[n + 1];
    int* R = new int[n + 1];

    S[1] = n;
    R[1] = 1;
    int d = 1;

    // Funkcja wypisująca podział
    auto writePart = [&]() {
        bool first = true;
        for (int i = 1; i <= d; i++)
            for (int j = 0; j < R[i]; j++) {
                if (!first) out << "+";
                out << S[i];
                first = false;
            }
        out << "\n";
    };

    writePart();

    while (S[1] > 1) {
        int sum = 0;
        // Usuń składniki równe 1
        if (S[d] == 1) {
            sum += R[d];
            d--;
        }
        sum += S[d];
        R[d]--;
        int l = S[d] - 1;
        if (R[d] > 0) d++;
        S[d] = l;
        R[d] = sum / l;
        l = sum % l;
        // Dodaj ostatni składnik równy reszcie
        if (l != 0) {
            d++;
            S[d] = l;
            R[d] = 1;
        }
        writePart();
    }

    delete[] S;
    delete[] R;
}
