#include "word.hpp"
#include <iostream>

#define F(x,y,z) ((x & y) | ((~x) & z))


void round () {
    Word a[16];
    Word b[16];
    Word c[16];
    Word d[16];
    Word M[16];
    
    M[0] = Word(0xdeadbeef, 0x00000000);
    M[1] = Word(0xbeefdead, 0x00000000);
    M[2] = Word(0xfeebdaed, 0x00000000);
    M[3] = Word(0xdaedfeeb, 0x00000000);
    
    for (int i = 4; i < 16; i++) {
        M[i] = Word(0x00000000, 0xffffffff);
    }
    
    a[0] = Word(0x00112233, 0xffffffff);
    b[0] = Word(0x44556677, 0xffffffff);
    c[0] = Word(0x8899aabb, 0xffffffff);
    d[0] = Word(0xccddeeff, 0xffffffff);
    a[4] = Word(0x292d98b3, 0xffffffff);
    b[4] = Word(0x61db67c8, 0xffffffff);
    c[4] = Word(0x48facff4, 0xffffffff);
    d[4] = Word(0xfe2b53ce, 0xffffffff);


    for (int i = 0; i < 4; i++) {
        a[i+1] = b[i  ] + (a[i] + F(b[i  ], c[i  ], d[i  ]) + M[i*4  ]).rotl(7);
        d[i+1] = a[i+1] + (d[i] + F(a[i+1], b[i  ], c[i  ]) + M[i*4+1]).rotl(12);
        c[i+1] = d[i+1] + (c[i] + F(d[i+1], a[i+1], b[i  ]) + M[i*4+2]).rotl(17);
        b[i+1] = c[i+1] + (b[i] + F(c[i+1], d[i+1], a[i+1]) + M[i*4+3]).rotl(22);
    }
    
    for (int i = 0; i < 5; i++) {
        std::cout << "a[" << i << "] " << a[i].bit_string() << "\n";
        std::cout << "b[" << i << "] " << b[i].bit_string() << "\n";
        std::cout << "c[" << i << "] " << c[i].bit_string() << "\n";
        std::cout << "d[" << i << "] " << d[i].bit_string() << "\n";
    }
    
    for (int i = 0; i < 16; i++) {
        std::cout << "M[" << i << "] " << M[i].bit_string() << "\n";
    }
    
}


int main () {
    round();
    return 0;
}
