/**
 * @file LibFiles.h
 * @brief Deklaracje funkcji do obsługi plików.
 */

#ifndef LIBFILES_H
#define LIBFILES_H

#include <fstream>
#include <string>

void f_readInput(const std::string& filename, int& numSets,
                 int**& data, int*& sizes, int**& queries, int*& querySizes);

#endif
