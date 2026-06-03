// Mróz Bartłomiej

/**
 * @file LibAddCong.cpp
 * @brief Implementacja generatora addytywnego (lagged Fibonacci).
 */

#include "LibAddCong.h"

void f_generateAddCong(long long* output, int n, long long m,
                       int l, int k, const long long* seed)
{
    // Bufor zawiera ziarno + n wygenerowanych wartości
    // (potrzebujemy historii ostatnich k wartości żeby liczyć kolejne)
    int bufSize = n + k;
    long long* buffer = new long long[bufSize];

    // Pierwsze k miejsc bufora to ziarno
    for (int i = 0; i < k; i++) {
        buffer[i] = seed[i];
    }

    // Generujemy n nowych wartości używając wzoru: X_n = (X_{n-l} + X_{n-k}) mod m
    for (int i = k; i < bufSize; i++) {
        buffer[i] = (buffer[i - l] + buffer[i - k]) % m;
    }

    // Zwracamy n wartości WYGENEROWANYCH (bez ziarna)
    for (int i = 0; i < n; i++) {
        output[i] = buffer[k + i];
    }

    delete[] buffer;
}
