#ifndef word_HEADER
#define word_HEADER


#include <stdio.h>
#include <string>
using namespace std;


#define word_rotl(x, s) (((x) << s) | ((x) >> (32 - s)))
#define word_rotr(x, s) (((x) >> s) | ((x) << (32 - s)))


class Word {

    private :
        string name;
        bool lock_bool;
        unsigned int word;
        
    protected :
        unsigned int mask;

    public :
        Word ();
        Word (string name);
        Word (string name, unsigned int word);
        Word (unsigned int word, unsigned int mask);

        void         s_word (unsigned int word);
        void         s_mask (unsigned int mask);
        
        unsigned int g_word ();
        unsigned int g_mask ();
        std::string  g_name ();
        
        int mask_count ();
        
        Word operator&= (const Word & a);
        Word operator|= (const Word & a);
        Word operator^= (const Word & a);
        Word operator+= (const Word & a);
        Word operator-= (const Word & a);
        Word operator&  (const Word & a);
        Word operator|  (const Word & a);
        Word operator^  (const Word & a);
        Word operator+  (const Word & a);
        Word operator-  (const Word & a);
        Word operator~  ();
        Word operator=  (const Word & a);
        
        Word rotr (int bits);
        Word rotl (int bits);
        
        /**
        * Takes bits from a and sets those bits in this word, maintaining the
        * bits that are already set in this word
        */
        void take_bits (Word a);
        
        std::string bit_string ();

};



#endif
