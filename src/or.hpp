#ifndef or_HEADER
#define or_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

class Or : public Operation {

    private :
        Word * result;
        std::list <Word *> operands;
    
    public :
        Or ();
        Or (std::string name);
        void add_operand (Word * operand);
        void s_result    (Word * result);
        bool execute ();
        
};      
        
#endif
