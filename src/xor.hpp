#ifndef xor_HEADER
#define xor_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

class Xor : public Operation {

    private :
        Word * result;
        std::list <Word *> operands;
    
    public :
        Xor ();
        Xor (std::string name);
        void add_operand (Word * operand);
        void s_result    (Word * result);
        bool execute ();
        
};      
        
#endif
