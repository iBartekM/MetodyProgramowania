// Mróz Bartłomiej

/**
 * @file LibKnapsack01.cpp
 * @brief Implementacja problemu plecakowego 0-1 z algorytmem powrotów.
 */

#include "LibKnapsack01.h"
#include <iomanip>

void f_sortByRatio(Item* items, int n)
{
    // Sortowanie bąbelkowe malejąco wg ratio (p/w)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].ratio < items[j + 1].ratio) {
                Item tmp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = tmp;
            }
        }
    }
}

double f_bound(int level, int weight, int profit, const SolverState& state)
{
    // Jeśli plecak już pełny — bound = profit (nic więcej nie weźmiemy)
    if (weight >= state.W) return profit;

    double result = profit;
    int j = level;          // następny przedmiot do rozważenia (0-indeksowany)
    int totWeight = weight;

    // Greedy: dodajemy całe przedmioty dopóki się mieszczą
    while (j < state.n && totWeight + state.items[j].weight <= state.W) {
        totWeight += state.items[j].weight;
        result += state.items[j].profit;
        j++;
    }

    // Pierwszy przedmiot, który się nie mieści — bierzemy jego ułamek
    // (relaksacja ułamkowa: w ten sposób bound jest GÓRNYM oszacowaniem)
    if (j < state.n) {
        result += (state.W - totWeight) * state.items[j].ratio;
    }

    return result;
}

void f_checknode(int level, int weight, int profit, SolverState& state)
{
    state.stepCounter++;
    int currentStep = state.stepCounter;

    // Obliczenie bound dla tego węzła
    double bnd = f_bound(level, weight, profit, state);

    // Logowanie aktualnego węzła
    std::ofstream& out = *state.out;
    out << "[Krok " << currentStep << "] level=" << level
        << " weight=" << weight << " profit=" << profit
        << " bound=" << std::fixed << std::setprecision(2) << bnd;

    // Aktualizacja najlepszego rozwiązania, jeśli aktualne lepsze
    bool updated = false;
    if (weight <= state.W && profit > state.maxProfit) {
        state.maxProfit = profit;
        for (int i = 0; i < state.n; i++) state.bestSet[i] = state.include[i];
        updated = true;
    }
    if (updated) out << " [NOWY NAJLEPSZY=" << profit << "]";

    // Sprawdzenie czy węzeł jest "promising" (warto eksplorować dzieci)
    bool promising = (weight < state.W) && (bnd > state.maxProfit);

    // Liść drzewa — wszystkie decyzje podjęte
    if (level == state.n) {
        out << " LISC" << std::endl;
        return;
    }

    if (!promising) {
        out << " OBCIETE (bound <= best)" << std::endl;
        return;
    }

    out << " PROMISING" << std::endl;

    // Wariant A: WEŹ przedmiot na pozycji "level"
    if (weight + state.items[level].weight <= state.W) {
        out << "   -> bierze przedmiot id=" << state.items[level].id
            << " (p=" << state.items[level].profit
            << ", w=" << state.items[level].weight << ")" << std::endl;
        state.include[level] = true;
        f_checknode(level + 1,
                    weight + state.items[level].weight,
                    profit + state.items[level].profit,
                    state);
    }

    // Wariant B: NIE BIERZ przedmiotu na pozycji "level"
    out << "   -> pomija przedmiot id=" << state.items[level].id << std::endl;
    state.include[level] = false;
    f_checknode(level + 1, weight, profit, state);
}

void f_solveKnapsack(Item* items, int n, int W, std::ofstream& out)
{
    // Sortowanie przedmiotów malejąco wg p/w
    f_sortByRatio(items, n);

    // Zapis posortowanej listy do pliku
    out << "Przedmioty po sortowaniu (malejaco wg p/w):" << std::endl;
    out << "  i  | id | profit | weight | p/w" << std::endl;
    out << "  ---+----+--------+--------+------" << std::endl;
    for (int i = 0; i < n; i++) {
        out << "  " << (i + 1) << "  | " << items[i].id
            << "  | " << items[i].profit
            << "      | " << items[i].weight
            << "      | " << std::fixed << std::setprecision(2)
            << items[i].ratio << std::endl;
    }
    out << std::endl;

    // Inicjalizacja stanu rozwiązania
    SolverState state;
    state.n = n;
    state.W = W;
    state.maxProfit = 0;
    state.bestSet = new bool[n]();
    state.include = new bool[n]();
    state.stepCounter = 0;
    state.items = items;
    state.out = &out;

    // Uruchomienie rekurencji od korzenia drzewa (level=0, plecak pusty)
    out << "Sledzenie algorytmu:" << std::endl;
    out << "====================" << std::endl;
    f_checknode(0, 0, 0, state);
    out << std::endl;

    // Wypisanie wyniku
    out << "==============================" << std::endl;
    out << "WYNIK:" << std::endl;
    out << "Maksymalny zysk: " << state.maxProfit << std::endl;
    out << "Wybrane przedmioty (oryginalne id): ";
    int totalWeight = 0;
    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (state.bestSet[i]) {
            out << items[i].id << " ";
            totalWeight += items[i].weight;
            totalProfit += items[i].profit;
        }
    }
    out << std::endl;
    out << "Laczna waga: " << totalWeight << " (z " << W << ")" << std::endl;
    out << "Laczny zysk: " << totalProfit << std::endl;
    out << "Liczba odwiedzonych wezlow: " << state.stepCounter << std::endl;

    delete[] state.bestSet;
    delete[] state.include;
}
