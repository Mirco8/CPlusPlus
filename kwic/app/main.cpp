#include "Kwic.hpp"
#include "Word.hpp"
#include <iostream>
#include <sstream>

auto main() -> int
{
    std::cout << "=== KWIC - Keyword in Context ===" << std::endl;
    std::cout << "Enter lines of text (Ctrl+D to finish):" << std::endl;
    std::cout << std::endl;

    // Process KWIC from standard input
    text::kwic(std::cin, std::cout);

    return 0;
}
