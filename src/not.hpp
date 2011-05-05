#ifndef not_HEADER
#define not_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"


class Not : public Operation {

    private :
        Word * result;
        Word * source;
    
    public :
        Not ();
        Not (std::string name);
        void s_source (Word * source);
        void s_result (Word * result);
        bool execute ();
        
};      
        
#endif
