#include "word.hpp"


Word :: Word (unsigned int word, unsigned int mask) {
    this->name = "";
    this->word = word;
    this->mask = mask;
    this->lock_bool = false;
}


Word :: Word (std::string name, unsigned int word) {
    this->name = name;
    this->word = word;
    this->lock_bool = false;
    this->mask = 0x00000000;
}


Word :: Word (std::string name) {
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
    int current;
    int bit;
    int carry; // -1 = unknown what bit carried to this location
               //  0 = no bit was carried to this location
               //  1 = 1 bit was carried to this location

    carry = -1;
    sum = a.word + this->word;
    mask = 0x00000000;
    
    // first bit is a special case
    // both first bits are set
    if ((a.mask & 0x00000001) && (this->mask & 0x00000001)) {
        if (((a.word & 0x00000001) == 1) && ((this->word & 0x00000001) == 1))
            carry = 1;
        else
            carry = 0;
        mask = 0x00000001;
    }
    // one first bit is set. we may at least know if we carry
    else if ((a.mask & 0x00000001) && ((a.word & 0x00000001) == 0))
        carry = 0;
    else if ((this->mask & 0x00000001) && ((this->mask & 0x00000001) == 0))
        carry = 0;
    
    // these are rules for when we have 0-0 or 1-1 to initiate flipping
    // bits
    for (bit = 1; bit < 32; bit++) {
        // is mask is set for both of these bits
        if ((a.mask & (1 << bit)) && (this->mask & (1 << bit))) {
            // if we knew what carried here, then we know what the result will
            // be
            if (carry >= 0)
                mask |= 1 << bit;
            // we always know from here what will carry to the next place
            current = ((a.word >> bit) & 0x00000001) 
                       + ((this->word >> bit) & 0x00000001);
            if (carry >= 0) {
                if (current + carry >= 2)
                    carry = 1;
                else
                    carry = 0;
            }
            else {
                if (current == 0)
                    carry = 0;
                else if (current == 2)
                    carry = 1;
                else
                    carry = -1;
            }
        }
        // mask is set for one of the bits
        else if ((a.mask & (1 << bit)) || (this->mask & (1 << bit))) {
            if (a.mask & (1 << bit))
                current = (a.word     >> bit) & 0x00000001;
            else
                current = (this->word >> bit) & 0x00000001;
            // if we currently have a 1 and we carried a 1, we know we will
            // carry a 1 from this location
            if ((current == 1) && (carry == 1))
                carry = 1;
            // if we currently have a 0 and we carried a 0, we know we will not
            // carry any bits from this location
            else if ((current == 0) && (carry == 0))
                carry = 0;
            // otherwise we do not know if we will carry a bit from this
            // location
            else
                carry = -1;
        }
        // mask is set for no bits
        else
            carry = -1;
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


std::string Word :: bit_string () {
    char buf[9];
    int i;
    std::string bit_string;
    
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
