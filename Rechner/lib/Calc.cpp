
#include "Calc.hpp"
#include <stdexcept>


auto calc(int x, int y, char op) -> int {
    switch (op){
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': 
            if (y == 0) throw std::invalid_argument("Error: Division duch 0");
            return x / y;
        case '%':
            if (y == 0) throw std::invalid_argument("Error: Modulo mit 0, wa willsch?");
            return x % y;
        
        default:
            throw std::invalid_argument{"unknown operator"};
    }
}