#include "add.hpp"

#include <cstdlib>

Add :: Add ()                 { this->name = "";   }
Add :: Add (std::string name) { this->name = name; }

void Add :: add_operand (Word * operand) { this->operands.push_back(operand); }
void Add :: s_result    (Word * result ) { this->result = result; }


Word Add :: best_adder (std::string exclude) {
    std::list <Word *> :: iterator it;
    int bit;
    bool flipping = false;
    int operands_not_set = 0;
    unsigned int bit_mask;
    unsigned int mask = 0x00000000;
    unsigned int word = 0x00000000;
    int previous_value;
    int current_value = 0;
    
    for (bit = 0; bit < 32; bit++) {
        bit_mask = 1 << bit;
        previous_value = current_value;
        current_value = -1; // -1 is not set
        operands_not_set = 0;
        // we need to find out what the current value at this position is for
        // all operands that are masked, and how many operands are not masked
        for (it = operands.begin(); it != operands.end(); it++) {
            if ((*it)->g_name() == exclude)
                continue;
            // is the mask set for this word
            if ((*it)->g_mask() & bit_mask) {
                if (current_value == -1)
                    current_value = ((*it)->g_word() >> bit) & 0x00000001;
                else 
                    current_value += ((*it)->g_word() >> bit) & 0x00000001;
            }
            else
                operands_not_set++;
        }
        // if all operands are masked
        if (operands_not_set == 0) {
            // if we are not already flipping, we need to start flipping and
            // the best value is the one that allows that to happen (IE provides
            // an even value for this position)
            if (flipping == false) {
                mask |= 1 << bit;
                word |= (current_value % 2) << bit;
                flipping = true;
            }
            // if we're already flipping then it does not matter what the value
            // is here
        }
        // if only one operand is not masked
        else if (operands_not_set == 1) {
            // and we are still flipping
            if (flipping == true) {
                // find out what the previous value was, and make sure the
                // current value lines up with that
                if ((current_value % 2) != (previous_value % 2))
                    word |= 1 << bit;
                mask |= 1 << bit;
            }
            // otherwise don't do anything
        }
        else
            flipping = false;
    }
    
    return Word(word, mask);
}   


bool Add :: subtractor (Word accumulator, Word * operand,
                        std::list <Word *> operands) {
    unsigned int mask;
    bool changed = false;
    std::list <Word *> ops;
    std::list <Word *> :: iterator it;
    
    if (operands.size() == 0) {
        mask = operand->g_mask();
        operand->take_bits(accumulator);
        if (mask != operand->g_mask())
            return true;
        return false;
    }
    
    for (it = operands.begin(); it != operands.end(); it++) {
        ops = operands;
        ops.remove(*it);
        if (subtractor(accumulator - **it, operand, ops))
            changed = true;
    }
    return changed;
}


bool Add :: adder (Word accumulator, Word * operand,
                   std::list <Word *> operands) {
    unsigned int mask;
    bool changed = false;
    std::list <Word *> ops;
    std::list <Word *> :: iterator it;
    
    if (operands.size() == 0) {
        mask = operand->g_mask();
        operand->take_bits(accumulator);
        if (mask != operand->g_mask())
            return true;
        return false;
    }
    
    for (it = operands.begin(); it != operands.end(); it++) {
        ops = operands;
        ops.remove(*it);
        if (adder(accumulator + **it, operand, ops))
            changed = true;
    }
    return changed;
}


// a & b = r
bool Add :: execute () {
    bool changed = false;
    Word tmp;
    std::list <Word *> ops;
    std::list <Word *> :: iterator it;

    /**
    *** SOLVE FOR BITS IN R BASED OFF BITS IN A AND B
    **/
    
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        ops = this->operands;
        ops.remove(*it);
        if (adder(**it, this->result, ops))
            changed = true;
    }
    
    /**
    *** SOLVE FOR OPERAND BY SUBTRACTING OTHER OPERANDS FROM RESULT
    **/
        
    for (it = this->operands.begin(); it != this->operands.end(); it++) {
        ops = this->operands;
        ops.remove(*it);
        if (subtractor(*(this->result), *it, ops))
            changed = true;
    }
    
    return changed;
}
