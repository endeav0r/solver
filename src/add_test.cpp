#include <iostream>

#include "word.hpp"
#include "add.hpp"

int main () {
    Word a(0x23456789, 0x98765432);
    Word b(0x89abcdef, 0x43287698);
    Word c;
    
    Add op;
    op.add_operand(&a);
    op.add_operand(&b);
    c = op.best_adder();
    
    std::cout << a.bit_string() << "\n";
    std::cout << b.bit_string() << "\n";
    std::cout << c.bit_string() << "\n";
    
    return 0;
}
