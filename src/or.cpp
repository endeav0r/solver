#include "or.hpp"

Or :: Or ()                 { this->name = "";   }
Or :: Or (std::string name) { this->name = name; }

void Or :: add_operand (Word * operand) { this->operands.push_back(operand); }
void Or :: s_result    (Word * result ) { this->result = result; }

// a & b = r
bool Or :: execute () {
    bool changed = false;
    unsigned int word;
    unsigned int mask;
    Word tmp;
    std::list <Word *> :: iterator it;
    std::list <Word *> :: iterator it2;

    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS IN A AND B
    *** if the bit is set in any operand, it will be set in r
    **/
    mask = this->result->g_mask();
    word = 0x00000000;
    
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        word |= (*it)->g_word();
    }
    
    // tmp now holds a & b, so any bits that are set in tmp need to be set in
    // result
    this->result->take_bits(Word(word, word));
    if (mask != this->result->g_mask())
        changed = true;

    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS IN A AND B
    *** if the bit is not set in any operand, it will be not set in r
    **/
    
    mask = this->result->g_mask();
    tmp = Word(0x00000000, 0xffffffff);
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        tmp |= (**it);
    }
    
    // all of the 0s become the mask
    tmp.s_mask(~(tmp.g_word()) & tmp.g_mask());
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;

    /**
    *** SOLVE FOR BITS IN OPERAND
    **/
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        // find out what all other operands are ORed together
        tmp = Word(0x00000000, 0xffffffff);
        for (it2 = this->operands.begin(); it2 != this->operands.end(); it2++) {
            if ((*it) != (*it2))
                tmp |= *(*it2);
        }
        // we want the bits that are 0 in all other operands to become the
        // mask for this operand
        tmp.s_mask(~(tmp.g_word()) & tmp.g_mask());
        tmp.s_word(0x00000000);
        // these bits will come directly from the result
        tmp |= *(this->result);
        
        // all of the 1s in tmp are going to be 0 in this operand
        mask = (*it)->g_mask();
        (*it)->take_bits(tmp);
        if (mask != (*it)->g_mask())
            changed = true;
    }
    
    return changed;
}
