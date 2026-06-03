/**
 * @file main.cpp
 * @brief Program konwersji INF <-> ONP. Wczytuje nazwy plików z cin,
 *        pierwsza linia pliku to liczba wyrażeń n, dalej n linii w formacie:
 *        "INF: <wyrazenie>" lub "ONP: <wyrazenie>".
 *        Dla każdej linii wypisuje konwersję w drugą stronę.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LibONP.h"
using namespace std;

int main()
{
    string inputFile, outputFile;
    cin >> inputFile >> outputFile;

    ifstream in(inputFile);
    if (!in.is_open()) return 1;

    int n;
    in >> n;
    in.ignore(); // pomiń znak nowej linii po n
    if (n <= 0) return 1;

    ofstream out(outputFile);

    for (int i = 0; i < n; i++) {
        string line;
        getline(in, line);

        // Szukamy prefiksu "INF:" lub "ONP:"
        if (line.rfind("INF:", 0) == 0) {
            string body = line.substr(4);
            string onp  = f_infToOnp(body);
            out << "INF: " << f_filter(body) << endl;
            out << "ONP: " << onp << endl;
        }
        else if (line.rfind("ONP:", 0) == 0) {
            string body = line.substr(4);
            string inf  = f_onpToInf(body);
            out << "ONP: " << f_filter(body) << endl;
            out << "INF: " << inf << endl;
        }
        else {
            out << "error: nieznany format linii" << endl;
        }
        out << endl;
    }

    in.close();
    out.close();
    return 0;
}
