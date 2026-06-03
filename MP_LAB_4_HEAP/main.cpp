/**
 * @file main.cpp
 * @brief Demonstracja 3 implementacji stosu: tablica dynamiczna, lista, std::stack.
 *        Wczytuje n liczb z pliku, wykonuje na każdym stosie te same operacje,
 *        zapisuje wynik do pliku wyjściowego.
 */

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "LibStackArray.h"
#include "LibStackList.h"
using namespace std;

int main()
{
    string inputFile, outputFile;
    cin >> inputFile >> outputFile;

    ifstream file(inputFile);
    if (!file.is_open()) return 1;
    int n;
    file >> n;
    if (n <= 0) return 1;

    int* values = new int[n];
    for (int i = 0; i < n; i++)
        file >> values[i];
    file.close();

    ofstream out(outputFile);

    // ===== A) Tablica dynamiczna =====
    out << "=== A) Tablica dynamiczna ===" << endl;
    StackArray sa = f_arrayCreate(4);
    out << "Pusty? " << (f_arrayIsEmpty(sa) ? "tak" : "nie") << endl;
    for (int i = 0; i < n; i++) {
        f_arrayPush(sa, values[i]);
        out << "Push " << values[i] << " -> rozmiar=" << f_arraySize(sa)
            << ", szczyt=" << f_arrayTop(sa) << endl;
    }
    out << "Pusty? " << (f_arrayIsEmpty(sa) ? "tak" : "nie") << endl;
    while (!f_arrayIsEmpty(sa)) {
        out << "Pop " << f_arrayTop(sa) << endl;
        f_arrayPop(sa);
    }
    f_arrayDelete(sa);

    // ===== B) Lista jednokierunkowa =====
    out << endl << "=== B) Lista jednokierunkowa ===" << endl;
    StackList sl = f_listCreate();
    out << "Pusty? " << (f_listIsEmpty(sl) ? "tak" : "nie") << endl;
    for (int i = 0; i < n; i++) {
        f_listPush(sl, values[i]);
        out << "Push " << values[i] << " -> rozmiar=" << f_listSize(sl)
            << ", szczyt=" << f_listTop(sl) << endl;
    }
    out << "Pusty? " << (f_listIsEmpty(sl) ? "tak" : "nie") << endl;
    while (!f_listIsEmpty(sl)) {
        out << "Pop " << f_listTop(sl) << endl;
        f_listPop(sl);
    }
    f_listDelete(sl);

    // ===== C) std::stack =====
    out << endl << "=== C) std::stack ===" << endl;
    stack<int> ss;
    out << "Pusty? " << (ss.empty() ? "tak" : "nie") << endl;
    for (int i = 0; i < n; i++) {
        ss.push(values[i]);
        out << "Push " << values[i] << " -> rozmiar=" << ss.size()
            << ", szczyt=" << ss.top() << endl;
    }
    out << "Pusty? " << (ss.empty() ? "tak" : "nie") << endl;
    while (!ss.empty()) {
        out << "Pop " << ss.top() << endl;
        ss.pop();
    }

    out.close();
    delete[] values;
    return 0;
}
