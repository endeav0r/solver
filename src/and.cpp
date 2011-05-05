#include "and.hpp"

And :: And ()                 { this->name = "";   }
And :: And (std::string name) { this->name = name; }

void And :: add_operand (Word * operand) { this->operands.push_back(operand); }
void And :: s_result    (Word * result ) { this->result = result; }

// a & b = r
bool And :: execute () {
    bool changed = false;
    unsigned int word;
    unsigned int mask;
    Word tmp;
    std::list <Word *> :: iterator it;
    std::list <Word *> :: iterator it2;

    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS IN BOTH A AND B
    **/
    mask = this->result->g_mask();
    tmp = Word(0xffffffff, 0xffffffff);
    
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        tmp &= **it;
    }
    
    // tmp now holds a & b, so any bits that are set in tmp need to be set in
    // result
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;
    
    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS NOT SET IN A OR B
    **/
    mask = this->result->g_mask();
    word = 0x00000000;
    
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        // if operand bit is NOT set and IS masked, word is set
        word |= ~((*it)->g_word()) & (*it)->g_mask();
    }
    
    // all bits set in word will be 0 in result
    tmp = Word(0x00000000, word);
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;
    
    
    /**
    *** SOLVE FOR BITS IN OPERAND
    **/
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        // find out what all other operands are ANDed together
        tmp = Word(0xffffffff, 0xffffffff);
        for (it2 = this->operands.begin(); it2 != this->operands.end(); it2++) {
            if ((*it) != (*it2)) {
                tmp &= **it2;
            }
        }
        // for all bits that are 1 in the other operands, this operand takes all
        // the bits from the result
        tmp.s_mask(tmp.g_word() & tmp.g_mask());
        tmp &= *(this->result);
        // all of the 1s in tmp are going to be 0 in this operand
        mask = (*it)->g_mask();
        (*it)->take_bits(tmp);
        if (mask != (*it)->g_mask())
            changed = true;
    }
    
    return changed;
}
