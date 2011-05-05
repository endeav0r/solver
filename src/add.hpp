#ifndef add_HEADER
#define add_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

class Add : public Operation {

    private :
        Word * result;
        std::list <Word *> operands;
    
    public :
        Add ();
        Add (std::string name);
        void add_operand (Word * operand);
        void s_result    (Word * result);
        Word best_adder (std::string exclude = "");
        bool subtractor (Word accumulator, Word * operand,
                         std::list <Word *> operands);
        bool adder (Word accumulator, Word * operand,
                    std::list <Word *> operands);
        bool execute ();
};      
        
#endif
