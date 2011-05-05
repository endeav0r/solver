#include "same.hpp"

Same :: Same ()                 { this->name = "";   }
Same :: Same (std::string name) { this->name = name; }

void Same :: add_operand (Word * operand) { this->operands.push_back(operand); }
void Same :: s_result    (Word * result ) { this->result = result; }

// a & b = r
bool Same :: execute () {
    unsigned int word;
    unsigned int mask;
    std::list <Word *> :: iterator it;
    Word tmp;
    
    it = this->operands.begin();
    word = (*it)->g_word();
    mask = (*it)->g_mask();
   
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        mask &= (*it)->g_mask();
        mask &= ~(word ^ (*it)->g_word());
    }
    tmp = Word(word, mask);
    mask = this->result->g_mask();
    this->result->take_bits(tmp);
    if (this->result->g_mask() != mask)
        return true;
    return false;
}
