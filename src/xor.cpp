#include "xor.hpp"

Xor :: Xor ()                 { this->name = "";   }
Xor :: Xor (std::string name) { this->name = name; }

void Xor :: add_operand (Word * operand) { this->operands.push_back(operand); }
void Xor :: s_result    (Word * result ) { this->result = result; }

// a & b = r
bool Xor :: execute () {
    bool changed = false;
    unsigned int mask;
    
    Word tmp;
    std::list <Word *> :: iterator it;
    std::list <Word *> :: iterator it2;


    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS IN BOTH A AND B
    **/
    it = this->operands.begin();
    tmp = **it;
    it++;
    while (it != this->operands.end()) {
        tmp ^= **it;
        it++;
    }
    mask = this->result->g_mask();
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;
        
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        tmp = *(this->result);
        for (it2 = this->operands.begin(); it2 != this->operands.end(); it2++) {   
            if (*it != *it2)
                tmp ^= **it2;
        }
        mask = (*it)->g_mask();
        (*it)->take_bits(tmp);
        if (mask != (*it)->g_mask())
            changed = true;
    }
    
    return changed;
}
