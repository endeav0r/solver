#ifndef and_HEADER
#define and_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

class And : public Operation {

    private :
        Word * result;
        std::list <Word *> operands;
    
    public :
        And ();
        And (std::string name);
        void add_operand (Word * operand);
        void s_result    (Word * result);
        bool execute ();
        
};      
        
#endif
