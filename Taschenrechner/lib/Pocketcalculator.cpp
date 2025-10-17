#include "Pocketcalculator.hpp"
#include "Calc.hpp"
#include "Sevensegment.hpp"

#include <iosfwd>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>

namespace {
constexpr std::size_t MAX_WIDTH = 8;}

static bool fitsEightWide(int value) {
    return std::to_string(value).size() <= MAX_WIDTH; // Minus zählt mit
}

static bool is_blank_line(std::string const& s) {
    for (unsigned char c : s) if (!std::isspace(c)) return false;
    return true;
}


auto pocketcalculator(std::istream &input, std::ostream &output) -> void {
    std::string line;
    while (std::getline(input, line)) {
        if (is_blank_line(line)) {
            // Leere Zeilen ignorieren (falls ihr stattdessen "Error" wollt: printLargeError(output); continue;)
            continue;
        }

        try {
            // Erwartetes Format: <int> <op> <int> (Whitespace beliebig)
            std::istringstream iss(line);
            int result = calc(iss);            // nutzt deine Calc-Variante mit Parsing & Validierung
            if (!fitsEightWide(result)) {
                printLargeError(output);       // Overflow -> "Error"
            } else {
                printLargeNumber(result, output);
            }
        } catch (...) {
            // Format falsch, unbekannter Operator, Division/Modulo durch 0, Restmüll etc.
            printLargeError(output);
        }
    }

}