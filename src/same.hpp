#ifndef same_HEADER
#define same_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

/*
* This is a special type of operation.
* All of the bits that are MASKED and the SAME in the operands are set in
* the result
* This is also a ONE-WAY operation. Bits that are set in the result are not
* automatically set in the operands
*/

class Same : public Operation {

    private :
        Word * result;
        std::list <Word *> operands;
    
    public :
        Same ();
        Same (std::string name);
        void add_operand (Word * operand);
        void s_result    (Word * result);
        bool execute ();
        
};      
        
#endif
