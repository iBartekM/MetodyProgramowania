// gen_test.cpp - Generator danych testowych dla wyszukiwania binarnego.

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <random>
#include <vector>

int main() {
    const int kNumElements = 1000;
    const int kNumQueries = 100;
    const int64_t kMinValue = -(1LL << 48);
    const int64_t kMaxValue = (1LL << 48);
    const unsigned int kSeed = 42;

    std::mt19937_64 rng(kSeed);
    std::uniform_int_distribution<int64_t> dist(kMinValue, kMaxValue);

    // Generowanie losowych elementow tablicy
    std::vector<int64_t> data(kNumElements);
    for (int i = 0; i < kNumElements; ++i) {
        data[i] = dist(rng);
    }

    // Sortowanie niemalejaco
    std::sort(data.begin(), data.end());

    // Generowanie zapytan - mieszanka istniejacych i nieistniejacych wartosci
    std::vector<int64_t> queries(kNumQueries);
    std::uniform_int_distribution<int> index_dist(0, kNumElements - 1);

    for (int i = 0; i < kNumQueries; ++i) {
        if (i % 2 == 0) {
            // Wartosc istniejaca w tablicy
            queries[i] = data[index_dist(rng)];
        } else {
            // Wartosc losowa (moze nie istniec w tablicy)
            queries[i] = dist(rng);
        }
    }

    // Zapis do pliku
    std::ofstream out("in_test.txt");
    out << 1 << "\n";           // liczba zestawow danych
    out << kNumElements << "\n"; // liczba elementow

    for (int i = 0; i < kNumElements; ++i) {
        out << data[i];
        if (i + 1 < kNumElements) out << " ";
    }
    out << "\n";

    out << kNumQueries << "\n"; // liczba zapytan

    for (int i = 0; i < kNumQueries; ++i) {
        out << queries[i];
        if (i + 1 < kNumQueries) out << " ";
    }
    out << "\n";

    out.close();
    return 0;
}
