#include "Sevensegment.hpp"

#include <ostream>
#include <array>

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