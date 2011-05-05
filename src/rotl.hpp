#ifndef rotl_HEADER
#define rotl_HEADER

#include <list>
#include <string>

#include "operation.hpp"
#include "word.hpp"

#define rotl(x,s) ((x << s) | (x >> (32 - s)))
#define rotr(x,s) ((x >> s) | (x << (32 - s)))


class Rotl : public Operation {

    private :
        int bits;
        Word * result;
        Word * source;
    
    public :
        Rotl ();
        Rotl (std::string name);
        void s_source (Word * source);
        void s_result (Word * result);
        void s_bits   (int bits);
        bool execute ();
        
};      
        
#endif
