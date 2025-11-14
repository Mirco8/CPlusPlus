#include "Word.hpp"
#include <iostream>
#include <sstream>

auto main() -> int {
    // Demonstrate Word class functionality
    std::cout << "=== Word Class Demo ===" << std::endl;
    
    // Test creating words from strings
    try {
        Word w1{"Hello"};
        Word w2{"WORLD"};
        std::cout << "w1: " << w1 << std::endl;
        std::cout << "w2: " << w2 << std::endl;
        
        // Test case-insensitive comparison
        Word w3{"hello"};
        std::cout << "\"Hello\" == \"hello\": " << (w1 == w3 ? "true" : "false") << std::endl;
        std::cout << "\"Hello\" < \"WORLD\": " << (w1 < w2 ? "true" : "false") << std::endl;
        
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // Test input from stream with special characters
    std::cout << "\n=== Input Stream Test ===" << std::endl;
    std::istringstream input{"compl33tely ~ weird !!?!! 4matted in_put"};
    Word w;
    while (input >> w) {
        std::cout << "Read word: " << w << std::endl;
    }
    
    return 0;
}
