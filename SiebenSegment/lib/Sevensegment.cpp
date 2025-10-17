#include "Sevensegment.hpp"

#include <ostream>
#include <array>
#include <string>
#include <stdexcept>

namespace {
using Glyph = std::array<std::string, 5>;

inline void appendGlyphRowWise(const Glyph& g,
                               std::array<std::string,5>& rows,
                               bool addSpaceAfter)
{
    for (int r = 0; r < 5; ++r) {
        rows[static_cast<std::size_t>(r)] += g[static_cast<std::size_t>(r)];
        if (addSpaceAfter) rows[static_cast<std::size_t>(r)] += ' ';
    }
}

// Buchstaben für "Error" im gleichen 3x3-Segment-Stil
const Glyph GLYPH_E { " - ", "|  ", " - ", "|  ", " - " };
const Glyph GLYPH_r { "   ", "|  ", " - ", "|  ", "   " };
const Glyph GLYPH_o { "   ", "   ", " - ", "| |", " - " };
}

std::array<std::array<std::string, 5>, 10> const digits{
{
    {
    " - ",
    "| |",
    "   ",
    "| |",
    " - "
    },
    {
    "   ",
    "  |",
    "   ",
    "  |",
    "   "
    },
    {
    " - ",
    "  |",
    " - ",
    "|  ",
    " - "
    },
    {
    " - ",
    "  |",
    " - ",
    "  |",
    " - "
    },
    {
    "   ",
    "| |",
    " - ",
    "  |",
    "   "
    },
    {
    " - ",
    "|  ",
    " - ",
    "  |",
    " - "
    },
    {
    " - ",
    "|  ",
    " - ",
    "| |",
    " - "
    },
    {
    " - ",
    "  |",
    "   ",
    "  |",
    "   "
    },
    {
    " - ",
    "| |",
    " - ",
    "| |",
    " - "
    },
    {
    " - ",
    "| |",
    " - ",
    "  |",
    " - "
    },

}

};

auto printLargeDigit(int i, std::ostream& output) -> void {
    if (i < 0 || i > 9) {
        throw std::invalid_argument{"printLargeDigit: invalid digit"};
    }

    for (auto const& line : digits[static_cast<std::size_t>(i)]) {
        output << line << '\n';
    }
}

auto printLargeNumber(int i, std::ostream& output) -> void {
    static const std::array<std::string, 5> minus{
        "   ",
        "   ",
        " - ",
        "   ",
        "   "
    };

    std::string s = std::to_string(i);
    std::array<std::string, 5> rows{};

    for (std::size_t idx = 0; idx < s.size(); ++idx) {
        const char c = s[idx];
        const std::array<std::string, 5>* glyph = nullptr;

        if (c == '-') {
            glyph = &minus;
        } else if (c >= '0' && c <= '9') {
            glyph = &digits[static_cast<std::size_t>(c - '0')];
        } else {
            throw std::invalid_argument{"printLargeNumber: invalid character"};
        }

        for (int r = 0; r < 5; ++r) {
            rows[r] += (*glyph)[static_cast<std::size_t>(r)];
            if (idx + 1 < s.size()) rows[r] += ' '; // genau ein Leerzeichen zwischen Ziffern
        }
    }

    for (auto const& line : rows) {
        output << line << '\n';
    }
}

auto printLargeError(std::ostream& out) -> void {
    std::array<std::string, 5> rows{};
    const std::array<Glyph,5> letters{ GLYPH_E, GLYPH_r, GLYPH_r, GLYPH_o, GLYPH_r };
    for (std::size_t i = 0; i < letters.size(); ++i) {
        appendGlyphRowWise(letters[i], rows, i + 1 < letters.size());
    }
    for (auto const& line : rows) out << line << '\n';
}