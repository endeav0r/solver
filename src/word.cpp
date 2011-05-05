#include "word.hpp"


Word :: Word (unsigned int word, unsigned int mask) {
    this->name = "";
    this->word = word;
    this->mask = mask;
    this->lock_bool = false;
}


Word :: Word (string name, unsigned int word) {
    this->name = name;
    this->word = word;
    this->lock_bool = false;
    this->mask = 0x00000000;
}


Word :: Word (string name) {
    this->name = name;
    this->word = 0x00000000;
    this->lock_bool = false;
    this->mask = 0x00000000;
}


Word :: Word () {
    this->name = "";
    this->word = 0x00000000;
    this->lock_bool = false;
    this->mask = 0x00000000;
}


void Word :: s_word (unsigned int word) { this->word = word; }
void Word :: s_mask (unsigned int mask) { this->mask = mask; }
unsigned int Word :: g_word   () { return this->word & this->mask; }
unsigned int Word :: g_mask   () { return this->mask; }
std::string  Word :: g_name () { return this->name; }


int Word :: mask_count () {
    int count = 0;
    for (int bit = 0; bit < 32; bit++) {
        if ((this->mask >> bit) & 0x00000001)
            count++;
    }
    return count;
}


Word Word :: operator&= (const Word & a) {
    this->mask &= a.mask;
    this->word = this->word & a.word;
    return *this;
}


Word Word :: operator|= (const Word & a) {
    this->mask &= a.mask;
    this->word  = this->word | a.word;
    return *this;
}


Word Word :: operator^= (const Word & a) {
    this->mask &= a.mask;
    this->word = this->word ^ a.word;    
    return *this;
}


Word Word :: operator += (const Word & a) {
    unsigned int sum;
    unsigned int mask;
    unsigned int current, previous;
    int bit;
    bool flipping = false;
    int skip_flip = -1;

    sum = a.word + this->word;
    mask = 0x00000000;
    
    // first bit is a special case
    if ((a.mask & 0x00000001) && (this->mask & 0x00000001)) {
        flipping = true;
        mask = 0x00000001;
    }
    
    // these are rules for when we have 0-0 or 1-1 to initiate flipping
    // bits
    for (bit = 1; bit < 32; bit++) {
        // is mask set for both of these bits
        if ((a.mask & (1 << bit)) && (this->mask & (1 << bit))) {
            // are we already flipping
            if (flipping)
                mask |= 1 << bit;
            // we are not already flipping
            else {
                // this location is 0-0
                if (((a.word & (1 << bit)) == 0x00000000)
                    && ((this->word & (1 << bit)) == 0x00000000))
                    flipping = true;
                // this location is 1-1
                else if ((a.word & (1 << bit))
                         && (this->word & (1 << bit)))
                    flipping = true;
            }
        }
        // mask is set for one of the bits
        else if ((a.mask & (1 << bit)) || (this->mask & (1 << bit))) {
            if (a.mask & (1 << bit))
                current = (a.word     >> bit) & 0x00000001;
            else
                current = (this->word >> bit) & 0x00000001;
            // is mask set for both of the previous bits
            if ((a.mask & (1 << (bit - 1))) && (this->mask & (1 << (bit - 1)))) {
                previous =  (a.word     >> (bit - 1)) & 0x00000001;
                previous += (this->word >> (bit - 1)) & 0x00000001;
                // previous is 0-0 and current is 0, keep flipping
                if ((previous == 0) && (current == 0)) {
                    skip_flip = 0;
                    flipping = true;
                }
                // previous is 1-1 and current is 1, keep flipping
                else if ((previous == 2) && (current == 1)) {
                    skip_flip = 1;
                    flipping = true;
                }
                // otherwise, stop flipping
                else
                    flipping = false;
            }
            // is mask set for one of the previous bits
            else if ((a.mask & (1 << (bit - 1))) || (this->mask & (1 << (bit - 1)))) {
                if (a.mask & (1 << (bit - 1)))
                    previous =  (a.word    >> (bit - 1)) & 0x00000001;
                else
                    previous = (this->word >> (bit - 1)) & 0x00000001;
                // if previous = 0, current = 0, skip_flip = 0 and we are still 
                // flipping, then we continue to flip
                if (((previous | skip_flip | current) == 0) && (flipping))
                    flipping = true;
                // if previous = 1, current = 1, skip_flip = 1 and we are still
                // flipping, then we continue to flip
                else if (((previous & skip_flip & current) == 1) && (flipping))
                    flipping = true;
                else
                    flipping = false;
            }
            else
                flipping = false;
        }
        // mask is set for no bits
        else
            flipping = false;
    }
    
    this->word = sum;
    this->mask = mask;
    
    return *this;
    
}


Word Word :: operator-= (const Word & a) {
    Word b = a;
    b = ~b;// Word(0xffffffff, 0xffffffff);
    b += Word(0x00000001, 0xffffffff);
    *this += b;
    
    return *this;
}


Word Word :: operator& (const Word & a) {
    Word tmp = *this;
    tmp &= a;
    return tmp;
}


Word Word :: operator| (const Word & a) {
    Word tmp = *this;
    tmp |= a;
    return tmp;
}


Word Word :: operator^ (const Word & a) {
    Word b;
    
    b = *this;
    b ^= a;
    
    return b;
}


Word Word :: operator+ (const Word & a) {
    Word tmp;
    
    tmp  = *this;
    tmp += a;
    
    return tmp;
}


Word Word :: operator- (const Word & a) {
    Word tmp;
    
    tmp  = *this;
    tmp -= a;
    
    return tmp;
}


Word Word :: operator~ () {
    Word b;
    
    b.mask = this->mask;
    b.word = ~(this->word);
    b.name = "~" + this->name;
    
    return b;
}


Word Word :: operator= (const Word & a) {

    if (this == &a)
        return *this;
    
    this->word = a.word;
    this->mask = a.mask;
    
    return *this;
    
}


Word Word :: rotl (int bits) {
    Word b;
    
    b.word = word_rotl(this->word, bits);
    b.mask = word_rotl(this->mask, bits);
    
    return b;
}


Word Word :: rotr (int bits) {
    Word b;
    
    b.word = word_rotr(this->word, bits);
    b.mask = word_rotr(this->mask, bits);
    
    return b;
}


void Word :: take_bits (Word a) {
    this->mask |= a.mask;
    this->word |= (a.word & a.mask);
}


string Word :: bit_string () {
    char buf[9];
    int i;
    string bit_string;
    
    for (i = 31; i >= 0; i--) {
        if ((this->mask >> i) & 0x00000001) {
            if ((this->word >> i) & 0x00000001)
                bit_string += "1";
            else
                bit_string += "0";
        }
        else
            bit_string += "?";
    }
    
    snprintf(buf, 9, "%08x", this->word);
    bit_string += " ";
    bit_string += buf;
    
    snprintf(buf, 9, "%08x", this->mask);
    bit_string += " ";
    bit_string += buf;
    
    return bit_string;
}
