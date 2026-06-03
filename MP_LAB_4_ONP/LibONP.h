/**
 * @file LibONP.h
 * @brief Konwersja INF <-> ONP (Odwrotna Notacja Polska).
 *        Operatory: = < > + - * / % ^ ~ (~ to operator jednoargumentowy).
 *        Operandy: pojedyncze małe litery a-z. Dozwolone nawiasy ( ).
 */

#ifndef LIBONP_H
#define LIBONP_H

#include <string>

// Czyści wejście — usuwa wszystko poza dozwolonymi znakami.
std::string f_filter(const std::string& s);

// Sprawdza, czy znak jest operatorem.
bool f_isOperator(char c);

// Priorytet operatora (im wyżej, tym mocniej wiąże).
int f_priority(char c);

// Czy operator jest prawostronnie łączny.
bool f_isRightAssoc(char c);

// Konwersja INF -> ONP. Zwraca "error" przy błędnym wyrażeniu.
std::string f_infToOnp(const std::string& inf);

// Konwersja ONP -> INF (z minimalną liczbą nawiasów). Zwraca "error" przy błędzie.
std::string f_onpToInf(const std::string& onp);

#endif
