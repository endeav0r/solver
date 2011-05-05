#include <iostream>
#include <list>
#include <sstream>

#include "word.hpp"
#include "add.hpp"
#include "and.hpp"
#include "or.hpp"
#include "rotl.hpp"
#include "not.hpp"
#include "xor.hpp"

class Solver {

    private :
        std::list <Operation *> operations;
        std::list <Word *> op_words;
        Word * a[13];
        Word * b[13];
        Word * c[13];
        Word * d[13];
        Word * M[16];
        
        Word * GConstant;
        Word * HConstant;
        
        void md4F (Word * a, Word * b, Word * c, Word * d,
                   Word * M, Word * r, int step, int bits);
        
        void md4G (Word * a, Word * b, Word * c, Word * d,
                   Word * M, Word * r, int step, int bits);
        
        void md4H (Word * a, Word * b, Word * c, Word * d,
                   Word * M, Word * r, int step, int bits);
                   
        Operation * get_operation (std::string name);
        Word * get_op_word (std::string name);
        Word find_best_M (std::string operation_name, int M_index);
        void find_best_Ms ();
       
        bool validate();
        int bit_count();
        void initialize_values();
        void execute();
        void output_state ();
    
    public :
        Solver ();
        ~Solver ();
        void solve ();
        Solver operator=  (const Solver & a);
};
