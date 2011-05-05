#include "not.hpp"

Not :: Not ()                 { this->name = "";   }
Not :: Not (std::string name) { this->name = name; }
void Not :: s_source (Word * source) { this->source = source; }
void Not :: s_result (Word * result) { this->result = result; }

bool Not :: execute () {
    bool changed = false;
    unsigned int mask;
    Word tmp;
    
    tmp = Word(~(this->source->g_word()), this->source->g_mask());
    mask = this->result->g_mask();
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;
    
    
    tmp = Word(~(this->result->g_word()), this->result->g_mask());
    mask = this->source->g_mask();
    this->source->take_bits(tmp);
    if (mask != this->source->g_mask())
        changed = true;
    
    return changed;
}
