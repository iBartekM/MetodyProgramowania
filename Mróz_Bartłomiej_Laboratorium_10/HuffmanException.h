// Mróz Bartłomiej

/**
 * @file HuffmanException.h
 * @brief Własna klasa wyjątku dla algorytmu Huffmana
 *        (wymóg zadania: "Zaimplementuj własną klasę dla swoich wyjątków").
 *        Dziedziczy po std::runtime_error.
 */

#ifndef HUFFMAN_EXCEPTION_H
#define HUFFMAN_EXCEPTION_H

#include <stdexcept>
#include <string>

class HuffmanException : public std::runtime_error {
public:
    // Konstruktor — przekazuje komunikat do klasy bazowej
    explicit HuffmanException(const std::string& msg)
        : std::runtime_error("[HuffmanException] " + msg) {}
};

#endif
