# Metody Programowania — Laboratoria

Zbiór projektów wykonanych w ramach przedmiotu **Metody Programowania**
(Informatyka, rok I, semestr II) — Politechnika Krakowska, Katedra Automatyki i Informatyki.

## Autor

**Mróz Bartłomiej**

## Język i narzędzia

- **Język:** C++ (standard C++17)
- **IDE:** CLion (JetBrains)
- **Build system:** CMake

## Struktura projektów

Każde laboratorium znajduje się w osobnym folderze. Każdy projekt jest podzielony
tematycznie na biblioteki (`.h` + `.cpp`) oraz plik główny z funkcją `main`.

## Spis laboratoriów

| Lab | Temat | Główne pojęcia |
|-----|-------|----------------|
| **LAB_2** | Dopasowanie modelu silnika | MSE, generowanie SVG |
| **LAB_3_MAIN** | Wyszukiwanie w tablicach | Wyszukiwanie binarne, interpolacyjne, usuwanie duplikatów |
| **LAB_3_ADD** | Generowanie kombinatoryczne | Kod Graya, k-elementowe podzbiory, partycje liczby |
| **LAB_4_HEAP** | Stosy | Implementacja na tablicy, liście jednokierunkowej, `std::stack` |
| **LAB_4_ONP** | Notacja postfixowa | Konwersja INF ↔ ONP, algorytm shunting-yard |
| **LAB_5** | Grafy | Macierz incydencji, lista incydencji, lista jednokierunkowa |
| **LAB_6** | Wyszukiwanie w tablicy 2D | Algorytm Saddleback Search O(n+m), rekurencja vs iteracja |
| **LAB_7** | Generatory liczb pseudolosowych | Liniowa metoda kongruencyjna (LCG), addytywna metoda (lagged Fibonacci) |
| **LAB_8** | Problem plecakowy | Programowanie dynamiczne, rekurencja |
| **LAB_9** | Problem plecakowy 0-1 | Backtracking z branch & bound |
| **LAB_10** | Kompresja danych | Algorytm Huffmana, kolejka priorytetowa, kody prefiksowe |

## Konwencje kodowania

W projektach stosowane są spójne zasady:

- **Komentarze Doxygen** na początku każdego pliku (`@file`, `@brief`)
- **Komentarze w języku polskim** przy bardziej skomplikowanych fragmentach
- **Zmienne w języku angielskim**, prefix `f_` dla funkcji
- **Dynamiczna alokacja pamięci** (`new` / `delete`)
- **Obsługa wyjątków** (`try` / `catch` / `throw`)
- **Podział na biblioteki tematyczne** (`Lib*.h` + `Lib*.cpp`)
- **Wejście / wyjście przez pliki** (`cin` czyta nazwy plików)

## Kompilacja i uruchamianie

W CLion:
1. Otwórz folder konkretnego laboratorium
2. **Run → Edit Configurations** — ustaw `Working directory` na folder projektu
3. Run ▶
4. W konsoli podaj nazwy plików wejściowych / wyjściowych
5. Wynik znajdziesz w pliku wyjściowym

## Licencja

Projekt edukacyjny — kod może być wykorzystywany jako materiał dydaktyczny
i punkt odniesienia, ale nie do bezpośredniego oddawania jako własne rozwiązanie.

---

*Politechnika Krakowska im. Tadeusza Kościuszki*
*Katedra Automatyki i Informatyki (E-1)*
*rok akademicki 2025/2026*