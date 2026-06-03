/**
 * @file LibONP.cpp
 * @brief Implementacja konwersji INF <-> ONP algorytmem stacji rozrządowej (shunting-yard).
 */

#include "LibONP.h"
#include <stack>

std::string f_filter(const std::string& s)
{
    // Zostawiamy tylko: a-z, nawiasy i operatory
    std::string out;
    for (char c : s) {
        bool letter = (c >= 'a' && c <= 'z');
        bool paren  = (c == '(' || c == ')');
        bool op     = f_isOperator(c);
        if (letter || paren || op) out += c;
    }
    return out;
}

bool f_isOperator(char c)
{
    return c == '=' || c == '<' || c == '>' ||
           c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^' || c == '~';
}

int f_priority(char c)
{
    // Im większa liczba, tym mocniej wiąże
    if (c == '=') return 0;
    if (c == '<' || c == '>') return 1;
    if (c == '+' || c == '-') return 2;
    if (c == '*' || c == '/' || c == '%') return 3;
    if (c == '^') return 4;
    if (c == '~') return 5; // unarny
    return -1;
}

bool f_isRightAssoc(char c)
{
    // Prawostronnie łączne: =, ^, ~
    return c == '=' || c == '^' || c == '~';
}

// ===== INF -> ONP (algorytm stacji rozrządowej) =====
std::string f_infToOnp(const std::string& infRaw)
{
    std::string inf = f_filter(infRaw);
    std::string out;
    std::stack<char> ops;

    // expectOperand = true gdy spodziewamy się operandu (na początku, po '(' lub po operatorze)
    bool expectOperand = true;

    for (size_t i = 0; i < inf.size(); i++) {
        char c = inf[i];

        if (c >= 'a' && c <= 'z') {
            // Operand
            if (!expectOperand) return "error"; // dwa operandy obok siebie
            out += c;
            expectOperand = false;
        }
        else if (c == '(') {
            if (!expectOperand) return "error";
            ops.push(c);
        }
        else if (c == ')') {
            if (expectOperand) return "error";
            // Wyrzucamy ze stosu aż napotkamy '('
            while (!ops.empty() && ops.top() != '(') {
                out += ops.top();
                ops.pop();
            }
            if (ops.empty()) return "error"; // brak '('
            ops.pop(); // usuwamy '('
            expectOperand = false;
        }
        else if (c == '~') {
            // ~ jest tylko unarny — musi pojawić się gdy oczekujemy operandu
            if (!expectOperand) return "error";
            ops.push(c);
            // Po ~ nadal oczekujemy operandu
        }
        else if (f_isOperator(c)) {
            // Operator dwuargumentowy
            if (expectOperand) return "error"; // brak lewego operandu
            int p = f_priority(c);
            // Zdejmujemy operatory o priorytecie wyższym lub (równym i lewostronnie łącznym)
            while (!ops.empty() && ops.top() != '(') {
                int pt = f_priority(ops.top());
                if (pt > p || (pt == p && !f_isRightAssoc(c))) {
                    out += ops.top();
                    ops.pop();
                } else break;
            }
            ops.push(c);
            expectOperand = true;
        }
        else {
            return "error";
        }
    }

    if (expectOperand) return "error"; // wyrażenie kończy się operatorem

    // Wyrzucamy resztę ze stosu
    while (!ops.empty()) {
        if (ops.top() == '(') return "error"; // niedomknięty nawias
        out += ops.top();
        ops.pop();
    }

    return out;
}

// ===== ONP -> INF (z minimalną liczbą nawiasów) =====
// Pomocnicza struktura: trzymamy łańcuch + priorytet operatora głównego
struct Expr {
    std::string text;
    int prio; // priorytet głównego operatora; 6 = operand pojedynczy (atom)
};

std::string f_onpToInf(const std::string& onpRaw)
{
    std::string onp = f_filter(onpRaw);
    std::stack<Expr> st;

    for (char c : onp) {
        if (c >= 'a' && c <= 'z') {
            // Operand atomowy
            st.push({ std::string(1, c), 6 });
        }
        else if (c == '~') {
            // Unarny — bierze 1 element ze stosu
            if (st.empty()) return "error";
            Expr e = st.top(); st.pop();
            // Operand ~ wymaga nawiasów jeśli jego priorytet < priorytet ~
            std::string inner = (e.prio < 5) ? "(" + e.text + ")" : e.text;
            st.push({ "~" + inner, 5 });
        }
        else if (f_isOperator(c)) {
            // Dwuargumentowy — bierze 2 elementy
            if (st.size() < 2) return "error";
            Expr right = st.top(); st.pop();
            Expr left  = st.top(); st.pop();
            int p = f_priority(c);
            bool rightAssoc = f_isRightAssoc(c);

            // Lewy operand: nawiasy jeśli pl < p LUB (pl == p i operator prawostronnie łączny)
            std::string ls = (left.prio < p || (left.prio == p && rightAssoc))
                             ? "(" + left.text + ")" : left.text;
            // Prawy operand: nawiasy jeśli pr <= p (zawsze przy równym priorytecie)
            std::string rs = (right.prio <= p)
                             ? "(" + right.text + ")" : right.text;

            st.push({ ls + c + rs, p });
        }
        else {
            return "error";
        }
    }

    if (st.size() != 1) return "error";
    return st.top().text;
}
