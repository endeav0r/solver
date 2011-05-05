#include <iostream>
#include "word.hpp"

void test (Word a, Word b) {
    Word c;
    std::cout << "a     " << a.bit_string() << "\n";
    std::cout << "b     " << b.bit_string() << "\n";
    c = a + b;
    std::cout << "a + b " << c.bit_string() << "\n";
    c = a - b;
    std::cout << "a - b " << c.bit_string() << "\n";
    c = a & b;
    std::cout << "a & b " << c.bit_string() << "\n";
    c = a | b;
    std::cout << "a | b " << c.bit_string() << "\n";
}

int main () {
    test(Word(0x56789abc, 0xffffffff), Word(0x55555555, 0xffffffff));
    test(Word(0x56789abc, 0x78787878), Word(0x55555555, 0xaaaaaaaa));
    test(Word(0x2e603914, 0xffffffff), Word(0xc1122306, 0xe1db3f16));
    
    
    
    return 0;
}
