#include "rotl.hpp"

Rotl :: Rotl ()                 { this->name = "";   }
Rotl :: Rotl (std::string name) { this->name = name; }
void Rotl :: s_source (Word * source) { this->source = source; }
void Rotl :: s_result (Word * result) { this->result = result; }
void Rotl :: s_bits   (int bits)      { this->bits = bits;     }

bool Rotl :: execute () {
    bool changed = false;
    unsigned int mask;
    Word tmp;
    
    tmp = Word(rotl(this->source->g_word(), this->bits),
               rotl(this->source->g_mask(), this->bits));
    mask = this->result->g_mask();
    this->result->take_bits(tmp);
    if (mask != this->result->g_mask())
        changed = true;
    

    tmp = Word(rotr(this->result->g_word(), this->bits),
               rotr(this->result->g_mask(), this->bits));
    mask = this->source->g_mask();
    this->source->take_bits(tmp);
    if (mask != this->source->g_mask())
        changed = true;
    
    return changed;
}
